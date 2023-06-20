#ifndef CONSUMABLE_H
#define CONSUMABLE_H

#include "item.h"

#include<string>
using std::string;

class Consumable : public Item {
    private:
    public:
        Consumable(string = "unnamed_item", string = "error");
        virtual void effect();
        virtual ~Consumable() =0;
};

#endif // CONSUMABLE_H