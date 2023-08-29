#include "model.h"

#include<QFile>
#include<QByteArray>

#include "consumable.h"
#include "potion.h"
using namespace potion::classe;
#include "weapon.h"
#include "shield.h"
#include "regular.h"


model::model() : player(new Player()), inv(Inventario()) {
    connectToPlayer();
}

model::model(Player* _pl, Inventario _inv) : player(_pl), inv(_inv) {
    connectToPlayer();
}

// model::~model() {
//     delete player;
// }

void model::insert(Item *x) {

    inv.insert(x);

}

void model::remove(Item *x) {
    inv.remove(x);
}

void model::use(Item *x) {
    Consumable* c = dynamic_cast<Consumable*>(x);
    overTime* ot = dynamic_cast<overTime*>(x);
    Potion* pt = dynamic_cast<Potion*>(x);
    regular::Regular* r = dynamic_cast<regular::Regular*>(x);
    shield::Shield* s = dynamic_cast<shield::Shield*>(x);

    if((c || pt) && !ot) {
        if(!pt) {            // caso in cui è solo consumable
            connect(c, SIGNAL(effectSignal(int)), player, SLOT(changeHP(int)));
            c->effect();

        } else {
            // ricerca overtime attivi
            bool found = false;
            for(Inventario::iteratore i = inv.begin(); i != inv.end() && !found; i++) {
                overTime* it = dynamic_cast<overTime*>(&inv[i]);
                if(it && it->isActive()) {
                    connect(it, SIGNAL(over(overtime::classe::overTime*)), this, SLOT(stopOverTime(overtime::classe::overTime*)));
                    if((pt->getType() == potion::TOXIC  && player->getStatus() == player::TOXIC)) {
                        it->stopOT();
                        found = true;
                    }
                    if((pt->getType() == potion::POISON && player->getStatus() == player::POISONED)) {
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
        if(ot->getType() == overtime::POISON) player->changeStatus(player::POISONED);
        if(ot->getType() == overtime::TOXIC) player->changeStatus(player::TOXIC);
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

Item* model::searchItemByID(u_int _id) const {
    bool found = false;
    Item* it = nullptr;
    for(Inventario::iteratore i = inv.begin(); i != inv.end() && !found; i++) {
        if((inv[i]).getID() == _id) {
            found = true;
            it = &(inv[i]);
        }
    }
    if(!found) return nullptr;
    else return it;
}

u_int model::getMaxId() const {
    return inv.getHighestID();
}

unsigned int model::invSize() const {
    return inv.size();
}

Player *model::getPlayer() const {
    return player;
}

void model::connectToPlayer() const {
    connect(player, SIGNAL(hpChanged()), this, SLOT(playerHpChanged()));
    connect(player, SIGNAL(statusChanged()), this, SLOT(playerStatusChanged()));
    connect(player, SIGNAL(atkChanged()), this, SLOT(playerAtkChanged()));
    connect(player, SIGNAL(defChanged()), this, SLOT(playerDefChanged()));
    connect(player, SIGNAL(dead()), this, SLOT(playerDied()));
}

void model::stopOverTime(overTime *x) {
    if(player->getStatus() != player::DEAD) player->changeStatus(player::NORMAL);
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

void model::playerDied() {
    for(Inventario::iteratore it = inv.begin(); it != inv.end(); it++) {
        overTime* ot = dynamic_cast<overTime*>(&inv[it]);
        if(ot && ot->isActive()) ot->stopOT();
    }
    emit playerDead();
}

void model::fromJson(const QJsonObject &json) {
    if(const QJsonValue v = json["inv"]; v.isObject())
        inv.fromJson(v.toObject());
    if(const QJsonValue v = json["player"]; v.isObject())
        player = new Player(Player::fromJson(v.toObject()));
}

QJsonObject model::toJson() const {
    QJsonObject obj;
    obj["inv"] = inv.toJson();
    obj["player"] = player->toJson();
    return obj;
}

bool model::loadGame(const std::string & path) {
    // cancellazione dati attuali
    Player* p = player;
    player = nullptr;
    delete p;
    inv.clear();

    QFile loadfile(QString::fromStdString(path));
    if(loadfile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QByteArray loaddata = loadfile.readAll();
        QJsonDocument jsdoc(QJsonDocument::fromJson(loaddata));
        fromJson(jsdoc.object());
        connectToPlayer();
        loadfile.close();
        return true;
    } else {
        loadfile.close();
        return false;
    }
}

void model::saveGame(const string& path) const {
    QFile saveFile(QString::fromStdString(path));
    QJsonObject obj = toJson();
    QByteArray byteArray = QJsonDocument(obj).toJson();
    if(saveFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        saveFile.write(byteArray);
    }
    saveFile.close();
}
