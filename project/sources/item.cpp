#include "item.h"

Item::Item(const string& a) : name(a), path(DEFAULTPIC), id(0) {}

Item::Item(const Item& other) : name(other.name), path(other.path) {}

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

void Item::setName(const string& _n) {
    name = _n;
}

void Item::setPath(const string& _path) {
    path = _path;
}

string Item::description() const {
    string s = getName();
    return s;
}

Item::~Item() {}
