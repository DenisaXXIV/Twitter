#pragma once

#include <string>

#include "DatabaseConnection.h"

class RetweetService
{
	void AddRetweet(std::string text, std::string date, std::string time, std::string id_user,int id_tweet);
	void DeleteRetweet(int id_retweet);
	void EditRetweet(int id_retweet, std::string newText);
	int GetId(std::string text, std::string date, std::string time, std::string id_user, int id_tweet);

	std::string GetText(int id_retweet) const;
	std::string GetDate(int id_retweet) const;
	std::string GetTime(int id_retweet) const;
	std::string GetUser(int id_retweet) const;
	int GetTweet(int id_retweet) const;

	void SetText(const int& id_retweet, const std::string& newText);
	void SetDate(const int& id_retweet, const std::string& newDate);
	void SetTime(const int& id_retweet, const std::string& newTime);
	void SetUser(const int& id_retweet, const std::string& newUser);
	void SetTweet(const int& id_retweet, const int newTweet);
};

