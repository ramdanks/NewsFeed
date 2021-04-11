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

	sprintf_s(sBuff, sizeof(sBuff), DB_LOGIN_CMD, username.c_str(), password.c_str());
	pqxx::result res = Exec(sBuff);
	return res[0][0].as<bool>();
}

bool DBRequest::Signup(const std::string& username, const std::string& password,
					   const std::string& email, const std::string& dob)
{
	PROFILE_FUNC();
	sprintf_s(sBuff, sizeof(sBuff), DB_SIGNUP_CMD, username.c_str(),
			  password.c_str(), email.c_str(), dob.c_str());
	ExecCommit(sBuff);
	return true;
}

bool DBRequest::SetBio(const std::string& bio, const std::string& username)
{
	PROFILE_FUNC();
	sprintf_s(sBuff, sizeof(sBuff), DB_SET_BIO, bio.c_str(), username.c_str());
	ExecCommit(sBuff);
	return true;
}

bool DBRequest::SetDisplayName(const std::string& displayname, const std::string& username)
{
	PROFILE_FUNC();
	if (displayname == username) return false;
	sprintf_s(sBuff, sizeof(sBuff), DB_SET_DISPLAYNAME, displayname.c_str(), username.c_str());
	ExecCommit(sBuff);
	return true;
}

bool DBRequest::Follow(const std::string& sender, const std::string& receiver)
{
	PROFILE_FUNC();
	if (sender == receiver) return false;
	sprintf_s(sBuff, sizeof(sBuff), DB_FOLLOW_CMD, sender.c_str(), receiver.c_str());
	ExecCommit(sBuff);
	return true;
}

bool DBRequest::Unfollow(const std::string& sender, const std::string& receiver)
{
	PROFILE_FUNC();
	if (sender == receiver) return false;
	sprintf_s(sBuff, sizeof(sBuff), DB_UNFOLLOW_CMD, sender.c_str(), receiver.c_str());
	ExecCommit(sBuff);
	return true;
}

unsigned int DBRequest::GetFid(const std::string& label, const std::string& owner)
{
	sprintf_s(sBuff, sizeof(sBuff), DB_GET_FID_CMD, label.c_str(), owner.c_str());
	pqxx::result res = Exec(sBuff);
	return res[0][0].as<unsigned int>();
}

std::string DBRequest::GetFlag(unsigned int fid)
{
	sprintf_s(sBuff, sizeof(sBuff), DB_GET_FLAG_PRIMARY_CMD, fid);
	pqxx::result res = Exec(sBuff);
	return res[0][0].c_str();
}

std::vector<std::string> DBRequest::GetFlag(const std::string& owner)
{
	sprintf_s(sBuff, sizeof(sBuff), DB_GET_FLAG_CMD, owner.c_str());
	pqxx::result res = Exec(sBuff);

	std::vector<std::string> vector;
	vector.reserve(res.size());
	for (auto row : res)
	{
		const char* label = row["label"].c_str();
		vector.emplace_back(label);
	}
	return vector;
}

bool DBRequest::AddFlag(const std::string& label, const std::string& owner)
{
	sprintf_s(sBuff, sizeof(sBuff), DB_ADD_FLAG_CMD, label.c_str(), owner.c_str());
	ExecCommit(sBuff);
	return true;
}

bool DBRequest::RemoveFlag(const std::string& label, const std::string& owner)
{
	sprintf_s(sBuff, sizeof(sBuff), DB_REMOVE_FLAG_CMD, label.c_str(), owner.c_str());
	ExecCommit(sBuff);
	return true;
}

std::vector<sFeed> DBRequest::GetFeeds(const std::string& username)
{
	sprintf_s(sBuff, sizeof(sBuff), DB_FEED_GET_CMD, username.c_str());
	pqxx::result res = Exec(sBuff);

	std::vector<sFeed> vector;
	vector.reserve(res.size());
	for (auto row : res)
	{
		sFeed f;
		auto fid = row["fid"].as<unsigned int>();
		f.id = row["id"].as<unsigned int>();
		f.text = row["text"].c_str();
		f.date = row["postTime"].c_str();
		f.flag = GetFlag(fid);
		vector.emplace_back(f);
	}

	return vector;
}

std::pair<int, std::string> DBRequest::PostFeed(const std::string& actor, const std::string& text, unsigned int fid)
{
	std::pair<int, std::string> pair(0,"");
	sprintf_s(sBuff, sizeof(sBuff), DB_FEED_POST_CMD, actor.c_str(), text.c_str(), fid);
	auto res = ExecCommit(sBuff);
	if (!res.empty())
	{
		pair.first = res[0][0].as<int>();
		pair.second = res[0][1].c_str();
	}
	return pair;
}

sProfile DBRequest::GetProfile(const std::string& username)
{
	PROFILE_FUNC();

	sprintf_s(sBuff, sizeof(sBuff), DB_PROFILE_CMD, username.c_str());
	pqxx::result res = Exec(sBuff);

	sProfile p;
	for (auto row : res)
	{
		p.displayname = row["displayname"].c_str();
		p.bio = row["bio"].c_str();
		p.username = username;
		if (p.displayname.empty())
			p.displayname = username;
	}

	return p;
}

std::vector<std::string> DBRequest::GetFollowing(const std::string& username)
{
	sprintf_s(sBuff, sizeof(sBuff), DB_FOLLOWING_CMD, username.c_str());
	pqxx::result res = Exec(sBuff);

	std::vector<std::string> vector;
	vector.reserve(res.size());
	for (auto row : res)
	{
		std::string user = row["receiver"].c_str();
		user.erase(user.find_last_not_of(' ') + 1);
		vector.emplace_back(user);
	}

	return vector;
}

pqxx::result DBRequest::ExecCommit(const char* cmd)
{
	PROFILE_FUNC();
	if (Offline()) throw - 1;
	pqxx::work work(*sConnect);
	auto res = work.exec(sBuff);
	work.commit();
	return res;
}

pqxx::result DBRequest::Exec(const char* cmd)
{
	PROFILE_FUNC();
	if (Offline()) throw - 1;
	pqxx::work work(*sConnect);
	auto ret = work.exec(sBuff);
	return ret;
}