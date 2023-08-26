#include "model.h"

#include "consumable.h"
#include "potion.h"
using namespace potion::classe;

#include "weapon.h"
#include "shield.h"
#include "regular.h"
#include<iostream>
using std::cout; using std::endl;

model::model(Player* _pl, Inventario _inv) : player(_pl), inventory(_inv) {
    connectToPlayer();
}

model::~model() {
    delete player;
}

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
    Regular* r = dynamic_cast<Regular*>(x);
    Shield* s = dynamic_cast<Shield*>(x);

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
                    connect(it, SIGNAL(over(overtime::classe::overTime*)), this, SLOT(stopOverTime(overtime::classe::overTime*)));
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
        connect(ot, SIGNAL(over(overtime::classe::overTime*)), this, SLOT(stopOverTime(overtime::classe::overTime*)));
        ot->startOT();
        if(ot->getName() == "poison") player->changeStatus(player::POISONED);
        if(ot->getName() == "toxic") player->changeStatus(player::TOXIC);
    }
    if(s) {
        connect(s, SIGNAL(statSignal(uint)), player, SLOT(setDefense(uint)));
        s->effect();
    }
    if(r) {
        connect(r, SIGNAL(statSignal(uint)), player, SLOT(setAttack(uint)));
        r->effect();
    }

}

Item *model::searchItemByID(u_int _id) const {
    bool found = false;
    for(Inventario::iteratore i = inventory.begin(); i != inventory.end() && !found; i++) {
        if((inventory[i]).getID() == _id) {
            found = true;
            return &(inventory[i]);
        }
    }
    if(!found) return nullptr;
}

unsigned int model::invSize() const {
    return inventory.size();
}

Player *model::getPlayer() const {
    return player;
}

void model::connectToPlayer() const {
    connect(player, SIGNAL(hpChanged()), this, SLOT(playerHpChanged()));
    connect(player, SIGNAL(statusChanged()), this, SLOT(playerStatusChanged()));
    connect(player, SIGNAL(atkChanged()), this, SLOT(playerAtkChanged()));
    connect(player, SIGNAL(defChanged()), this, SLOT(playerDefChanged()));
}

void model::stopOverTime(overTime *x) {
    player->changeStatus(player::NORMAL);
    remove(x);
}

void model::playerHpChanged() {
    emit changedHp();
}

void model::playerStatusChanged() {
    emit changedStatus();
}

void model::playerAtkChanged() {
    emit changedAtk();
}

void model::playerDefChanged() {
    emit changedDef();
}
