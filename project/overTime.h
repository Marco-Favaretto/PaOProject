#ifndef OVERTIME_H
#define OVERTIME_H

#include "consumable.h"

#include<string>
using std::string;

class overTime : public Consumable {
    private:
    public:
        overTime(string = "unnamed_item", string = "error");
        virtual void effect();
        virtual ~overTime() =0;
};

#endif // OVERTIME_H