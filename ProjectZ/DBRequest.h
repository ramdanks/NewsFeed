#pragma once
#include <string>
#include <pqxx/pqxx>

class DBRequest
{
private:
	DBRequest() {}

public:
	static bool Init();
	static bool Online();
	static bool Offline();

	static bool Login(std::string username, std::string password);

private:
	static pqxx::connection* sConnect;
	static char sBuff[1024];
};

#define DB_LOGIN_VALIDATION "SELECT EXISTS(SELECT 1 FROM Account WHERE username='%s' and password='%s')"