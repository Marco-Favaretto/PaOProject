#include "potion.h"

Potion::Potion(tipo _t, std::string name, std::string pic) : Consumable(0, name, pic), t(_t) {}

