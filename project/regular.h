#ifndef REGULAR_H
#define REGULAR_H

#include "weapon.h"

class Regular : public Weapon {
public:
    Regular(u_int = 10, string = "unnamed_item", string = "error");
};

#endif // REGULAR_H