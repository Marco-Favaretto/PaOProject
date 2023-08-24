#include "shield.h"

Shield::Shield(u_int _def, string _name, string _path)
    : Weapon(_def, _name, _path) {}

string Shield::description() const {
    string s = " def: " + std::to_string(getDEF()) + "%";
    return s;
}

unsigned int Shield::getDEF() const {
    return Weapon::getValue();
}
