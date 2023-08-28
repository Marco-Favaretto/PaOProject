#include "item.h"

Item::Item(string a, string b) : name(a), path(b) {
    id = 0;
}

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

void Item::setName(std::string _n) {
    name = _n;
}

void Item::setPath(string _path) {
    path = _path;
}

string Item::description() const {
    string s = getName();
    return s;
}

Item::~Item() {}
