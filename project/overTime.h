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
    public:
        overTime(string = "unnamed_item", string = "error", u_int = STDTIMER);
        virtual ~overTime() =0;
        bool isActive() const;
    public slots:
        virtual void effect();
        void stopOT();
        void startOT();
};

#endif // OVERTIME_H
