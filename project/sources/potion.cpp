#include "potion.h"
using namespace potion;
using namespace potion::classe;

Potion::Potion() : Consumable(), t(POISON) {}

Potion::Potion(tipo _t, const std::string& name) : Consumable(0, name), t(_t) {
    if(!pathCorrectness()) pathCorrect();
}

Potion::Potion(const Potion& other) : Consumable(other), t(other.t) {}

Potion* Potion::clone() const { return new Potion(*this); }

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

potion::tipo Potion::intToTipo(int i) {
    switch(i) {
    case 0:
        return POISON;
        break;
    case 1:
        return TOXIC;
        break;
    }
}

Potion Potion::fromJson(const QJsonObject &json) {    
    
    tipo _t = POISON;
    string _name = "", _path = "";
    
    if (const QJsonValue v = json["name"]; v.isString())
            _name = v.toString().toStdString();
    
    if (const QJsonValue v = json["tipo"]; v.isDouble())
            _t = intToTipo(v.toInt());
   
   return Potion(_t, _name);
}

QJsonObject Potion::toJson() const {
    QJsonObject obj;

    obj["name"] = QString::fromStdString(getName());
    obj["effect"] = getEffect();
    obj["tipo"] = t;
    
    return obj;
}
