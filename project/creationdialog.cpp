#include "creationdialog.h"

#include <QStringList>
#include <QMessageBox>

#include "consumable.h"
#include "potion.h"
using namespace potion::classe;
#include "shield.h"
#include "regular.h"
#include "overTime.h"
using namespace overtime::classe;

void creationDialog::setupDialog() {

    resize(394, 561);
    setMinimumSize(QSize(394, 561));
    setMaximumSize(QSize(394, 561));

    v1 = new QVBoxLayout(this);
    v1->setContentsMargins(10, 10, 10, 10);

    introLabel = new QLabel("Selezionare il tipo di oggetto da creare", this);
    v1->addWidget(introLabel);
    listTipi = new QListWidget(this);
    QStringList listaTipi;
    listaTipi.append("1) Consumabili");
    listaTipi.append("2) Oggetti a Tempo (veleno o tossicità)");
    listaTipi.append("3) Pozione per guarire da veleno o tossicità");
    listaTipi.append("4) Armi");
    listaTipi.append("5) Scudi");
    listTipi->addItems(listaTipi);
    v1->addWidget(listTipi);

    modGB = new QGroupBox("Modifica le variabili dell'oggetto", this);
    modGB->setMinimumSize(QSize(0, 300));
    v2 = new QVBoxLayout(modGB);
    v2->setContentsMargins(0, 0, 0, 0);

    h1 = new QHBoxLayout(modGB);
    tipolabel = new QLabel("Tipologia", modGB);
    h1->addWidget(tipolabel);
    tipobox = new QComboBox(modGB);
    h1->addWidget(tipobox);

    v2->addLayout(h1);

    v3 = new QVBoxLayout(modGB);

    h2 = new QHBoxLayout(modGB);
    hplabel = new QLabel("Effetto oggetto (può essere un numero negativo)", modGB); // se ot -> solo neg
    h2->addWidget(hplabel);
    effettoLineEdit = new QLineEdit(modGB);
    effettoLineEdit->setReadOnly(true);
    h2->addWidget(effettoLineEdit);
    h2Turni = new QHBoxLayout(modGB);
    turnilabel = new QLabel("Turni (solo per ogg. a tempo)", modGB);
    turniLineEdit = new QLineEdit(modGB);
    turniLineEdit->setPlaceholderText("Solo positivi, di default: infinito");

    h2Turni->addWidget(turnilabel);
    h2Turni->addWidget(turniLineEdit);
    turniLineEdit->setReadOnly(true);

    v3->addLayout(h2);
    v3->addLayout(h2Turni);
    v2->addLayout(v3);

    h3 = new QHBoxLayout();
    nomelabel = new QLabel("Nome Oggetto", modGB);
    h3->addWidget(nomelabel);
    nomeComboBox = new QComboBox(modGB);
    h3->addWidget(nomeComboBox);

    v2->addLayout(h3);

    v1->addWidget(modGB);

    creaButton = new QPushButton("Crea Oggetto", this);
    v1->addWidget(creaButton);

}

void creationDialog::comboBoxTipo() {
    tipobox->setPlaceholderText("");
    tipobox->clear();
    QStringList lista;
    switch(rowSel) {
    case 0: // consumabili
        tipobox->setPlaceholderText("Nessuna azione disponibile");
        effettoLineEdit->setReadOnly(false);
        turniLineEdit->setReadOnly(true);
        tipo = true;
        break;
    case 1: // ot
        lista.append("Veleno");
        lista.append("Tossicità");
        tipobox->addItems(lista);
        hplabel->setText("Effetto oggetto (solo valori negativi)");
        effettoLineEdit->setPlaceholderText("Solo valori negativi");
        effettoLineEdit->setReadOnly(false);
        turniLineEdit->setReadOnly(false);
        break;
    case 2: // pozioni
        lista.append("Veleno");
        lista.append("Tossicità");
        tipobox->addItems(lista);
        effettoLineEdit->setPlaceholderText("Nessuna azione disponibile");
        effettoLineEdit->setReadOnly(true);
        turniLineEdit->setReadOnly(true);
        effect = true;
        break;
    case 3: // armi
        lista.append("Spada");
        lista.append("Ascia");
        lista.append("Mazza");
        tipobox->addItems(lista);
        hplabel->setText("Effetto oggetto (solo valori positvi)");
        effettoLineEdit->setPlaceholderText("Solo valori positivi");
        effettoLineEdit->setReadOnly(false);
        turniLineEdit->setReadOnly(true);
        break;
    case 4: // scudi
        lista.append("Scudo di legno");
        lista.append("Scudo medio");
        lista.append("Scudo grande");
        tipobox->addItems(lista);
        hplabel->setText("Effetto oggetto (solo valori positvi)");
        effettoLineEdit->setPlaceholderText("Solo valori positivi");
        effettoLineEdit->setReadOnly(false);
        turniLineEdit->setReadOnly(true);
        break;
    default: // -1
        tipobox->setPlaceholderText("");
        tipobox->clear();
        effettoLineEdit->setReadOnly(true);
        turniLineEdit->setReadOnly(true);
        effettoLineEdit->setPlaceholderText("");
        break;
    }
}

void creationDialog::comboBoxNome() {
    nomeComboBox->clear();
    QStringList lista;
    switch(rowSel) {
    case 0: // consumabili
        if(effetto >= 0) lista.append("Cura");
        else lista.append("Pastiglia");
        nomeComboBox->addItems(lista);
        break;
    case 1: // ot
        if(fromComboTipo == "Veleno") {
            lista.append("Veleno");
            lista.append("Poison");
        } else {
            lista.append("Tossicità");
            lista.append("Toxic");
        }
        nomeComboBox->addItems(lista);
        break;
    case 2: // pozioni
        if(fromComboTipo == "Veleno") {
            lista.append("Pozione-V");
        } else {
            lista.append("Pozione-T");
        }
        nomeComboBox->addItems(lista);
        break;
    case 3: // armi
        if(fromComboTipo == "Spada") {lista.append("Stocco"); lista.append("Spada"); }
        else if(fromComboTipo == "Ascia") {lista.append("Ascia");}
        else lista.append("Mazza");
        nomeComboBox->addItems(lista);
        break;
    case 4: // scudi
        if(fromComboTipo == "Scudo di legno") lista.append("Scudo di legno");
        else if(fromComboTipo == "Scudo medio") lista.append("Scudo medio");
        else lista.append("Scudo grande");
        nomeComboBox->addItems(lista);
        break;
    default:
//        nomeComboBox->clear();
//        nomeComboBox->addItem("");
        break;
    }
}

bool creationDialog::doneEverything() const {
    return tipo && effect && nomeCheck;
}

void creationDialog::resetDialog() {
//    setupDialog();
    effettoLineEdit->clear();
    turniLineEdit->clear();
    effettoLineEdit->setReadOnly(true);
    turniLineEdit->setReadOnly(true);
    rowSel = -1;
    fromComboTipo = "";
    effetto = 0;
    nome = "";
    tipo = false;
    effect = false;
    nomeCheck = false;
}

creationDialog::creationDialog(QWidget* parent) :
    QDialog(parent), rowSel(-1),
    fromComboTipo(""), effetto(0), nome(""), turni(-1),
    tipo(false), effect(false), nomeCheck(false)
{
    setupDialog();
    tipobox->setPlaceholderText("Tipologia Oggetto");
    nomeComboBox->setPlaceholderText("Nome Oggetto");
    connect(listTipi, SIGNAL(currentRowChanged(int)), this, SLOT(onListWidget(int)));
    connect(tipobox, SIGNAL(currentTextChanged(QString)), this, SLOT(onTipoBox(QString)));
    connect(nomeComboBox, SIGNAL(currentTextChanged(QString)), this, SLOT(onNomeBox(QString)));
    connect(creaButton, SIGNAL(clicked()), this, SLOT(onCreationButton()));
    connect(effettoLineEdit, SIGNAL(textEdited(QString)), this, SLOT(onEffetto(QString)));
    connect(turniLineEdit, SIGNAL(textEdited(QString)), this, SLOT(onturni(QString)));
}

void creationDialog::onListWidget(int _row) {
    resetDialog();
    rowSel = _row;
    comboBoxTipo();
    comboBoxNome();
}

void creationDialog::onTipoBox(QString row) {
    fromComboTipo = row.toStdString();
    tipo = true;
    comboBoxNome();
}

void creationDialog::onEffetto(QString lineEdited) {
    effetto = lineEdited.toInt();
    effect = true;
}

void creationDialog::onNomeBox(QString row) {
    nome = row.toStdString();
    nomeCheck = true;
}


void creationDialog::onturni(QString _t) {
    turni = _t.toInt();
    if(turni < 0) QMessageBox::warning(this, "Turni", "Scegliere un numero positivo.");
}

void creationDialog::onCreationButton() {

    if(!doneEverything()) {
        QMessageBox::warning(this, "Missing Fields", "Completare l'intero Form");
        resetDialog();
    } else {
        switch(rowSel) {
        case 0: // consumabili
            emit onCreateButton(new Consumable(effetto, nome));
            break;
        case 1: // ot
            if(effetto > 0) {effect = false; QMessageBox::warning(this, "Effetto", "L'effetto deve essere negativo");}
            else if(fromComboTipo == "Veleno") emit onCreateButton(new overTime(overtime::POISON, effetto, turni, nome));
            else emit onCreateButton(new overTime(overtime::TOXIC, effetto, turni, nome));
            break;
        case 2: // pozioni
            if(fromComboTipo == "Veleno") emit onCreateButton(new Potion(potion::POISON, nome));
            else emit onCreateButton(new Potion(potion::TOXIC, nome));
            break;
        case 3: // armi
            if(effetto < 0) {effect = false; QMessageBox::warning(this, "Effetto", "L'effetto deve essere positivo");}
            else emit onCreateButton(new Regular(effetto, nome));
            break;
        case 4: // scudi
            if(effetto < 0) {effect = false; QMessageBox::warning(this, "Effetto", "L'effetto deve essere positivo");}
            else emit onCreateButton(new Shield(effetto, nome));
            break;
        default: // -1
            break;
        }
    }
}
