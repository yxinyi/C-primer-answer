#include "Folder.h"


void Folder::remMsg(Message * m) {
    this->messages.erase(m);
}
void Folder::addMsg(Message * m) {
    messages.insert(m);
}