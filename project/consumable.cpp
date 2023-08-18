#include "consumable.h"

Consumable::Consumable(string a, string b, int c) : Item(a, b), hpEffect(c) {}

int Consumable::effect() {}

Consumable::~Consumable() {}
