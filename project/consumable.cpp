#include "consumable.h"

Consumable::Consumable(string a, string b, int c) : Item(a, b), hpEffect(c) {}

void Consumable::effect() {}

Consumable::~Consumable() {}