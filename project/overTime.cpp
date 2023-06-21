#include "overTime.h"

overTime::overTime(string _name, string _path, u_int time)
    : Consumable(_name, _path), timer(new QTimer()) {
    timer->setInterval(time);
    connect(timer, SIGNAL(timeout()), this, SLOT(effect()));
    timer->start();
    status = true;
}

bool overTime::isActive() const {
    return status;
}

overTime::~overTime() {
    delete timer;
}

void overTime::effect() {}

void overTime::stopOT() {
    status = false;
    timer->stop();
}
