#include "consumable.h"

Consumable::Consumable(int c, string a, string b) : Item(a, b), hpEffect(c) {}

void Consumable::effect() {
    emit effectSignal(getEffect());
}

Consumable::~Consumable() {}

int Consumable::getEffect() const {
    return hpEffect;
}
