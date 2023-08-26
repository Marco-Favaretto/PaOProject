#include "overTime.h"
using namespace overtime;
using namespace overtime::classe;

#include <iomanip>
#include <sstream>

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

overTime::~overTime() {
    delete timer;
}

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
