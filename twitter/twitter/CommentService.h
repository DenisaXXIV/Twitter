#pragma once

#include <string>

#include "DatabaseConnection.h"

class CommentService
{
	void AddComment(std::string text, std::string date, std::string time, std::string id_user, int id_tweet);
	void DeleteComment(int id_comment);
	void EditComment(int id_comment, std::string newText);
	int GetId(std::string text, std::string date, std::string time, std::string id_user, int id_tweet);

	std::string GetText(int id_comment) const;
	std::string GetDate(int id_comment) const;
	std::string GetTime(int id_comment) const;
	std::string GetUser(int id_comment) const;
	int GetTweet(int id_comment) const;

	void SetText(const int& id_comment, const std::string& newText);
	void SetDate(const int& id_comment, const std::string& newDate);
	void SetTime(const int& id_comment, const std::string& newTime);
	void SetUser(const int& id_comment, const std::string& newUser);
	void SetTweet(const int& id_comment, const int newTweet);
};

