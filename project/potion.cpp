#include "potion.h"
using namespace potion;
using namespace potion::classe;

Potion::Potion(tipo _t, std::string name, std::string pic) : Consumable(0, name, pic), t(_t) {
    if(!pathCorrectness()) pathCorrect();
}

tipo Potion::getType() const {
    return t;
}

bool Potion::pathCorrectness() const {
    switch(t) {
        case POISON:
            return getItemPath() == POTIONP_PIC;
            break;
        case TOXIC:
            return getItemPath() == POTIONT_PIC;
            break;
    }
}

void Potion::pathCorrect() {
    switch(t) {
        case POISON:
            setPath(POTIONP_PIC);
            break;
        case TOXIC:
            setPath(POTIONT_PIC);
            break;
    }
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
