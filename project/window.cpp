#include "window.h"

#include "consumable.h"
#include "overTime.h"
#include "potion.h"
using namespace potion::classe;
#include "shield.h"
#include "regular.h"
#include "inventario.h"
#include "player.h"
using namespace player::classe;

#include<iostream>

Window::Window(QWidget *parent)
    : QMainWindow{parent}, mod(new model(new Player(), Inventario())), rowSel(-1), colSel(-1)
{
    setupGui();
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
    Consumable* cure1 = new Consumable(20, "cure", "error");
    Consumable* cure2 = new Consumable(10, "cure", "error");
    Consumable* cure3 = new Consumable(15, "cure", "error");
    Consumable* cure4 = new Consumable(5 , "cure", "error");
    mod->insert(cure1);
    mod->insert(cure2);
    mod->insert(cure3);
    mod->insert(cure4);
    overTime* ot = new overTime(-10, 2000, 8, "poison", "error");
    mod->insert(ot);
    overTime* otoxic = new overTime(-20, 500, 4, "toxic", "error");
    mod->insert(otoxic);
    Potion* cure4poison = new Potion(potion::POISON , "Potion::poison", "error");
    mod->insert(cure4poison);
    Potion* cure4toxic = new Potion(potion::TOXIC , "Potion::toxic", "error");
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
    Item *x;
    showOnly(x);
}

void Window::connectModel() {
    connect(mod, SIGNAL(changedHp()),     this, SLOT(hpChanged()));
    connect(mod, SIGNAL(changedStatus()), this, SLOT(statusChanged()));
    connect(mod, SIGNAL(changedAtk()),    this, SLOT(atkChanged()));
    connect(mod, SIGNAL(changedDef()),    this, SLOT(defChanged()));
}

void Window::hpChanged() {
    hpValue->setText(QString::number(mod->getPlayer()->getHP()) + " / " + QString::number(MAX_HEALTH));
    hpProgressBar->setValue(mod->getPlayer()->getHP());
}

void Window::statusChanged() {
    statusTxt->setText(QString::fromStdString(mod->getPlayer()->getStatusString()));
}

void Window::atkChanged() {
    atkTxt->setText(QString::number(mod->getPlayer()->getAtk()));
}

void Window::defChanged() {
    defTxt->setText(QString::number(mod->getPlayer()->getDef()) + "%");
}

void Window::cellSelected(int row, int column) {
    rowSel = row;
    colSel = column;
}

void Window::onRemoveButton() {
    QTableWidgetItem* it = invDisplay->takeItem(rowSel, 0);
    mod->remove(mod->searchItemByID(it->text().toInt()));
    invDisplay->removeRow(invDisplay->currentRow());
    delete it;
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
}

void Window::onEquipButton() {
    QTableWidgetItem* it = invDisplay->item(rowSel, 0);
    mod->use(mod->searchItemByID(it->text().toInt()));
}


void Window::loadRow(u_int i) {
    int rows = invDisplay->rowCount();
    invDisplay->insertRow(rows);
    invDisplay->setItem(rows, 0, new QTableWidgetItem(QString::number(mod->searchItemByID(i)->getID())));
    invDisplay->setItem(rows, 1, new QTableWidgetItem(QString::fromStdString(mod->searchItemByID(i)->getName())));
    invDisplay->setItem(rows, 2, new QTableWidgetItem(QString::fromStdString(mod->searchItemByID(i)->description())));
}

void Window::showOnly(Item* x) {
    invDisplay->setRowCount(0); // reset tabella
    // tipo richiesto -> se tutti falliscono è Item*
    Consumable* c = dynamic_cast<Consumable*>(x);
    overTime* ot  = dynamic_cast<overTime*>(x);
    Potion* pt    = dynamic_cast<Potion*>(x);
    Weapon* w     = dynamic_cast<Weapon*>(x);

    for(u_int i = 0; i < mod->invSize(); i++) {
        // tipo oggetto dell'inventario in esame
        Consumable* it_c  = dynamic_cast<Consumable*>(mod->searchItemByID(i));
        overTime*   it_ot = dynamic_cast<overTime*>(mod->searchItemByID(i));
        Potion*     it_pt = dynamic_cast<Potion*>(mod->searchItemByID(i));
        Weapon*     it_w  = dynamic_cast<Weapon*>(mod->searchItemByID(i));
        // esame di corrispondenza
        if(w && it_w)        {std::cout << "w\n"; loadRow(i);}
        else if(pt && it_pt) {std::cout << "p\n"; loadRow(i);}
        else if(ot && it_ot) {std::cout << "ot\n";loadRow(i);}
        else if(c && it_c)   {std::cout << "c\n"; loadRow(i);}
        else                 {std::cout << "i\n"; loadRow(i);}
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
    connect(dispTutto, SIGNAL(clicked(Item*)), this, SLOT(showOnly(Item*)));
    connect(dispCons,  SIGNAL(clicked(Item*)), this, SLOT(showOnly(Item*)));
    connect(dispOT,    SIGNAL(clicked(Item*)), this, SLOT(showOnly(Item*)));
    connect(dispPot,   SIGNAL(clicked(Item*)), this, SLOT(showOnly(Item*)));
    connect(dispWeap,  SIGNAL(clicked(Item*)), this, SLOT(showOnly(Item*)));
    // menu
}

Window::~Window() {
    delete mod;
}

void Window::setupGui() {
    setObjectName("Progetto PaO");
    resize(851, 595);
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
    actionTutti = new QAction("Tutti", this);
    actionConsumabili = new QAction("Consumabili", this);
    actionOggetti_a_Tempo = new QAction("Oggetti a Tempo", this);
    actionPozioni = new QAction("Pozioni", this);
    actionArmi_e_Scudi = new QAction("Armi e Scudi", this);
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
    dispTutto = new ShowButton(TUTTI, "Tutto", centralWidget);
    upButtonLayout->addWidget(dispTutto);
    dispCons = new ShowButton(CONSUMABILI, "Consumabili", centralWidget);
    upButtonLayout->addWidget(dispCons);
    dispOT = new ShowButton(TEMPO, "Oggetti a Tempo", centralWidget);
    upButtonLayout->addWidget(dispOT);
    dispPot = new ShowButton(POZIONI, "Pozioni", centralWidget);
    upButtonLayout->addWidget(dispPot);
    dispWeap = new ShowButton(ARMI, "Armi e Scudi", centralWidget);
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
    infoDisp->setMinimumSize(QSize(300, 549));
    infoLayout = new QVBoxLayout(infoDisp);
    centralHL->addLayout(infoLayout);

    // immagini
    imgDisp = new QWidget(infoDisp);
    imgDisp->setGeometry(QRect(0, 0, 301, 211));
    imgItem = new QLabel("ImgItem", imgDisp);
    imgItem->setGeometry(QRect(0, 0, 170, 151));
    imgPlayer = new QLabel("ImgPlayer", imgDisp);
    imgPlayer->setGeometry(QRect(150, 0, 170, 151));
    infoLayout->addWidget(imgDisp);

    // stat generale
    statDisp = new QWidget(infoDisp);
    statDisp->setGeometry(QRect(-1, -1, 301, 276));
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
    widgetSaveLoad->setGeometry(QRect(0, 0, 301, 61));
    layoutSaveLoad = new QHBoxLayout(widgetSaveLoad);
    layoutSaveLoad->setContentsMargins(0, 0, 0, 0);
    saveButton = new QPushButton("Salva", widgetSaveLoad);
    layoutSaveLoad->addWidget(saveButton);
    loadButton = new QPushButton("Carica", widgetSaveLoad);
    layoutSaveLoad->addWidget(loadButton);
    infoLayout->addWidget(widgetSaveLoad);

    centralHL->addWidget(infoDisp);

}
