#include "overTime.h"

overTime::overTime(string _name, string _path, int hp, u_int time, int c)
    : Consumable(_name, _path, hp),
      timer(new QTimer()), counter(c == 0 ? -1 : c) {
    timer->setInterval(time);
    connect(timer, SIGNAL(timeout()), this, SLOT(effect()));
    status = false;
}

bool overTime::isActive() const {
    return status;
}

overTime::~overTime() {
    delete timer;
}

int overTime::effect() {
    if(counter == 0) {
        stopOT();
    }
    else {
        counter--;
        return Consumable::effect();
    }
}

void overTime::stopOT() {
    status = false;
    timer->stop();
    emit over();
}

void overTime::startOT(){
    status = true;
    timer->start();
}
