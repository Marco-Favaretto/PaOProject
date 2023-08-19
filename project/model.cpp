#include "model.h"

model::model() {}

model::~model() {}

void model::insert(Item *x) {
    inventory->insert(x);
}

void model::remove(Item *x) {
    inventory->remove(x);
}

void model::connetti(const Item *x) {
//   connect(x, SIGNAL(), player, SLOT());


    /* Possibili connessioni:
     * se x è consumable -> connect(x, SIGNAL(emit hpEffect), player, SLOT(changeHp))
     * se x è overTime   -> connect(x, SIGNAL(emit hpEffect), player, SLOT(changeHP))
     *                   -> connect(player, SIGNAL(statusChanged(_st)), x, SLOT(stopOT(_st)))
     *                   -> mettere stopOT(_st) if(_st!=poisoned)
     * in ogni caso:
     *      connect(x, SIGNAL(used(true), this, SLOT(itemUsed(true)))
     *      itemUsed(bool) dovrà eliminare item* x { remove(x) }
    */
}
