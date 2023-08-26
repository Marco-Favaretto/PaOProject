#include "gameoverdialog.h"

gameOverDialog::gameOverDialog(QWidget *parent) :
    QDialog(parent), v(new QVBoxLayout()), v2(new QVBoxLayout()), h2(new QHBoxLayout()),
    end(new QPushButton("Chiudi", this)), ng(new QPushButton("Ricarica", this)) {
    if(!isModal()) setModal(true);
    l = new QLabel("Y O U  D I E D");
    l->setAlignment(Qt::AlignCenter);
    v2->addWidget(l);
    lp = new QLabel("Scegliere se chiudere l'inventario o ricaricarlo");
    lp->setAlignment(Qt::AlignCenter);
    v2->addWidget(lp);
    h2->addWidget(end);
    h2->addWidget(ng);
    v->addLayout(v2);
    v->addLayout(h2);
    setLayout(v);

    connect(end, SIGNAL(clicked()), this, SLOT(endGameSlot()));
    connect(ng, SIGNAL(clicked()), this, SLOT(newGameSlot()));
}

void gameOverDialog::endGameSlot() {
    emit endgame();
    close();
}

void gameOverDialog::newGameSlot() {
    emit reroll();
    close();
}
