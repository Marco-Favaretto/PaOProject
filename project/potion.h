#ifndef POTION_H
#define POTION_H

#include "consumable.h"
#include<string>
using std::string;

enum tipo{POISON, TOXIC};

class Potion : public Consumable
{
    Q_OBJECT
private:
    tipo t;
public:
    Potion(tipo _t, string = "unnamed_item", string = "error");
};

#endif // POTION_H
