#include "consumable.h"

Consumable::Consumable(int c, string a, string b) : Item(a, b), hpEffect(c) {}

Consumable::Consumable(const Consumable& other) : Item(other), hpEffect(other.hpEffect) {}

Consumable* Consumable::clone() const {
    return new Consumable(*this);
}

void Consumable::effect() {
    emit effectSignal(getEffect());
}

Consumable::~Consumable() {}

int Consumable::getEffect() const {
    return hpEffect;
}

string Consumable::description() const {
    string s = getEffect() > 0 ? "somma " : "sottrae "; 
    s += std::to_string(getEffect()) + " HP al Player";
    return s;
}