#include "shield.h"

Shield::Shield(u_int _def, string _name, string _path)
    : Weapon(_def, _name, _path) {}

Shield::Shield(const Shield& other) : Weapon(other) {}

Shield* Shield::clone() const { return new Shield(*this); }

string Shield::description() const {
    string s = " def: " + std::to_string(getDEF()) + "%";
    return s;
}

unsigned int Shield::getDEF() const {
    return Weapon::getValue();
}

Shield Shield::fromJson(const QJsonObject &json) {
    Shield s;
    if (const QJsonValue v = json["id"]; v.isDouble())
            s.setID(v.toInt());
    if (const QJsonValue v = json["name"]; v.isString())
        s.setName(v.toString().toStdString());
    if (const QJsonValue v = json["path"]; v.isString())
        s.setPath(v.toString().toStdString());
    if (const QJsonValue v = json["effect"]; v.isDouble())
        s.setValue(v.toInt());
    return s;
}

QJsonObject Shield::toJson() const {
    QJsonObject obj;
    obj["id"] = static_cast<int>(getID());
    obj["name"] = QString::fromStdString(getName());
    obj["path"] = QString::fromStdString(getItemPath());
    obj["effect"] = static_cast<int>(getDEF());
    return obj;
}
