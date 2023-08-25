#ifndef SHIELD_H
#define SHIELD_H

#include "weapon.h"

class Shield : public Weapon {
private:
    u_int def;
public:
    Shield(u_int = 10, string = "unnamed_item", string = "error");
    virtual string description() const;
    u_int getDEF() const;
};

#endif // SHIELD_H