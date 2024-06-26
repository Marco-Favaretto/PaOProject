#include "consumable.h"

Consumable::Consumable(int c, const string& a) : Item(a), hpEffect(c) {
    if(!pathCorrectness()) pathCorrect();
}

Consumable::Consumable(const Consumable& other) : Item(other), hpEffect(other.hpEffect) {}

Consumable* Consumable::clone() const {
    return new Consumable(*this);
}


bool Consumable::pathCorrectness() const {
    return (hpEffect >= 0 && getItemPath() == CURA_PIC) || (hpEffect < 0 && getItemPath() == PASTIGLIA_PIC);
}

void Consumable::pathCorrect() {
    if(hpEffect >= 0) setPath(CURA_PIC);
    else setPath(PASTIGLIA_PIC);
}


void Consumable::setEffect(int n) {
    hpEffect = n;
}

Consumable Consumable::fromJson(const QJsonObject &json) {

    int _effect =0;
    string _name = "", _path = "";

    const QJsonValue vname = json["name"];
    if (vname.isString())
        _name = vname.toString().toStdString();

    const QJsonValue veffect = json["effect"];
    if (veffect.isDouble())
        _effect = veffect.toInt();

    return Consumable(_effect, _name);
}

QJsonObject Consumable::toJson() const {
    QJsonObject obj;
    obj["name"] = QString::fromStdString(getName());
    obj["effect"] = hpEffect;
    return obj;
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
