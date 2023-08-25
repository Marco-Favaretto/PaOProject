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
            emit click(TUTTI);
        break;
        case CONSUMABILI:
            emit click(CONSUMABILI);
        break;
        case TEMPO:
            emit click(TEMPO);
        break;
        case POZIONI:
            emit click(POZIONI);
        break;
        case ARMI:
            emit click(ARMI);
        break;
    }
}