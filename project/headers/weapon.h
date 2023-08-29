#ifndef WEAPON_H
#define WEAPON_H

#include "item.h"

#define u_int unsigned int

#include<string>
using std::string;

class Weapon : public Item {
    Q_OBJECT
    private:
        u_int atk;
        bool equip;
    public:
        Weapon(u_int = 10, const string& = "unnamed_item", const string& = "error");
        Weapon(const Weapon&);
        virtual ~Weapon() =0;
        bool isEquipped() const;
        void setValue(int);
        u_int getValue() const;
        virtual string description() const;
    public slots:
        virtual void effect();
    signals:
        void statSignal(u_int);
};

#endif // WEAPON_H