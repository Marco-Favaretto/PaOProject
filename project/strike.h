#ifndef STRIKE_H
#define STRIKE_H

#include "weapon.h"

class Strike : public Weapon {
public:
    Strike(u_int = 10, string = "unnamed_item", string = "error");
};

#endif // STRIKE_H
