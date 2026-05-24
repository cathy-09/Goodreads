#pragma once
#include <string>

enum class MessageType
{
    Regular,
    LikedNotice,
    FollowNotice,
    FriendNotice,
    BookNotice,
    JobOffer 
};

class Message
{
private:
    std::string from;
    std::string content;
    MessageType type = MessageType::Regular;
    bool isRead = false;
public:
    bool isJobOffer() const;
    bool isFollowNotice() const; 
    bool isBookNotice() const;
    bool isLikedNotice() const;
    bool isFriendNotice() const;
};

