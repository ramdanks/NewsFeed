#pragma once
#include <string>
#include <pqxx/pqxx>

enum DBReturn
{
	DBERR   = -1,
	VALID   = 1,
	NOVALID = 0,
};

class DBRequest
{
private:
	DBRequest() {}

public:
	static bool Init();
	static bool Online();
	static bool Offline();

	static bool UserExist(const std::string& username);
	static DBReturn Login(const std::string& username, const std::string& password);
	static DBReturn Signup(const std::string& username, const std::string& password, const std::string& email);

private:
	static pqxx::result Exec(const char* cmd);

	static pqxx::connection* sConnect;
	static char sBuff[1024];
};

#define DB_USEREXIST_CMD  "SELECT EXISTS(SELECT FROM Account WHERE username='%s')"
#define DB_LOGIN_CMD      "SELECT EXISTS(SELECT 1 FROM Account WHERE username='%s' and password='%s')"
#define DB_SIGNUP_CMD     "INSERT INTO Account VALUES('%s', '%s', '%s')"