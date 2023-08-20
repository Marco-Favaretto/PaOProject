#ifndef OVERTIME_H
#define OVERTIME_H

#include "consumable.h"

#define u_int unsigned int
#include<string>
using std::string;

#include <QTimer>
#define STDTIMER 5000
#define MAXCOUNTER 10
#define INFCOUNTER -1

class overTime : public Consumable {
    Q_OBJECT
    private:
        QTimer* timer;
        bool status;
        int counter;
    public:
        overTime(int hp = 0, u_int = STDTIMER, int c = INFCOUNTER, string = "unnamed_item", string = "error");
        virtual ~overTime();
        bool isActive() const;
    public slots:
        virtual void effect();
        void stopOT();
        void startOT();
    signals:
        void over(overTime*);
};

#endif // OVERTIME_H
