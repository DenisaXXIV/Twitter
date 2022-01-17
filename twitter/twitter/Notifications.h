#pragma once
#include <vector>
#include <string>
#include "User.h";
#include "Tweet.h";

class Notifications
{
public:
	enum class NotifType {
		//?eMentions,
		eReplies,
		eRetweets,
		eLikes,
		eNewFollowers,
		eFollowedList,
		eDirectMessages
	};

	Notifications() = default;
	Notifications(std::vector<std::string>);
	~Notifications() = default;

	std::vector<std::string> GetNotifList()const ;

	void SetNotifList(const std::vector<std::string>&);

	std::string CreateNotif(const User& user,const NotifType& notifType,const Tweet& tweet);//Post pentru a identifica daca e post comment sau retweet
	void AddNotif(const std::string&);
	void DeleteNotif(const std::string&);

private:
	std::vector<std::string> m_notifList; 
};

