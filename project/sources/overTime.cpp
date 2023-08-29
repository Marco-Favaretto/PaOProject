#include "overTime.h"
using namespace overtime;
using namespace overtime::classe;

// importazioni per stringa con precisione .00
#include <iomanip>
#include <sstream>

overTime::overTime() : Consumable(), timer(new QTimer()), counter(-1), t(POISON) {}

overTime::overTime(tipo _t, int hp, int c, const string& _name)
    : Consumable(hp, _name),
      timer(new QTimer()), counter(c), t(_t) {
    if(t == POISON) timer->setInterval(STDTIMERPOISON);
    else timer->setInterval(STDTIMERTOXIC);

    if(c == 0) counter = INFCOUNTER;
    if(c > MAXCOUNTER) counter = MAXCOUNTER;
    status = false;
    if(!pathCorrectness()) pathCorrect();
}

void overTime::setTimer(int i) {
    timer->setInterval(i);
}

overTime::overTime(const overTime& other) : Consumable(other), timer(other.timer), counter(other.counter), t(other.t) {}

overTime* overTime::clone() const { return new overTime(*this); }

bool overTime::isActive() const {
    return status;
}

double overTime::getTimer() const {
    return timer->interval() / 1000.00;
}

string overTime::description() const {
    string s = Consumable::description() + " ogni ";
    std::stringstream stream;
    stream << std::fixed << std::setprecision(1) << getTimer();
    s += stream.str() + "s";
    if(counter != -1) s += " per " + std::to_string(counter) + " volte";
    return s;
}

overtime::tipo overTime::getType() const {
    return t;
}

bool overTime::pathCorrectness() const {
    bool ok = false;
    switch(t) {
        case POISON:
            ok = getItemPath() == POISON_PIC;
            break;
        case TOXIC:
            ok = getItemPath() == TOXIC_PIC;
            break;
    }
    return ok;
}

void overTime::pathCorrect() {
    switch(t) {
        case POISON:
            setPath(POISON_PIC);
            break;
        case TOXIC:
            setPath(TOXIC_PIC);
            break;
    }
}

void overTime::effect() {
    if(counter == 0) {
        stopOT();
    }
    else {
        counter--;
        emit effectSignal(getEffect());
    }
}

void overTime::stopOT() {
    status = false;
    timer->stop();
    emit over(this);
}

void overTime::startOT(){
    connect(timer, SIGNAL(timeout()), this, SLOT(effect()));
    timer->start();
    status = true;
}

overtime::tipo overTime::intToTipo(int i) {
    overtime::tipo _t = POISON;
    switch(i) {
    case 0:
        _t = POISON;
        break;
    case 1:
        _t = TOXIC;
        break;
    }
    return _t;
}

overTime overTime::fromJson(const QJsonObject &json) {
    
    int _effect =0, _counter = -1;
    tipo _t = POISON;
    string _name = "", _path = "";
    
    if (const QJsonValue v = json["name"]; v.isString())
            _name = v.toString().toStdString();
    
    if (const QJsonValue v = json["effect"]; v.isDouble())
            _effect = v.toInt();
    
    if (const QJsonValue v = json["tipo"]; v.isDouble())
            _t = intToTipo(v.toInt());

    if (const QJsonValue v = json["counter"]; v.isDouble())
            _counter = intToTipo(v.toInt());
   
   return overTime(_t, _effect, _counter, _name);
}

QJsonObject overTime::toJson() const {
    QJsonObject obj;

    obj["name"] = QString::fromStdString(getName());
    obj["effect"] = getEffect();
    obj["counter"] = counter;
    obj["tipo"] = t;
    
    return obj;
}
