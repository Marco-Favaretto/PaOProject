#ifndef REGULAR_H
#define REGULAR_H

#include "weapon.h"

class Regular : public Weapon {
public:
    Regular(u_int = 10, string = "unnamed_item", string = "error");
    Regular(const Regular&);
    Regular* clone() const override;
    virtual string description() const;
    u_int getATK() const;
};

#endif // REGULAR_H