#include "showaction.h"
using namespace showaction;

ShowAction::ShowAction(showbutton::tipo _t, QString title, QObject *parent) :
    QAction(title, parent), t(_t) {
    connect(this, SIGNAL(triggered()), this, SLOT(onClicked()));
}

void ShowAction::onClicked() {
    switch(t) {
        case showbutton::TUTTI:
            emit trig(showbutton::TUTTI);
        break;
        case showbutton::CONSUMABILI:
            emit trig(showbutton::CONSUMABILI);
        break;
        case showbutton::TEMPO:
            emit trig(showbutton::TEMPO);
        break;
        case showbutton::POZIONI:
            emit trig(showbutton::POZIONI);
        break;
        case showbutton::ARMI:
            emit trig(showbutton::ARMI);
        break;
    }
}
