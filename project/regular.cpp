#include "regular.h"

Regular::Regular(u_int _atk, string _name, string _path)
    : Weapon(_atk, _name, _path) {}

Regular::Regular(const Regular& other) : Weapon(other) {}

Regular* Regular::clone() const { return new Regular(*this); }

string Regular::description() const {
    string s = " atk: " + std::to_string(getATK());
    return s;
}

unsigned int Regular::getATK() const {
    return Weapon::getValue();
}