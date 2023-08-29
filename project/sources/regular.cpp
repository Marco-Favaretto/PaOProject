#include "regular.h"
using namespace regular;
using namespace regular::Tipo;

tipo Regular::intToTipo(int n) {
    tipo _t = SPADA;
    switch(n) {
    case 0:
        _t = SPADA;
        break;
    case 1:
        _t = STOCCO;
        break;
    case 2:
        _t = ASCIA;
        break;
    case 3:
        _t = MAZZA;
        break;
    }
    return _t;
}

bool Regular::pathCorrectness() const {
    bool ok = false;
    switch(t) {
    case SPADA:
        ok = SPADA_PIC == getItemPath();
        break;
    case STOCCO:
        ok = STOCCO_PIC == getItemPath();
        break;
    case ASCIA:
        ok = ASCIA_PIC == getItemPath();
        break;
    case MAZZA:
        ok = MAZZA_PIC == getItemPath();
        break;
    }
    return ok;
}

void Regular::pathCorrect() {
    switch(t) {
    case SPADA:
        setPath(SPADA_PIC);
        break;
    case STOCCO:
        setPath(STOCCO_PIC);
        break;
    case ASCIA:
        setPath(ASCIA_PIC);
        break;
    case MAZZA:
        setPath(MAZZA_PIC);
        break;
    }
}

Regular::Regular(tipo _t, u_int _atk, const string& _name)
    : Weapon(_atk, _name), t(_t) {
    if(!pathCorrectness()) pathCorrect();
}

Regular::Regular(const Regular& other) : Weapon(other), t(other.t) {}

Regular* Regular::clone() const { return new Regular(*this); }

string Regular::description() const {
    string s = getName() +  " atk: " + std::to_string(getATK());
    return s;
}

unsigned int Regular::getATK() const {
    return Weapon::getValue();
}


Regular Regular::fromJson(const QJsonObject &json) {

    int _effect =0;
    tipo _t = SPADA;
    string _name = "", _path = "";

    const QJsonValue vname = json["name"];
    if (vname.isString())
        _name = vname.toString().toStdString();

    const QJsonValue vtipo = json["tipo"];
    if (vtipo.isDouble())
        _t = intToTipo(vtipo.toInt());

    const QJsonValue veffect = json["effect"];
    if (veffect.isDouble())
        _effect = veffect.toInt();

    return Regular(_t, _effect, _name);
}

QJsonObject Regular::toJson() const {
    QJsonObject obj;
    obj["name"] = QString::fromStdString(getName());
    obj["tipo"] = t;
    obj["effect"] = static_cast<int>(getATK());
    return obj;
}
