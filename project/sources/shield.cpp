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

    return Shield(_effect, _name, _path);
}

QJsonObject Shield::toJson() const {
    QJsonObject obj;
    // obj["id"] = static_cast<int>(getID());
    obj["name"] = QString::fromStdString(getName());
    obj["path"] = QString::fromStdString(getItemPath());
    obj["effect"] = static_cast<int>(getDEF());
    return obj;
}
