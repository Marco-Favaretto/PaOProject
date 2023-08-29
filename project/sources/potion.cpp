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
    bool ok = false;
    switch(t) {
        case POISON:
            ok = getItemPath() == POTIONP_PIC;
            break;
        case TOXIC:
            ok = getItemPath() == POTIONT_PIC;
            break;
    }
    return ok;
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
    string s = "";
    switch(t) {
        case POISON:
            s = "POISON";
        break;
        case TOXIC:
            s = "TOXIC";
        break;
    }
    return s;
}

string Potion::description() const {
    string s = " cures from " + getTypeString() + " status";
    return s;
}

potion::tipo Potion::intToTipo(int i) {
    potion::tipo _t = POISON;
    switch(i) {
    case 0:
        _t = POISON;
        break;
    case 1:
        _t = TOXIC;
        break;
    }
    return _t;
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
