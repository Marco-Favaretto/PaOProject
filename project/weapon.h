#ifndef WEAPON_H
#define WEAPON_H

#include "item.h"

#define u_int unsigned int

#include<string>
using std::string;

class Weapon : public Item {
    private:
        u_int atk;
    public:
        Weapon(u_int = 10, string = "unnamed_item", string = "error");
        virtual ~Weapon() =0;
    public slots:
        virtual int effect();
};

#endif // WEAPON_H
