#include "weapon.h"

Weapon::Weapon(u_int _atk, string _name, string _path)
    : Item(_name, _path), atk(_atk), equip(false) {}

Weapon::Weapon(const Weapon& other) : Item(other), atk(other.atk), equip(other.equip) {}

bool Weapon::isEquipped() const {
    return equip;
}

unsigned int Weapon::getValue() const {
    return atk;
}

string Weapon::description() const {
    string s = Item::description();
    return s;
}

void Weapon::effect() {
    equip = true;
    emit statSignal(atk);
}

Weapon::~Weapon() {}