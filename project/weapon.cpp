#include "weapon.h"

Weapon::Weapon(u_int _atk, string _name, string _path)
    : Item(_name, _path), atk(_atk), equip(false) {}

void Weapon::effect() { equip = true; emit statSignal(atk); }

Weapon::isEquipped() { return equip; }

Weapon::~Weapon() {}
