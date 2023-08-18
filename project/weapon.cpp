#include "weapon.h"

Weapon::Weapon(u_int _atk, string _name, string _path)
    : Item(_name, _path), atk(_atk) {}

int Weapon::effect() { return atk; }

Weapon::~Weapon() {}
