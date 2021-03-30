#include "DBRequest.h"
#include "Instrumentator.h"

pqxx::connection* DBRequest::sConnect;
char DBRequest::sBuff[1024];

const char opt[] = "host=localhost port=5432 dbname=projectz_db user=postgres";

bool DBRequest::Init()
{
	PROFILE_FUNC();
	if (!sConnect) sConnect = new pqxx::connection(opt);
	return sConnect->is_open();
}

bool DBRequest::Online()
{
	PROFILE_FUNC();
	return sConnect->is_open();
}

bool DBRequest::Offline()
{
	PROFILE_FUNC();
	return !sConnect->is_open();
}

bool DBRequest::Login(std::string username, std::string password)
{
	PROFILE_FUNC();
	try
	{
		if (Offline()) throw -1;
		sprintf_s(sBuff, sizeof(sBuff), DB_LOGIN_VALIDATION, username.c_str(), password.c_str());
	}
	catch (...)
	{
		return false;
	}
	pqxx::work work(*sConnect);
	pqxx::result res = work.exec(sBuff);
	return res[0][0].as<bool>();
}
