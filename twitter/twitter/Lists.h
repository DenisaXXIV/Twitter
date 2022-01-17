#pragma once
#include<vector>
#include<algorithm>

#include "User.h"

class Lists
{
public:
	class List
	{
	public:
		List() = default;
		List(std::string, User, std::vector<User>, std::vector<User>);
		~List() = default;
		
		std::string GetListName()const;
		User GetListCreator()const;
		std::vector<User> GetListMembers()const;
		std::vector<User> GetListFollowers()const;

		void SetListName(const std::string&);
		void SetListCreator(const User&);
		void SetListMembers(const std::vector<User>&);
		void SetListFollowers(const std::vector<User>&);

		void AddListMember(const User&);
		void DeleteListMember(const User&);
		void AddListFollower(const User&);
		void DeleteListFollower(const User&);


	private:
		std::string m_listName;
		User m_listCreator;
		std::vector<User> m_listMembers;
		std::vector<User> m_listFollowers;	
	};

	Lists() = default;
	Lists(std::vector<List>);
	~Lists() = default;

	
	std::vector<List> GetLists()const ;

	void SetLists(const std::vector<List>&);

	void AddList(const List&);
	void DeleteList(const List&);

private:
	std::vector<List> m_lists;

};

