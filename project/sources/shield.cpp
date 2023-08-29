#include "shield.h"
using namespace shield;
using namespace shield::Tipo;


Shield::Shield(tipo _t, u_int _def, const string& _name)
    : Weapon(_def, _name), t(_t) {
    if(!pathCorrectness()) pathCorrect();
}

Shield::Shield(const Shield& other) : Weapon(other), t(other.t) {}

Shield* Shield::clone() const { return new Shield(*this); }

tipo Shield::intToTipo(int n) {
    tipo _t = LEGNO;
    switch(n) {
    case 0:
        _t = LEGNO;
        break;
    case 1:
        _t = MEDIO;
        break;
    case 2:
        _t = GRANDE;
        break;
    }
    return _t;
}

bool Shield::pathCorrectness() const {
    bool ok = false;
    switch(t) {
    case LEGNO:
        ok = SCUDOLEGNO_PIC == getItemPath();
        break;
    case MEDIO:
        ok = SCUDOMEDIO_PIC == getItemPath();
        break;
    case GRANDE:
        ok = SCUDOGRANDE_PIC == getItemPath();
        break;
    }
    return ok;
}

void Shield::pathCorrect() {
    switch(t) {
    case LEGNO:
        setPath(SCUDOLEGNO_PIC);
        break;
    case MEDIO:
        setPath(SCUDOMEDIO_PIC);
        break;
    case GRANDE:
        setPath(SCUDOGRANDE_PIC);
        break;
    }
}

string Shield::description() const {
    string s = getName() +  " def: " + std::to_string(getDEF()) + "%";
    return s;
}

unsigned int Shield::getDEF() const {
    return Weapon::getValue();
}

Shield Shield::fromJson(const QJsonObject &json) {

    int _effect =0;
    tipo _t = LEGNO;
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

    return Shield(_t, _effect, _name);
}

QJsonObject Shield::toJson() const {
    QJsonObject obj;
    obj["name"] = QString::fromStdString(getName());
    obj["tipo"] = t;
    obj["effect"] = static_cast<int>(getDEF());
    return obj;
}
