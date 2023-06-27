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
//    connect(x, SIGNAL(), player, SLOT());
}
