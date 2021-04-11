#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <vector>
#include <pqxx/pqxx>
#include "Profile.h"
#include "Feed.h"

class DBRequest
{
private:
	DBRequest() {}

public:
	static bool Init();
	static bool Online();
	static bool Offline();

	static bool UserExist(const std::string& username);
	static bool Login(const std::string& username, const std::string& password);
	static bool Signup(const std::string& username, const std::string& password,
					   const std::string& email, const std::string& dob);

	static bool SetBio(const std::string& bio, const std::string& username);
	static bool SetDisplayName(const std::string& displayname , const std::string& username);

	static std::vector<std::string> GetFollowing(const std::string& username);
	static bool Follow(const std::string& sender, const std::string& receiver);
	static bool Unfollow(const std::string& sender, const std::string& receiver);

	static unsigned int GetFid(const std::string& label, const std::string& owner);
	static std::string GetFlag(unsigned int fid);
	static std::vector<std::string> GetFlag(const std::string& owner);
	static bool AddFlag(const std::string& label, const std::string& owner);
	static bool RemoveFlag(const std::string& label, const std::string& owner);

	static std::vector<sFeed> GetFeeds(const std::string& username);
	static std::pair<int, std::string> PostFeed(const std::string& actor, const std::string& text, unsigned int fid);

	static sProfile GetProfile(const std::string& username);

private:
	static pqxx::result ExecCommit(const char* cmd);
	static pqxx::result Exec(const char* cmd);

	static pqxx::connection* sConnect;
	static char sBuff[1024];
};

#define DB_USEREXIST_CMD           "SELECT EXISTS(SELECT FROM Account WHERE username='%s')"
#define DB_LOGIN_CMD               "SELECT EXISTS(SELECT 1 FROM Account WHERE username='%s' and password='%s')"
#define DB_SIGNUP_CMD              "INSERT INTO Account VALUES('%s', '%s', '%s', to_date('%s', 'YYYY-MM-DD'))"
#define DB_PROFILE_CMD             "SELECT displayname, bio FROM Account WHERE username='%s'"
#define DB_SET_BIO                 "UPDATE Account SET bio='%s' WHERE username='%s'"
#define DB_SET_DISPLAYNAME         "UPDATE Account SET displayname='%s' WHERE username='%s'"
							       
#define DB_FOLLOWING_CMD           "SELECT receiver FROM Follow WHERE sender='%s'"
#define DB_FOLLOW_CMD              "INSERT INTO Follow(sender,receiver) VALUES('%s','%s')"
#define DB_UNFOLLOW_CMD            "DELETE FROM Follow WHERE sender='%s' AND receiver='%s'"
								   
#define DB_GET_FID_CMD             "SELECT id FROM Flag WHERE label='%s' AND owner='%s'"
#define DB_GET_FLAG_PRIMARY_CMD    "SELECT label FROM Flag WHERE id='%u'"
#define DB_GET_FLAG_CMD            "SELECT label FROM Flag WHERE owner='%s'"
#define DB_ADD_FLAG_CMD            "INSERT INTO Flag(label,owner) VALUES('%s','%s')"
#define DB_REMOVE_FLAG_CMD         "DELETE FROM Flag WHERE label='%s' AND owner='%s'"
								   
#define DB_FEED_GET_CMD             "SELECT * FROM Feed WHERE actor='%s'"
#define DB_FEED_POST_CMD            "INSERT INTO Feed(actor,text,fid) VALUES ('%s','%s','%u') RETURNING id,postTime"