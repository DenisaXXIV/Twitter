#include "Notifications.h"

Notifications::Notifications(std::vector<std::string> notifList)
	:m_notifList(notifList)
{
}

std::vector<std::string> Notifications::GetNotifList()const 
{
	return this->m_notifList;
}

void Notifications::SetNotifList(const std::vector<std::string>& notifList)
{
	this->m_notifList.clear();
	for (std::string i : notifList)
	{
		this->m_notifList.push_back(i);
	}

}

std::string Notifications::CreateNotif(const User& user,const NotifType& notifType,const Tweet& tweet)
{
	std::string name = user.GetName();
	//isPost isComment isRetweet undefined
	std::string postType;
	//switch (notifType)
	//{
	//	case NotifType::eReplies :
	//		if (tweet.isPost())
	//			postType = "post";
	//		else
	//			postType = "retweet";
	//		return (name + " Replied to your " + postType);
	//	
	//	case NotifType::eRetweets :
	//		if (tweet.isPost())
	//			postType = "post";
	//		else
	//			postType = "retweet";
	//		return (name + " Retweeted your "+postType);

	//	case NotifType::eLikes :
	//		if (tweet.isPost())
	//			postType = "post";
	//		else
	//			postType = "retweet";
	//		return (name + " liked your "+postType);

	//	case NotifType::eNewFollowers:
	//		return (name + " followed you");

	//	case NotifType::eFollowedList:
	//		return (name + "followed your List");

	//	default://eDirectMessage
	//		return (name + " messaged you");
	//		

	//}
	return postType;
}

void Notifications::AddNotif(const std::string& notif)
{
	this->m_notifList.push_back(notif);
}

void Notifications::DeleteNotif(const std::string& notif)
{
	//deleteFunc
}
