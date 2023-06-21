#ifndef WEAPON_H
#define WEAPON_H

#include "item.h"

#define u_int unsigned int

#include<string>
using std::string;

enum w_type {THRUST, STRIKE};

class Weapon : public Item {
    private:
        w_type tipo;
        u_int atk;
    public:
        Weapon(w_type = THRUST, u_int = 10, string = "unnamed_item", string = "error");
        virtual void effect();
        virtual ~Weapon() =0;
};

#endif // WEAPON_H
