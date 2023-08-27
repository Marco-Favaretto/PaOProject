#include "shield.h"

Shield::Shield(u_int _def, string _name, string _path)
    : Weapon(_def, _name, _path) {}

Shield::Shield(const Shield& other) : Weapon(other) {}

Shield* Shield::clone() const { return new Shield(*this); }

string Shield::description() const {
    string s = " def: " + std::to_string(getDEF()) + "%";
    return s;
}

unsigned int Shield::getDEF() const {
    return Weapon::getValue();
}