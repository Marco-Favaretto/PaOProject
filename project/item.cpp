#include "item.h"

Item::Item(string a, string b) : name(a), path(b) {}

string Item::getName() const {
    return name;
}

Item::~Item() {}
