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

    return Regular(_effect, _name, _path);
}

QJsonObject Regular::toJson() const {
    QJsonObject obj;
    // obj["id"] = static_cast<int>(getID());
    obj["name"] = QString::fromStdString(getName());
    obj["path"] = QString::fromStdString(getItemPath());
    obj["effect"] = static_cast<int>(getATK());
    return obj;
}
