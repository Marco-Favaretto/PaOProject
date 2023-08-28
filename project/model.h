#ifndef MODEL_H
#define MODEL_H

#include "player.h"
using namespace player::classe;
#include "inventario.h"
#include "item.h"
#include "overTime.h"
using namespace overtime::classe;

#include <QObject>

/* -- Per lettura/scrittura file JSON -- */
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

class model : public QObject {
    Q_OBJECT
private:
    Player* player;
    Inventario inv;
    void connectToPlayer() const;
public:
    model();
    model(Player*, Inventario);
//     ~model();
    void insert(Item*);
    void remove(Item*);
    void use(Item*);
    Item* searchItemByID(u_int) const;
    u_int invSize() const;
    Player* getPlayer() const;
    void fromJson(const QJsonObject&);
    QJsonObject toJson() const;
    bool loadGame(const string&);
    void saveGame(const string&) const;
    u_int getMaxId() const;
public slots:
    void stopOverTime(overtime::classe::overTime*);
    void playerHpChanged();
    void playerStatusChanged();
    void playerAtkChanged();
    void playerDefChanged();
    void playerDied();
signals:
    void changedHp();
    void changedStatus();
    void changedAtk();
    void changedDef();
    void playerDead();
};

#endif // MODEL_H
