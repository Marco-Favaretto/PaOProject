#ifndef MODEL_H
#define MODEL_H

#include "player.h"
#include "inventario.h"
#include "item.h"

#include <QObject>

class model : public QObject {
    Q_OBJECT
private:
    Player* player;
    Inventario* inventory;
public:
    model();
    ~model();
    void insert(Item*);
    void remove(Item*);
    void connetti(const Item*);
};

#endif // MODEL_H
