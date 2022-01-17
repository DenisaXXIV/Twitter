#pragma once

#include "Tweet.h"

class Retweet:public Tweet
{
public:
	Retweet() = default;
	Retweet(Tweet* referenceTweet, std::string text, time_t time);
	~Retweet();

	Tweet* GetReferenceTweet();

private:
	Tweet* m_referenceTweet;
};

