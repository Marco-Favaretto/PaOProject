#ifndef CONSUMABLE_H
#define CONSUMABLE_H

#include "item.h"

#include<string>
using std::string;

#define CURA_PIC ":/consumabili/images/curaHP"

class Consumable : public Item {
    Q_OBJECT
    private:
        int hpEffect;
    public:
        Consumable(int=0, string = "unnamed_item", string = "error");
        Consumable(const Consumable&);
        virtual ~Consumable();
        int getEffect() const;
        virtual string description() const;
        Consumable* clone() const override;
    public slots:
        virtual void effect();
    signals:
       void effectSignal(int);
};

#endif // CONSUMABLE_H
