#include "Message.h"

void Message::save(Folder& f){
    folders.insert(&f);
    f.addMsg(this);
}
void Message::remove(Folder& f) {
    folders.erase(&f);
    f.remMsg(this);
}

void Message::add_to_Folders(Message& m){
    for(auto f: m.folders){
        f->addMsg(&m);
    }
}

Message::Message(const Message& m):contents(m.contents),folders(m.folders){
    add_to_Folders(*this);
}

void Message::remove_from_Folders(){
    for(auto f: folders){
        f->remMsg(this);
    }
}

Message::~Message(){
    remove_from_Folders();
}

Message& Message::operator=(Message & m){
    remove_from_Folders();
    contents = m.contents;
    folders = m.folders;
    add_to_Folders(m);
    return *this;
}


void swap(Message& lhs, Message& rhs){
    for(auto f:lhs.folders){
        f->remMsg(&lhs);
    }
    for (auto f : rhs.folders) {
        f->remMsg(&rhs);
    }
    std::swap(lhs.contents, rhs.contents);
    std::swap(lhs.folders, rhs.folders);
    for(auto f:lhs.folders){
        f->addMsg(&lhs);
    }for (auto f : rhs.folders) {
        f->addMsg(&rhs);
    }
}
void Message::insertFolder(Folder * f) {
    this->folders.insert(f);
}
void Message::eraseFolder(Folder * f) {
    this->folders.erase(f);
}

Message::Message(Message&& m) :contents(std::move(m.contents)) {
    folders = std::move(m.folders);
    for (auto f : folders) {
        f->remMsg(&m);
        f->addMsg(this);
    }
    m.folders.clear();
};
Message& Message::operator=(Message&& m) {
    if (this != &m) {
        folders = std::move(m.folders);
        for (auto f : folders) {
            f->remMsg(&m);
            f->addMsg(this);
        }
        m.folders.clear();
    }
    return *this;
};