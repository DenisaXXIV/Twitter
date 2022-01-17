#include "Lists.h"


Lists::List::List(std::string listName, User listCreator, std::vector<User> listMembers, std::vector<User> listFollowers):
	m_listName(listName), 
	m_listCreator(listCreator), 
	m_listMembers(listMembers),
	m_listFollowers(listFollowers)
{
}

std::string Lists::List::GetListName()const
{
	return this->m_listName;
}

User Lists::List::GetListCreator()const 
{
	return this->GetListCreator();
}

std::vector<User> Lists::List::GetListMembers()const 
{
	return this->m_listMembers;
}

std::vector<User> Lists::List::GetListFollowers()const 
{
	return this->m_listFollowers;
}

void Lists::List::SetListName(const std::string& listName)
{
	this->m_listName = listName;
}

void Lists::List::SetListCreator(const User& listCreator)
{
	//copyConstructor User
}



void Lists::List::SetListMembers(const std::vector<User>& listMembers)
{
	this->m_listMembers.clear();
	for (User i : listMembers)
	{
		this->m_listMembers.push_back(i);
	}
}

void Lists::List::SetListFollowers(const std::vector<User>& listFollowers)
{
	this->m_listFollowers.clear();
	for (User i : listFollowers)
	{
		this->m_listFollowers.push_back(i);
	}
}


void Lists::List::AddListMember(const User& listMember)
{
	for (User i : this->m_listMembers)
	{
		if (i == listMember)//== operator
			return;
	}
	this->m_listMembers.push_back(listMember);
}

void Lists::List::DeleteListMember(const User& listMember)
{
	//new DeleteFunct
	//std::remove_if(this->m_listMembers.begin(), this->m_listMembers.end(), listMember);
	
}

void Lists::List::AddListFollower(const User& listFollower)
{
	for (User i : this->m_listFollowers)
	{
		if (i == listFollower)//== operator
			return;
	}
	this->m_listFollowers.push_back(listFollower);
}

void Lists::List::DeleteListFollower(const User& listFollower)
{
	//new DeleteFunct
	//std::remove_if(this->m_listFollowers.begin(),this->m_listFollowers.end(),listFollower)
}



Lists::Lists(std::vector<List> lists)
	:m_lists(lists)
{
}


std::vector<Lists::List> Lists::GetLists()const
{
	return this->m_lists;
}

void Lists::SetLists(const std::vector<List>& lists)
{
	this->m_lists.clear();
	for (List i : lists)
	{
		this->m_lists.push_back(i);
	}
}

void Lists::AddList(const List& list)
{
	for (int i = 0;i < m_lists.size();i++)
	{
		if (m_lists[i].GetListName() == list.GetListName() and m_lists[i].GetListCreator() == list.GetListCreator())// == operator User
			return;
	}
	this->m_lists.push_back(list);
}

void Lists::DeleteList(const List& list)
{
	//deleteFunct
}
