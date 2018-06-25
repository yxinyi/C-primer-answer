#pragma once
#include "Folder.h"
#include <string>
#include <set>

class Folder;
class Message {
friend void swap(Message& lhs, Message& rhs);
public:
    explicit Message(const std::string& str = ""):contents(str){}
    Message(const Message&);
    Message(Message&& m);
    Message& operator=(Message&& m);


    Message& operator=(Message&);
    ~Message();
    void save(Folder&);
    void remove(Folder&);
    void insertFolder(Folder *);
    void eraseFolder(Folder *);
private:
    std::string contents;
    std::set<Folder* > folders;
    void add_to_Folders(Message&);
    void remove_from_Folders();


};

