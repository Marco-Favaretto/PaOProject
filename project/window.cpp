#include "window.h"

#include "consumable.h"
#include "overTime.h"
using namespace overtime::classe;
#include "potion.h"
using namespace potion::classe;
#include "shield.h"
#include "regular.h"
#include "inventario.h"
#include "player.h"
using namespace player::classe;

#include <QPixmap>

#include<iostream>

Window::Window(QWidget *parent)
    : QMainWindow{parent},
      mod(new model(new Player(), Inventario())),
      deathScreen(new gameOverDialog(this)),
      rowSel(-1), colSel(-1)
{
    setupGui();
    loadItemPicDefault();
    connectModel();
    connectGui();
    fillInv();
    loadInv();
    hpChanged();
    statusChanged();
    atkChanged();
    defChanged();
}

void Window::fillInv() {
    Consumable* cure1 = new Consumable(20, "cure", CURA_PIC);
    Consumable* cure2 = new Consumable(10, "cure", CURA_PIC);
    Consumable* cure3 = new Consumable(15, "cure", CURA_PIC);
    Consumable* cure4 = new Consumable(5 , "cure", CURA_PIC);
    Consumable* cura5 = new Consumable(-99 , "instaDeath", CURA_PIC);
    Consumable* cura6 = new Consumable(-100 , "instaDeath", CURA_PIC);
    mod->insert(cure1);
    mod->insert(cure2);
    mod->insert(cure3);
    mod->insert(cure4);
    mod->insert(cura5);
    mod->insert(cura6);
    overTime* ot = new overTime(overtime::POISON, -10, 8, "poison");
    mod->insert(ot);
    overTime* otoxic = new overTime(overtime::TOXIC, -20, 4, "toxic");
    mod->insert(otoxic);
    Potion* cure4poison = new Potion(potion::POISON , "Potion::poison");
    mod->insert(cure4poison);
    Potion* cure4toxic = new Potion(potion::TOXIC , "Potion::toxic");
    mod->insert(cure4toxic);
    Regular* swrd = new Regular(25, "longSword");
    Regular* swrd2 = new Regular(15, "shortSword");
    Shield* shild = new Shield(15, "shield1");
    Shield* shild2 = new Shield(30, "PortoneDeCasa");
    mod->insert(swrd);
    mod->insert(swrd2);
    mod->insert(shild);
    mod->insert(shild2);
}

void Window::loadInv() {
    invDisplay->horizontalHeader()->setStretchLastSection(true);
    invDisplay->setEditTriggers(QAbstractItemView::NoEditTriggers);
    invDisplay->verticalHeader()->setVisible(false);
    invDisplay->setColumnCount(3);
    QStringList tableHeaders;
    tableHeaders.append("ID");
    tableHeaders.append("Name");
    tableHeaders.append("Description");
    invDisplay->setHorizontalHeaderLabels(tableHeaders);
    showOnly(showbutton::TUTTI);
}

void Window::connectModel() {
    connect(mod, SIGNAL(changedHp()),     this, SLOT(hpChanged()));
    connect(mod, SIGNAL(changedStatus()), this, SLOT(statusChanged()));
    connect(mod, SIGNAL(changedAtk()),    this, SLOT(atkChanged()));
    connect(mod, SIGNAL(changedDef()),    this, SLOT(defChanged()));
    connect(mod, SIGNAL(playerDead()),    this, SLOT(playerDeath()));
}

void Window::hpChanged() {
    hpValue->setText(QString::number(mod->getPlayer()->getHP()) + " / " + QString::number(MAX_HEALTH));
    hpProgressBar->setValue(mod->getPlayer()->getHP());
    loadPlayerPic();
}

void Window::statusChanged() {
    statusTxt->setText(QString::fromStdString(mod->getPlayer()->getStatusString()));
    loadPlayerPic();
}

void Window::atkChanged() {
    atkTxt->setText(QString::number(mod->getPlayer()->getAtk()));
}

void Window::defChanged() {
    defTxt->setText(QString::number(mod->getPlayer()->getDef()) + "%");
}

void Window::playerDeath() {
    statusChanged();
    hpChanged();
    deathScreen->show();
}

void Window::cellSelected(int row, int column) {
    rowSel = row;
    colSel = column;
    loadItemPic();
}

void Window::onRemoveButton() {
    QTableWidgetItem* it = invDisplay->takeItem(rowSel, 0);
    mod->remove(mod->searchItemByID(it->text().toInt()));
    invDisplay->removeRow(invDisplay->currentRow());
    delete it;
    loadItemPicDefault();
}

void Window::onCreateButton() {
    // crea prompt per nuovo oggetto
    // mod->insert
    // table->insert
}

void Window::onUseButton() {
    QTableWidgetItem* it = invDisplay->takeItem(rowSel, 0);
    mod->use(mod->searchItemByID(it->text().toInt()));
    invDisplay->removeRow(invDisplay->currentRow());
    delete it;
    loadItemPicDefault();
}

void Window::onEquipButton() {
    QTableWidgetItem* it = invDisplay->item(rowSel, 0);
    mod->use(mod->searchItemByID(it->text().toInt()));
}

void Window::loadPlayerPic() {
    QPixmap playerPixmap(QString::fromStdString(mod->getPlayer()->getPath()));
    imgPlayer->setPixmap( playerPixmap.scaled(imgPlayer->width(), imgPlayer->height(), Qt::KeepAspectRatio) );
}

void Window::loadItemPic() {
    QTableWidgetItem* it = invDisplay->item(rowSel, 0);
    QPixmap itemPixmap(QString::fromStdString( mod->searchItemByID(it->text().toInt())->getItemPath() ));
    imgItem->setPixmap( itemPixmap.scaled(imgPlayer->width(), imgPlayer->height(), Qt::KeepAspectRatio) );
}

void Window::loadItemPicDefault() {
    QPixmap itemPixmap(QString::fromStdString( DEFAULTPIC ));
    imgItem->setPixmap( itemPixmap.scaled(imgItem->width(), imgItem->height(), Qt::KeepAspectRatio) );
}

void Window::loadRow(u_int i) {
    int rows = invDisplay->rowCount();
    invDisplay->insertRow(rows);
    invDisplay->setItem(rows, 0, new QTableWidgetItem(QString::number(mod->searchItemByID(i)->getID())));
    invDisplay->setItem(rows, 1, new QTableWidgetItem(QString::fromStdString(mod->searchItemByID(i)->getName())));
    invDisplay->setItem(rows, 2, new QTableWidgetItem(QString::fromStdString(mod->searchItemByID(i)->description())));
}

void Window::showOnly(showbutton::tipo t) {
    invDisplay->setRowCount(0); // reset tabella
    switch(t) {
        case showbutton::TUTTI:
            for(u_int i = 0; i < mod->invSize(); i++) loadRow(i);
        break;
        case showbutton::CONSUMABILI:
            for(u_int i = 0; i < mod->invSize(); i++) {
                if(dynamic_cast<Consumable*>(mod->searchItemByID(i))) loadRow(i);
            }
        break;
        case showbutton::TEMPO:
            for(u_int i = 0; i < mod->invSize(); i++) {
                if(dynamic_cast<overTime*>(mod->searchItemByID(i))) loadRow(i);
            }
        break;
        case showbutton::POZIONI:
            for(u_int i = 0; i < mod->invSize(); i++) {
                if(dynamic_cast<Potion*>(mod->searchItemByID(i))) loadRow(i);
            }
        break;
        case showbutton::ARMI:
            for(u_int i = 0; i < mod->invSize(); i++) {
                if(dynamic_cast<Weapon*>(mod->searchItemByID(i))) loadRow(i);
            }
        break;
    }
}












void Window::connectGui() {
    // tabella
    connect(invDisplay, SIGNAL(cellClicked(int,int)), this, SLOT(cellSelected(int,int)));
    // bottomButtons
    connect(removeButton, SIGNAL(clicked()), this, SLOT(onRemoveButton()));
    connect(useButton,    SIGNAL(clicked()), this, SLOT(onUseButton())   );
    connect(equipButton,  SIGNAL(clicked()), this, SLOT(onEquipButton()) );
    connect(createButton, SIGNAL(clicked()), this, SLOT(onCreateButton()));
    // up buttons
    connect(dispTutto, SIGNAL(click(showbutton::tipo)), this, SLOT(showOnly(showbutton::tipo)));
    connect(dispCons,  SIGNAL(click(showbutton::tipo)), this, SLOT(showOnly(showbutton::tipo)));
    connect(dispOT,    SIGNAL(click(showbutton::tipo)), this, SLOT(showOnly(showbutton::tipo)));
    connect(dispPot,   SIGNAL(click(showbutton::tipo)), this, SLOT(showOnly(showbutton::tipo)));
    connect(dispWeap,  SIGNAL(click(showbutton::tipo)), this, SLOT(showOnly(showbutton::tipo)));
    // menu
    // menu mostra solo
    connect(actionTutti,          SIGNAL(trig(showbutton::tipo)), this, SLOT(showOnly(showbutton::tipo)));
    connect(actionConsumabili,    SIGNAL(trig(showbutton::tipo)), this, SLOT(showOnly(showbutton::tipo)));
    connect(actionOggetti_a_Tempo,SIGNAL(trig(showbutton::tipo)), this, SLOT(showOnly(showbutton::tipo)));
    connect(actionPozioni,        SIGNAL(trig(showbutton::tipo)), this, SLOT(showOnly(showbutton::tipo)));
    connect(actionArmi_e_Scudi,   SIGNAL(trig(showbutton::tipo)), this, SLOT(showOnly(showbutton::tipo)));
}

Window::~Window() {
    delete mod;
}

void Window::setupGui() {
    setObjectName("Progetto PaO");
    resize(900, 595);
    // setup centrale
    centralWidget = new QWidget(this);
    centralWidget->setGeometry(QRect(10, 10, 840, 560));
    centralHL = new QHBoxLayout(centralWidget);
    centralHL->setContentsMargins(10, 10, 10, 25);
    setCentralWidget(centralWidget);
    centralWidget->setLayout(centralHL);


    actionSalva = new QAction("Salva", this);
    actionCarica = new QAction("Carica", this);
    actionCrea_oggetto = new QAction("Crea Oggetto", this);
    actionTutti = new ShowAction(showbutton::TUTTI, "Tutti", this);
    actionConsumabili = new ShowAction(showbutton::CONSUMABILI, "Consumabili", this);
    actionOggetti_a_Tempo = new ShowAction(showbutton::TEMPO, "Oggetti a Tempo", this);
    actionPozioni = new ShowAction(showbutton::POZIONI, "Pozioni", this);
    actionArmi_e_Scudi = new ShowAction(showbutton::ARMI, "Armi e Scudi", this);
    // menu
    menubar = new QMenuBar(this);
    menubar->setGeometry(QRect(0, 0, 851, 25));
    menuFile = new QMenu("File", menubar);
    menuOpzioni = new QMenu("Opzioni", menubar);
    menuMostra_Solo = new QMenu("Mostra Solo...", menuOpzioni);
    menuBar()->setNativeMenuBar(false);
    setMenuBar(menubar);

    menubar->addAction(menuFile->menuAction());
    menubar->addAction(menuOpzioni->menuAction());
    menuFile->addAction(actionSalva);
    menuFile->addAction(actionCarica);
    menuOpzioni->addAction(actionCrea_oggetto);
    menuOpzioni->addAction(menuMostra_Solo->menuAction());
    menuMostra_Solo->addAction(actionTutti);
    menuMostra_Solo->addAction(actionConsumabili);
    menuMostra_Solo->addAction(actionOggetti_a_Tempo);
    menuMostra_Solo->addAction(actionPozioni);
    menuMostra_Solo->addAction(actionArmi_e_Scudi);

    //inventario
    inv_layout = new QVBoxLayout(centralWidget);

    // setup bottoni in alto
    upButtonLayout = new QHBoxLayout();
    dispTutto = new ShowButton(showbutton::TUTTI, "Tutto", centralWidget);
    upButtonLayout->addWidget(dispTutto);
    dispCons = new ShowButton(showbutton::CONSUMABILI, "Consumabili", centralWidget);
    upButtonLayout->addWidget(dispCons);
    dispOT = new ShowButton(showbutton::TEMPO, "Oggetti a Tempo", centralWidget);
    upButtonLayout->addWidget(dispOT);
    dispPot = new ShowButton(showbutton::POZIONI, "Pozioni", centralWidget);
    upButtonLayout->addWidget(dispPot);
    dispWeap = new ShowButton(showbutton::ARMI, "Armi e Scudi", centralWidget);
    upButtonLayout->addWidget(dispWeap);
    inv_layout->addLayout(upButtonLayout);

    // set up tabella
    invDisplay = new QTableWidget(centralWidget);
    inv_layout->addWidget(invDisplay);

    // setup bottoni in basso
    bottomButtonLayout = new QHBoxLayout();
    createButton = new QPushButton("Crea", centralWidget);
    bottomButtonLayout->addWidget(createButton);
    useButton = new QPushButton("Usa", centralWidget);
    bottomButtonLayout->addWidget(useButton);
    equipButton = new QPushButton("Equipaggia", centralWidget);
    bottomButtonLayout->addWidget(equipButton);
    removeButton = new QPushButton("Rimuovi", centralWidget);
    bottomButtonLayout->addWidget(removeButton);
    inv_layout->addLayout(bottomButtonLayout);

    centralHL->addLayout(inv_layout);

    // setup laterale
    infoDisp = new QWidget(centralWidget);
    infoDisp->setMinimumSize(QSize(200, 549));
    infoDisp->setMaximumSize(QSize(300, 549));
    infoLayout = new QVBoxLayout(infoDisp);
    centralHL->addLayout(infoLayout);

    // immagini
    imgDisp = new QWidget(infoDisp);
    imgDisp->setGeometry(QRect(0, 0, 200, 211));
    imgLayout = new QHBoxLayout(imgDisp);
    imgLayout->setContentsMargins(0, 0, 0, 0);
    infoLayout->addWidget(imgDisp);

    imgItem = new QLabel("ImgItem", imgDisp);
    imgItem->setGeometry(QRect(0, 0, 170, 151));
    imgPlayer = new QLabel("ImgPlayer", imgDisp);
    imgPlayer->setGeometry(QRect(150, 0, 170, 151));
    imgLayout->addWidget(imgItem);
    imgLayout->addWidget(imgPlayer);

    // stat generale
    statDisp = new QWidget(infoDisp);
    statDisp->setGeometry(QRect(-1, -1, 200, 276));
    statLayout = new QVBoxLayout(statDisp);
    statLayout->setContentsMargins(0, 0, 0, 0);
    infoLayout->addWidget(statDisp);

    // stat hp
    statHL1 = new QHBoxLayout(statDisp);
    hpLabel = new QLabel("HP", statDisp);
    statHL1->addWidget(hpLabel);
    hpProgressBar = new QProgressBar(statDisp);
    hpProgressBar->setMaximum(MAX_HEALTH);
    hpProgressBar->setTextVisible(false);
    statHL1->addWidget(hpProgressBar);
    hpValue = new QLabel("x/x", statDisp);
    statHL1->addWidget(hpValue);
    statLayout->addLayout(statHL1);
    // stat status
    statHL2 = new QHBoxLayout(statDisp);
    statusLabel = new QLabel("STATUS", statDisp);
    statHL2->addWidget(statusLabel);
    statusTxt = new QTextEdit(statDisp);
    statusTxt->setMinimumSize(QSize(10, 10));
    statusTxt->setMaximumSize(QSize(300, 30));
    statusTxt->setReadOnly(true);
    statHL2->addWidget(statusTxt);
    statLayout->addLayout(statHL2);
    // stat atk
    statHL3 = new QHBoxLayout(statDisp);
    atkLabel = new QLabel("ATK", statDisp);
    statHL3->addWidget(atkLabel);
    atkTxt = new QTextEdit(statDisp);
    atkTxt->setMaximumSize(QSize(300, 30));
    atkTxt->setReadOnly(true);
    statHL3->addWidget(atkTxt);
    statLayout->addLayout(statHL3);
    // stat def
    statHL4 = new QHBoxLayout(statDisp);
    defLabel = new QLabel("DEF", statDisp);
    statHL4->addWidget(defLabel);
    defTxt = new QTextEdit(statDisp);
    defTxt->setMaximumSize(QSize(300, 30));
    defTxt->setReadOnly(true);
    statHL4->addWidget(defTxt);
    statLayout->addLayout(statHL4);

    // save & load
    widgetSaveLoad = new QWidget(infoDisp);
    widgetSaveLoad->setGeometry(QRect(0, 0, 300, 61));
    layoutSaveLoad = new QHBoxLayout(widgetSaveLoad);
    layoutSaveLoad->setContentsMargins(0, 0, 0, 0);
    saveButton = new QPushButton("Salva", widgetSaveLoad);
    layoutSaveLoad->addWidget(saveButton);
    loadButton = new QPushButton("Carica", widgetSaveLoad);
    layoutSaveLoad->addWidget(loadButton);
    infoLayout->addWidget(widgetSaveLoad);

    centralHL->addWidget(infoDisp);

}
