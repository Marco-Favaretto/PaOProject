#include "window.h"

Window::Window(QWidget *parent)
    : QMainWindow{parent}, mod(new model(new Player(), Inventario())), rowSel(-1), colSel(-1)
{
    setupGui();
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
    dispTutto = new ShowButton("Tutto", centralWidget);
    upButtonLayout->addWidget(dispTutto);
    dispCons = new ShowButton("Consumabili", centralWidget);
    upButtonLayout->addWidget(dispCons);
    dispOT = new ShowButton("Oggetti a Tempo", centralWidget);
    upButtonLayout->addWidget(dispOT);
    dispPot = new ShowButton("Pozioni", centralWidget);
    upButtonLayout->addWidget(dispPot);
    dispWeap = new ShowButton("Armi e Scudi", centralWidget);
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
