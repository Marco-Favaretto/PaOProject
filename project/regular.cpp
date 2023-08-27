#include "regular.h"

Regular::Regular(u_int _atk, string _name, string _path)
    : Weapon(_atk, _name, _path) {}

Regular::Regular(const Regular& other) : Weapon(other) {}

Regular* Regular::clone() const { return new Regular(*this); }

string Regular::description() const {
    string s = " atk: " + std::to_string(getATK());
    return s;
}

unsigned int Regular::getATK() const {
    return Weapon::getValue();
}


Regular Regular::fromJson(const QJsonObject &json) {
    Regular w;
    if (const QJsonValue v = json["id"]; v.isDouble())
            w.setID(v.toInt());
    if (const QJsonValue v = json["name"]; v.isString())
        w.setName(v.toString().toStdString());
    if (const QJsonValue v = json["path"]; v.isString())
        w.setPath(v.toString().toStdString());
    if (const QJsonValue v = json["effect"]; v.isDouble())
        w.setValue(v.toInt());
    return w;
}

QJsonObject Regular::toJson() const {
    QJsonObject obj;
    obj["id"] = static_cast<int>(getID());
    obj["name"] = QString::fromStdString(getName());
    obj["path"] = QString::fromStdString(getItemPath());
    obj["effect"] = static_cast<int>(getATK());
    return obj;
}
