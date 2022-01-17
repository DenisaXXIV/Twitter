#include "Twitter.h"


std::vector<Tweet> Twitter::GetTweets() const
{
	return m_tweets;
}
std::unordered_set<std::string> Twitter::GetUsers() const
{
	return m_users;
}
Twitter::Twitter()
{
	this->m_isConnected = true;
}

void Twitter::SetTweet(const Tweet& tweet)
{
	m_tweets.push_back(tweet);
}

void Twitter::AddFriendMethod()
{
	std::string received;

	try {
		received = this->RecieveString();
	}
	catch (std::exception e)
	{
		log->LocI(Logger::Level::ERROR, "Receive error:", e.what());
		return;
	}

	UserService checkUser;
	if (checkUser.CheckUser(received))
	{

		FriendsService friendsService;
		try
		{
			if (friendsService.VerifyFriends(m_currentUser, received))
			{

				log->LocI(Logger::Level::INFO, "Username: ", m_currentUser, " and username: ", received, " are already friends!");
				std::string message = "They are already friends";
				this->m_client->Send(message.c_str(), message.size());
			}
			else
			{
				friendsService.AddFriend(this->m_currentUser, received);
				friendsService.AddFriend(received, this->m_currentUser);

				std::string message = "Added friend";
				log->LocI(Logger::Level::INFO, m_currentUser, "is now friends with", received);
				this->m_client->Send(message.c_str(), message.size());
			}
		}
		catch (std::exception e)
		{
			log->LocI(Logger::Level::ERROR, e.what());
		}
	}
	else 
	{
		log->LocI(Logger::Level::ERROR, "There is no user with username: ", received);
		std::string message = "Error";
		this->m_client->Send(message.c_str(), message.size());
	}

}

void Twitter::MakePostMethod()
	{
		std::string received;

		try {
			received = this->RecieveString();
		}
		catch (std::exception e)
		{
			log->LocI(Logger::Level::ERROR, "Receive error:", e.what());
			return;
		}
		TweetService tweetService;

		time_t now = time(0);

		// convert now to string form
		char* date_time = ctime(&now);
		std::string time;
		for (int i = 11; i < 19; i++)
		{
			time += date_time[i];
		}
		std::string date;
		for (int i = 4; i < 11; i++)
		{
			date += date_time[i];
		}
		for (int i = 20; i < 25; i++)
		{
			date += date_time[i];
		}
		log->LocI(Logger::Level::INFO, "The current date and time is: ", date_time, '\n'); 

		tweetService.AddTweet(received, date, time, m_currentUser);
	}
void Twitter::LoginMethod()
	{

		std::string recieved;
		try {
			recieved = this->RecieveString();
		}
		catch (std::exception e)
		{
			log->LocI(Logger::Level::ERROR, "Receive error:", e.what());
			return;
		}

		UserService checkUser;
		std::string message;
		if (checkUser.CheckUser(recieved))
		{
			//logare cu numele recieved;
			//construire obiect de tip user
			log->LocI(Logger::Level::INFO, "Connected on username: ", recieved);
			message = "Nice";
			m_client->Send(message.c_str(), message.size());
			/// mai incolo

			this->m_currentUser = recieved;
			this->MakeFeedPriorityQueue();
		}
		else
		{
			message = "Login Failed";
			m_client->Send(message.c_str(), message.size());
		}
	}
void Twitter::RegisterMethod()
{
	User newUser;
	bool isTaken = false;
	for (int i = 0; i < 6;)
	{
		if (isTaken == true)
			break;
		std::string message;
		
		try {
			message = this->RecieveString();
		}
		catch (std::exception e)
		{
			log->LocI(Logger::Level::ERROR, "Receive error:", e.what());
			return;
		}

		std::cout << message << '\n';
		switch (i)
		{
		case 0:
			UserService checkUser;
			if (checkUser.CheckUser(message)) //if it already exists
			{
				isTaken = true;
				message = "This username is already taken";
				m_client->Send(message.c_str(), message.size());
				i++;
			}
			else
			{
				newUser.SetUsername(message);
				message = "Continue";
				m_client->Send(message.c_str(), message.size());
				i++;
			}
			break;
		case 1:
			newUser.SetName(message);
			i++;
			break;
		case 2:
			newUser.SetBio(message);
			i++;
			break;
		case 3:
			newUser.SetBirthday(message);
			i++;
			break;
		case 4:
			newUser.SetWebsite(message);
			i++;
			break;
		case 5:
			newUser.SetLocation(message);
			i++;
			break;
		}
	}
	if (isTaken == false)
	{
		UserService userService;
		userService.AddUser(newUser.GetUsername(), newUser.GetBirthday(), newUser.GetName(), newUser.GetBio(), newUser.GetWebsite(), newUser.GetLocation());
	}
}

std::string Twitter::RecieveString() const
{
	std::array<char, 512> receiveBuffer;
	int revieved;
	std::string recieved;
	this->m_client->Receive(receiveBuffer.data(), receiveBuffer.size(), revieved);

	std::copy(receiveBuffer.begin(), receiveBuffer.begin() + revieved, std::back_inserter(recieved));

	return recieved;
}

void Twitter::operator()(TcpSocket& client, Logger& log)
{
	this->m_client = std::make_shared<TcpSocket>(client);
	this->log = &log;
	this->m_isConnected = true;
	while (true)
	{
		// receive
		std::string recieved;
		try {
			recieved = this->RecieveString();
		}
		catch (std::exception e)
		{
			this->log->LocI(Logger::Level::ERROR, "Receive error:", e.what());
			return;
		}
		std::cout << recieved << ' ';
		uint16_t aux = static_cast<uint16_t>(recieved.at(0));
		std::cout << aux << '\n';
		Features::Network feature = static_cast<Features::Network>(aux);
		switch (feature)
		{
		case Features::Register:
			this->log->LocI(Logger::Level::INFO, "Registered user");
			RegisterMethod();
			break;
		case Features::Login:
			this->log->LocI(Logger::Level::INFO, "Login");
			LoginMethod();
			break;
		case Features::MakePost:
			this->log->LocI(Logger::Level::INFO, "Added post");
			MakePostMethod();
			break;
		case Features::ShowFollowers:
			break;
		case Features::Like:
			break;
		case Features::Exit:
			this->log->LocI(Logger::Level::INFO, "Client closed");
			client.~TcpSocket();
			m_isConnected = false;
			break;
		case Features::AddFriend:
			this->AddFriendMethod();
			break;
		case Features::Profile:
			this->MakePriorityQueue();
			break;
		case Features::NextPost:
			this->ShowNextPost();
			break;
		case Features::PreviousPost:
			this->ShowPreviousPost();
			break;
		case Features::ProfileNextPost:
			this->ProfileShowNextPost();
			break;
		case Features::ProfilePreviousPost:
			this->ProfilShowPreviousPost();
			break;
		case Features::Refresh:
			this->MakeFeedPriorityQueue();
			break;
		default:
			std::cout << "Nu merge";
			break;
			//
		}
		if (m_isConnected == false)
			break;

	}
}

void Twitter::MakePriorityQueue()
{
	TweetService tweets;
	while (this->m_priorityQueue.Size() > 0)
		this->m_priorityQueue.ExtractMax();
	std::string postari;
	std::vector<std::string> date = tweets.GetDate(m_currentUser);
	std::vector<std::string> time = tweets.GetTime(m_currentUser);
	if (time.size() == 0)
	{
		std::string message = "You have no posts!";
		this->m_client->Send(message.c_str(), message.size());
	}
	else
	{
		if(time.size() > 0)
			for (int i = 0; i < time.size(); i++)
			{
				postari += date[i];
				postari += time[i];
				m_profilePriorityQueue.Insert(postari);
			}
		else
		{
			std::string message = "You have no posts";
			this->m_client->Send(message.c_str(), message.size());
			return;
		}
		std::string firstPost = m_profilePriorityQueue.GetMaxElement();
		std::string time2 = "";
		for (int i = 8; i < firstPost.size(); i++)
			time2 += firstPost[i];

		std::string post = tweets.GetTweet(time2);
		try
		{
			this->m_client->Send(post.c_str(), post.size());
		}
		catch(std::exception e)
		{
			std::cout << "error" << e.what();
		}
	}
}

void Twitter::MakeFeedPriorityQueue()
{
	TweetService tweet;
	FriendsService friendsService;
	while (this->m_priorityQueue.Size() > 0)
		this->m_priorityQueue.ExtractMax();
	std::vector<std::string> friendList = friendsService.GetFriendsList(m_currentUser);

	if (friendList.size() == 0)
	{
		std::string message = "You have no friends!";
		this->m_client->Send(message.c_str(), message.size());
	}
	else
	{
		for (auto x : friendList)
		{
			std::string postari = "";
			std::vector<std::string> date = tweet.GetDate(x);
			std::vector<std::string> time = tweet.GetTime(x);
			if(time.size() > 0)
				for (int i = 0; i < time.size(); i++)
				{
					postari = "";
					postari += date[i];
					postari += time[i];
					m_priorityQueue.Insert(postari);
				}
			else
			{
				std::string message = "Your friends have no posts";
				this->m_client->Send(message.c_str(), message.size());
				return;
			}
		}
		std::string firstPost = m_priorityQueue.GetMaxElement();
		std::string time = "";
		for (int i = 8; i < firstPost.size(); i++)
			time += firstPost[i];

		std::string post = tweet.GetTweet(time);
		this->m_client->Send(post.c_str(), post.size());
	}
}

void Twitter::ShowNextPost()
{
	if (m_priorityQueue.Size() == 1 || m_priorityQueue.Size() == 0)
	{
		std::string message = "There are no other posts";
		this->m_client->Send(message.c_str(), message.size());
	}
	else
	{
		TweetService tweet;
		std::string oldPost = m_priorityQueue.GetMaxElement();
		m_oldPosts.push(oldPost);

		m_priorityQueue.ExtractMax();

		std::string currentPost = m_priorityQueue.GetMaxElement();

		std::string time = "";
		for (int i = 8; i < currentPost.size(); i++)
			time += currentPost[i];

		std::string post = tweet.GetTweet(time);

		this->m_client->Send(post.c_str(), post.size());
	}
}

void Twitter::ShowPreviousPost()
{
	if (m_oldPosts.empty())
	{
		std::string message = "There are no other posts";
		this->m_client->Send(message.c_str(), message.size());
	}
	else
	{
		TweetService tweet;

		std::string currentPost = m_oldPosts.top();
		m_priorityQueue.Insert(currentPost);

		m_oldPosts.pop();

		std::string time = "";
		for (int i = 8; i < currentPost.size(); i++)
			time += currentPost[i];

		std::string post = tweet.GetTweet(time);

		this->m_client->Send(post.c_str(), post.size());

	}
}

void Twitter::ProfileShowNextPost()
{
	if (m_profilePriorityQueue.Size() == 1 || m_profilePriorityQueue.Size() == 0)
	{
		std::string message = "There are no other posts";
		this->m_client->Send(message.c_str(), message.size());
	}
	else
	{
		TweetService tweet;
		std::string oldPost = m_profilePriorityQueue.GetMaxElement();
		m_profileOldPosts.push(oldPost);

		m_profilePriorityQueue.ExtractMax();

		std::string currentPost = m_profilePriorityQueue.GetMaxElement();

		std::string time = "";
		for (int i = 8; i < currentPost.size(); i++)
			time += currentPost[i];

		std::string post = tweet.GetTweet(time);

		this->m_client->Send(post.c_str(), post.size());
	}
}

void Twitter::ProfilShowPreviousPost()
{
	if (m_profileOldPosts.empty())
	{
		std::string message = "There are no other posts";
		this->m_client->Send(message.c_str(), message.size());
	}
	else
	{
		TweetService tweet;

		std::string currentPost = m_profileOldPosts.top();
		m_profilePriorityQueue.Insert(currentPost);

		m_profileOldPosts.pop();

		std::string time = "";
		for (int i = 8; i < currentPost.size(); i++)
			time += currentPost[i];

		std::string post = tweet.GetTweet(time);

		this->m_client->Send(post.c_str(), post.size());
	}
}
