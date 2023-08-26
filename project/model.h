#ifndef MODEL_H
#define MODEL_H

#include "player.h"
using namespace player::classe;
#include "inventario.h"
#include "item.h"
#include "overTime.h"
using namespace overtime::classe;

#include <QObject>

class model : public QObject {
    Q_OBJECT
private:
    Player* player;
    Inventario inventory;
    void connectToPlayer() const;
public:
    model(Player*, Inventario);
    ~model();
    void insert(Item*);
    void remove(Item*);
    void use(Item*);
    Item* searchItemByID(u_int) const;
    u_int invSize() const;
    Player* getPlayer() const;
public slots:
    void stopOverTime(overtime::classe::overTime*);
    void playerHpChanged();
    void playerStatusChanged();
    void playerAtkChanged();
    void playerDefChanged();
signals:
    void changedHp();
    void changedStatus();
    void changedAtk();
    void changedDef();
};

#endif // MODEL_H
