#ifndef OVERTIME_H
#define OVERTIME_H

#include "consumable.h"

#define u_int unsigned int
#include<string>
using std::string;

#include <QTimer>
#define STDTIMER 5000

class overTime : public Consumable {
    private:
        QTimer* timer;
        bool status;
        int hp;
        int counter;
    public:
        overTime(string = "unnamed_item", string = "error", int hp = 0, u_int = STDTIMER, int c = -1);
        virtual ~overTime();
        bool isActive() const;
    public slots:
        virtual int effect();
        void stopOT();
        void startOT();
    signals:
        void over();
};

#endif // OVERTIME_H
