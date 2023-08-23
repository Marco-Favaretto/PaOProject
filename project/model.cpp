#include "model.h"

#include "consumable.h"
#include "potion.h"
using namespace potion::classe;
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
    Potion* pt = dynamic_cast<Potion*>(x);

    if((c || pt) && !ot) {
        if(!pt) {            // caso in cui è solo consumable
            connect(c, SIGNAL(effectSignal(int)), player, SLOT(changeHP(int)));
            c->effect();

        } else {
            // ricerca overtime attivi
            bool found = false;
            for(Inventario::iteratore i = inventory.begin(); i != inventory.end() && !found; i++) {
                overTime* it = dynamic_cast<overTime*>(&inventory[i]);
                if(it && it->isActive()) {
                    connect(it, SIGNAL(over(overTime*)), this, SLOT(stopOverTime(overTime*)));
                    if(it->getName() == "toxic" &&  (pt->getType() == potion::TOXIC  && player->getStatus() == player::TOXIC)) {
                        it->stopOT();
                        found = true;
                    }
                    if(it->getName() == "poison" && (pt->getType() == potion::POISON && player->getStatus() == player::POISONED)) {
                        it->stopOT();
                        found = true;
                    }
                }
            }
        }
    }
    else if (ot) {
        connect(ot, SIGNAL(effectSignal(int)), player, SLOT(changeHP(int)));
        connect(ot, SIGNAL(over(overTime*)), this, SLOT(stopOverTime(overTime*)));
        ot->startOT();
        if(ot->getName() == "poison") player->changeStatus(player::POISONED);
        if(ot->getName() == "toxic") player->changeStatus(player::TOXIC);
    }

}

void model::stopOverTime(overTime *x) {
    player->changeStatus(player::NORMAL);
    remove(x);
}

void model::printStat() {
    cout << "Status: " << player->getStatusString()
         << " | hp: " << player->getHP() << " / " << MAX_HEALTH
         << endl;
}
