#ifndef THRUST_H
#define THRUST_H

#include "weapon.h"

class Thrust : public Weapon {
public:
    Thrust(u_int = 10, string = "unnamed_item", string = "error");
};

#endif // THRUST_H
