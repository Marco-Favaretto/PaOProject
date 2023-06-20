#include "weapon.h"

Weapon::Weapon(u_int _atk, w_type _tipo, string _name, string _path) 
    : Item(_name, _path), atk(_atk), tipo(_tipo) {}

void Weapon::effect() {}

Weapon::~Weapon() {}