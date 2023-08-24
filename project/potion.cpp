#include "potion.h"
using namespace potion;
using namespace potion::classe;

Potion::Potion(tipo _t, std::string name, std::string pic) : Consumable(0, name, pic), t(_t) {}

tipo Potion::getType() const {
    return t;
}

string Potion::getTypeString() const {
    switch(t) {
        case POISON:
            return "POISON";
        break;
        case TOXIC:
            return "TOXIC";
        break;
    }
}

string Potion::description() const {
    string s = " cures from " + getTypeString() + " status";
    return s;
}
