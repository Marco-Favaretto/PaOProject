#include "overTime.h"
using namespace overtime;
using namespace overtime::classe;

#include <iomanip>
#include <sstream>

overTime::overTime() : Consumable(), timer(new QTimer()), counter(-1), t(POISON) {}

overTime::overTime(tipo _t, int hp, int c, string _name, string _path)
    : Consumable(hp, _name, _path),
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

//overTime::~overTime() {
//    delete timer;
//}

bool overTime::pathCorrectness() const {
    switch(t) {
        case POISON:
            return getItemPath() == POISON_PIC;
            break;
        case TOXIC:
            return getItemPath() == TOXIC_PIC;
            break;
    }
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
    switch(i) {
    case 0:
        return POISON;
        break;
    case 1:
        return TOXIC;
        break;
    }
}

overTime overTime::fromJson(const QJsonObject &json) {
    
    // int _id = 0, _timer = 0,
    int _effect =0, _counter = -1;
    tipo _t = POISON;
//    bool _st = false;
    string _name = "", _path = "";

    // if (const QJsonValue v = json["id"]; v.isDouble())
    //         _id = v.toInt();
    
    if (const QJsonValue v = json["name"]; v.isString())
            _name = v.toString().toStdString();
    
    if (const QJsonValue v = json["path"]; v.isString())
            _path = v.toString().toStdString();
    
    if (const QJsonValue v = json["effect"]; v.isDouble())
            _effect = v.toInt();
    
//    if (const QJsonValue v = json["timer"]; v.isDouble())
//            _timer = v.toInt();
    
    if (const QJsonValue v = json["tipo"]; v.isDouble())
            _t = intToTipo(v.toInt());

    if (const QJsonValue v = json["counter"]; v.isDouble())
            _counter = intToTipo(v.toInt());
    
//    if (const QJsonValue v = json["status"]; v.isBool())
//            _st = v.toBool();
   
   return overTime(_t, _effect, _counter, _name, _path);
}

QJsonObject overTime::toJson() const {
    QJsonObject obj;
    // obj["id"] = static_cast<int>(getID());
    obj["name"] = QString::fromStdString(getName());
    obj["path"] = QString::fromStdString(getItemPath());
    obj["effect"] = getEffect();
//    obj["timer"] = timer->interval();
    obj["counter"] = counter;
    obj["tipo"] = t;
//    obj["status"] = status;
    return obj;
}
