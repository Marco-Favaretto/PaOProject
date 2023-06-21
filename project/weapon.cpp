#include "weapon.h"

Weapon::Weapon(w_type _tipo, u_int _atk, string _name, string _path)
    : Item(_name, _path), tipo(_tipo), atk(_atk) {}

void Weapon::effect() {}

Weapon::~Weapon() {}
