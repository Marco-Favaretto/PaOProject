#include "shield.h"
using namespace shield;
using namespace shield::Tipo;


Shield::Shield(tipo _t, u_int _def, const string& _name, const string& _path)
    : Weapon(_def, _name, _path), t(_t) {
    if(!pathCorrectness()) pathCorrect();
}

Shield::Shield(const Shield& other) : Weapon(other), t(other.t) {}

Shield* Shield::clone() const { return new Shield(*this); }

tipo Shield::intToTipo(int n)
{
    switch(n) {
    case 0:
        return LEGNO;
        break;
    case 1:
        return MEDIO;
        break;
    case 2:
        return GRANDE;
        break;
    }
}

bool Shield::pathCorrectness() const {
    switch(t) {
    case LEGNO:
        return SCUDOLEGNO_PIC == getItemPath();
        break;
    case MEDIO:
        return SCUDOMEDIO_PIC == getItemPath();
        break;
    case GRANDE:
        return SCUDOGRANDE_PIC == getItemPath();
        break;
    }
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

    const QJsonValue vpath = json["path"];
    if (vpath.isString())
        _path = vpath.toString().toStdString();

     const QJsonValue vtipo = json["tipo"];
     if (vtipo.isDouble())
             _t = intToTipo(vtipo.toInt());

    const QJsonValue veffect = json["effect"];
    if (veffect.isDouble())
        _effect = veffect.toInt();

    return Shield(_t, _effect, _name, _path);
}

QJsonObject Shield::toJson() const {
    QJsonObject obj;
    obj["name"] = QString::fromStdString(getName());
    obj["path"] = QString::fromStdString(getItemPath());
    obj["tipo"] = t;
    obj["effect"] = static_cast<int>(getDEF());
    return obj;
}
