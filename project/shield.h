#ifndef SHIELD_H
#define SHIELD_H

#include "weapon.h"

class Shield : public Weapon {
public:
    Shield(u_int = 10, string = "unnamed_item", string = "error");
};

#endif // SHIELD_H
