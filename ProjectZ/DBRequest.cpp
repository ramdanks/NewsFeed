#include "DBRequest.h"
#include "Instrumentator.h"
#include <iostream>

pqxx::connection* DBRequest::sConnect;
char DBRequest::sBuff[1024];

const char opt[] = "host=localhost port=5432 dbname=projectz_db user=postgres";

bool DBRequest::Init()
{
	PROFILE_FUNC();
	try
	{
		if (!sConnect) sConnect = new pqxx::connection(opt);
	}
	catch (...)
	{
		return false;
	}
	return sConnect->is_open();
}

bool DBRequest::Online()
{
	PROFILE_FUNC();
	if (!sConnect) return false;
	return sConnect->is_open();
}

bool DBRequest::Offline()
{
	PROFILE_FUNC();
	return !Online();
}

bool DBRequest::UserExist(const std::string& username)
{
	PROFILE_FUNC();
	try
	{
		sprintf_s(sBuff, sizeof(sBuff), DB_USEREXIST_CMD, username.c_str());
		pqxx::result res = Exec(sBuff);
		return res[0][0].as<bool>();
	}
	catch (...)
	{
		return false;
	}
}

bool DBRequest::Login(const std::string& username, const std::string& password)
{
	PROFILE_FUNC();
	if (!sConnect) Init();
	sprintf_s(sBuff, sizeof(sBuff), DB_LOGIN_CMD, username.c_str(), password.c_str());
	pqxx::result res = Exec(sBuff);
	return res[0][0].as<bool>();
}

bool DBRequest::Signup(const std::string& username, const std::string& password,
					   const std::string& email, const std::string& dob)
{
	PROFILE_FUNC();
	if (!sConnect) Init();
	sprintf_s(sBuff, sizeof(sBuff), DB_SIGNUP_CMD, username.c_str(),
			  password.c_str(), email.c_str(), dob.c_str());
	pqxx::work work(*sConnect);
	work.exec(sBuff);
	work.commit();
	return true;
}

pqxx::result DBRequest::Exec(const char* cmd)
{
	PROFILE_FUNC();
	if (Offline()) throw - 1;
	pqxx::work work(*sConnect);
	auto ret = work.exec(sBuff);
	return ret;
}