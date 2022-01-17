#include "Comment.h"

Comment::Comment(Tweet* referenceTweet, std::string text, time_t time) :
	Tweet(text, time),
	m_referenceTweet(referenceTweet)
{
}


void Comment::AddLike()
{
}

void Comment::AddDislike()
{
}
