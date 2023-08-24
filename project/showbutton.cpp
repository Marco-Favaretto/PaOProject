#include "showbutton.h"

#include "consumable.h"
#include "overTime.h"
#include "potion.h"
using namespace potion::classe;
#include "weapon.h"

#include<iostream>

ShowButton::ShowButton(tipo _t, QString title, QWidget *parent) :
    QPushButton(title, parent), t(_t) {
    connect(this, SIGNAL(clicked()), this, SLOT(onClicked()));
}

void ShowButton::onClicked() {
    switch(t) {
        case TUTTI:
            Item* x;
            std::cout << "item*"<<std::endl;
            emit clicked(x);
        break;
        case CONSUMABILI:
            Consumable* c;
            std::cout << "consumable*"<<std::endl;
            emit clicked(c);
        break;
        case TEMPO:
            overTime* ot;
            std::cout << "overtime*"<<std::endl;
            emit clicked(ot);
        break;
        case POZIONI:
            Potion* pt;
            std::cout << "potion*"<<std::endl;
            emit clicked(pt);
        break;
        case ARMI:
            Weapon* w;
            std::cout << "weapon*"<<std::endl;
            emit clicked(w);
        break;
    }
}

