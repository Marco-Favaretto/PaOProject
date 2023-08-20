#include "model.h"
#include "consumable.h"

#include<iostream>
using std::cout; using std::endl;

model::model(Player* _pl, Inventario _inv) : player(_pl), inventory(_inv) {
    connect(player, SIGNAL(hpChanged()), this, SLOT(printStat()));
    connect(player, SIGNAL(statusChanged()), this, SLOT(printStat()));
}

model::~model() {}

void model::insert(Item *x) {
    inventory.insert(x);
}

void model::remove(Item *x) {
    inventory.remove(x);
}

void model::use(Item *x) {
    Consumable* c = dynamic_cast<Consumable*>(x);
    overTime* ot = dynamic_cast<overTime*>(x);

    if(c && !ot) {
        if(c->getName() != "cure4poison" && c->getName() != "cure4toxic"){
            connect(c, SIGNAL(effectSignal(int)), player, SLOT(changeHP(int)));
            c->effect();
        } else {
            // ricerca overtime attivi
            bool found = false;
            for(Inventario::iteratore i = inventory.begin(); i != inventory.end() && !found; i++) {
                overTime* it = dynamic_cast<overTime*>(&inventory[i]);
                if(it && it->isActive()) {
                    connect(it, SIGNAL(over(overTime*)), this, SLOT(stopOverTime(overTime*)));
                    if((it->getName() == "toxic" && c->getName() == "cure4toxic")) { it->stopOT(); found = true;}
                    if((it->getName() == "poison" && c->getName() == "cure4poison")) { it->stopOT(); found = true;}
                }
            }
            if(player->getStatus() == POISONED) player->changeStatus(NORMAL);
        }
    }
    else if (ot) {
        connect(ot, SIGNAL(effectSignal(int)), player, SLOT(changeHP(int)));
        connect(ot, SIGNAL(over(overTime*)), this, SLOT(stopOverTime(overTime*)));
        ot->startOT();
        player->changeStatus(POISONED);
    }

}

void model::stopOverTime(overTime *x) {
    player->changeStatus(NORMAL);
    remove(x);
}

void model::printStat() {
    cout << "Status: " << player->getStatusString()
         << " | hp: " << player->getHP() << " / " << MAX_HEALTH
         << endl;
}