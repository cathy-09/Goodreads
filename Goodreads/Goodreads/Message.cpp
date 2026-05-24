#include "Message.h"

bool Message::isJobOffer() const
{
	return type == MessageType::JobOffer;
}

bool Message::isFollowNotice() const
{
	return type == MessageType::FollowNotice;
}

bool Message::isBookNotice() const
{
	return type == MessageType::BookNotice;
}

bool Message::isLikedNotice() const
{
	return type == MessageType::FollowNotice;
}

bool Message::isFriendNotice() const
{
	return type == MessageType::FriendNotice;
}