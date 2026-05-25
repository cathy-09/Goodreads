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
    bool isReadMessage = false;
public:
    Message() = default;
    Message(const std::string& from, const std::string& content, MessageType type = MessageType::Regular);
    const std::string& getFrom() const;
    const std::string& getContent() const;
    MessageType getType() const;
    bool isRead() const;
    void markRead();
    bool isJobOffer() const;
    bool isFollowNotice() const; 
    bool isBookNotice() const;
    bool isLikedNotice() const;
    bool isFriendNotice() const;
    static std::string typeToString(MessageType type);
    static MessageType typeFromString(const std::string& string);
};

