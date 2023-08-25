#include "item.h"

Item::Item(string a, string b) : name(a), path(b) {
    id = 0;
}

string Item::getName() const {
    return name;
}

string Item::getItemPath() const {
    return path;
}

unsigned int Item::getID() const {
    return id;
}

void Item::setID(unsigned int _id) {
    id = _id;
}

string Item::description() const {
    string s = getName();
    return s;
}

Item::~Item() {}