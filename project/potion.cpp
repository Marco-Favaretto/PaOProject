#include "potion.h"
using namespace potion;
using namespace potion::classe;

Potion::Potion(tipo _t, std::string name, std::string pic) : Consumable(0, name, pic), t(_t) {}

tipo Potion::getType() const {
    return t;
}
