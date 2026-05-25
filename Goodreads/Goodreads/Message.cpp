#include "Message.h"

Message::Message(const std::string& from, const std::string& content, MessageType type) : from(from), content(content), type(type)
{

}

const std::string& Message::getFrom() const
{
	return from;
}

const std::string& Message::getContent() const
{
	return content;
}

MessageType Message::getType() const
{
	return type;
}

bool Message::isRead() const
{
	return isReadMessage;
}

void Message::markRead()
{
	isReadMessage = true;
}

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
	return type == MessageType::LikedNotice;
}

bool Message::isFriendNotice() const
{
	return type == MessageType::FriendNotice;
}

std::string Message::typeToString(MessageType type)
{
	if (type == MessageType::Regular)
	{
		return "Regular";
	}
	if (type == MessageType::FollowNotice)
	{
		return "FollowNotice";
	}
	if (type == MessageType::BookNotice)
	{
		return "BookNotice";
	}
	if (type == MessageType::JobOffer)
	{
		return "JobOffer";
	}
	if (type == MessageType::LikedNotice)
	{
		return "LikedNotice";
	}
	if (type == MessageType::FriendNotice)
	{
		return "FriendNotice";
	}
	return "Regular";
}

MessageType Message::typeFromString(const std::string& string)
{
	if (string == "FollowNotice")
	{
		return MessageType::FollowNotice;
	}
	if (string == "BookNotice")
	{
		return MessageType::BookNotice;
	}
	if (string == "JobOffer")
	{
		return MessageType::JobOffer;
	}
	if (string == "LikedNotice")
	{
		return MessageType::LikedNotice;
	}
	if (string == "FriendNotice")
	{
		return MessageType::FriendNotice;
	}
	return MessageType::Regular;
}
