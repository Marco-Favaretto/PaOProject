#include "showbutton.h"

//#include "consumable.h"
//#include "overTime.h"
//#include "potion.h"
//using namespace potion::classe;
//#include "weapon.h"

#include<iostream>

ShowButton::ShowButton(tipo _t, QString title, QWidget *parent) :
    QPushButton(title, parent), t(_t) {
    connect(this, SIGNAL(clicked()), this, SLOT(onClicked()));
}

void ShowButton::onClicked() {
    switch(t) {
        case TUTTI:
//            Item* x;
            std::cout << "item*"<<std::endl;
            emit click(TUTTI);
        break;
        case CONSUMABILI:
//            Consumable* c;
            std::cout << "consumable*"<<std::endl;
            emit click(CONSUMABILI);
        break;
        case TEMPO:
//            overTime* ot;
            std::cout << "overtime*"<<std::endl;
            emit click(TEMPO);
        break;
        case POZIONI:
//            Potion* pt;
            std::cout << "potion*"<<std::endl;
            emit click(POZIONI);
        break;
        case ARMI:
//            Weapon* w;
            std::cout << "weapon*"<<std::endl;
            emit click(ARMI);
        break;
    }
}

