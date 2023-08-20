#ifndef MODEL_H
#define MODEL_H

#include "player.h"
#include "inventario.h"
#include "item.h"
#include "overtime.h"

#include <QObject>

class model : public QObject {
    Q_OBJECT
public:
    Player* player;
    Inventario inventory;
    model(Player*, Inventario);
    ~model();
    void insert(Item*);
    void remove(Item*);
    void use(Item*);
public slots:
    void stopOverTime(overTime*);
    void printStat();
};

#endif // MODEL_H
