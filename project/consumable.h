#ifndef CONSUMABLE_H
#define CONSUMABLE_H

#include "item.h"

#include<string>
using std::string;

class Consumable : public Item {
    Q_OBJECT
    private:
        int hpEffect;
    public:
        Consumable(string = "unnamed_item", string = "error", int=0);
        virtual ~Consumable() =0;
    public slots:
        virtual void effect();
    signals:
       void effectSignal(int);
};

#endif // CONSUMABLE_H
