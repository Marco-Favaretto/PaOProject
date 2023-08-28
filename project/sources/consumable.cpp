#include "consumable.h"

Consumable::Consumable(int c, string a, string b) : Item(a, b), hpEffect(c) {}

Consumable::Consumable(const Consumable& other) : Item(other), hpEffect(other.hpEffect) {}

Consumable* Consumable::clone() const {
    return new Consumable(*this);
}

void Consumable::setEffect(int n) {
    hpEffect = n;
}

#include <QCborValue>

Consumable Consumable::fromJson(const QJsonObject &json) {

    // int _id = 0,
    int _effect =0;
    string _name = "", _path = "";

    // const QJsonValue vid = json["id"];
    // if (vid.isDouble())
    //         _id = vid.toInt();

    const QJsonValue vname = json["name"];
    if (vname.isString())
        _name = vname.toString().toStdString();

    const QJsonValue vpath = json["path"];
    if (vpath.isString())
        _path = vpath.toString().toStdString();

    const QJsonValue veffect = json["effect"];
    if (veffect.isDouble())
        _effect = veffect.toInt();

    return Consumable(_effect, _name, _path);
}

QJsonObject Consumable::toJson() const {
    QJsonObject obj;
    // obj["id"] = static_cast<int>(getID());
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
