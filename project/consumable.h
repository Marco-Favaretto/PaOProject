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
        Consumable(int=0, string = "unnamed_item", string = "error");
        virtual ~Consumable();
        int getEffect() const;
        virtual string description() const;
    public slots:
        virtual void effect();
    signals:
       void effectSignal(int);
};

#endif // CONSUMABLE_H
