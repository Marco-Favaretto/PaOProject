#include "consumable.h"

Consumable::Consumable(int c, string a, string b) : Item(a, b), hpEffect(c) {}

Consumable::Consumable(const Consumable& other) : Item(other), hpEffect(other.hpEffect) {}

Consumable* Consumable::clone() const {
    return new Consumable(*this);
}

void Consumable::setEffect(int n) {
    hpEffect = n;
}

Consumable Consumable::fromJson(const QJsonObject &json) {
    Consumable c;
    if (const QJsonValue v = json["id"]; v.isDouble())
            c.setID(v.toInt());
    if (const QJsonValue v = json["name"]; v.isString())
        c.setName(v.toString().toStdString());
    if (const QJsonValue v = json["path"]; v.isString())
        c.setPath(v.toString().toStdString());
    if (const QJsonValue v = json["effect"]; v.isDouble())
        c.hpEffect = v.toInt();
    return c;
}

QJsonObject Consumable::toJson() const {
    QJsonObject obj;
    obj["id"] = static_cast<int>(getID());
    obj["name"] = QString::fromStdString(getName());
    obj["path"] = QString::fromStdString(getItemPath());
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
