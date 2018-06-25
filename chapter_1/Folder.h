#pragma once
#include "Message.h"
#include <set>

class Message;
class Folder{
public:
    void remMsg(Message* );
    void addMsg(Message* );
private:
    std::set<Message* > messages;
};
