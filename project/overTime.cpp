#include "overTime.h"

#include<iostream>
using std::cout; using std::endl;

overTime::overTime(int hp, u_int time, int c, string _name, string _path)
    : Consumable(hp, _name, _path),
      timer(new QTimer()), counter(c) {
    if(c == 0) counter = INFCOUNTER;
    if(c > MAXCOUNTER) counter = MAXCOUNTER;
    timer->setInterval(time);
    status = false;
}

bool overTime::isActive() const {
    return status;
}

overTime::~overTime() {
    delete timer;
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
