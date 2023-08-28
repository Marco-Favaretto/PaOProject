#ifndef CREATIONDIALOG_H
#define CREATIONDIALOG_H

#include <QDialog>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QListWidget>
#include <QLineEdit>
#include <QString>
#include <iostream>
using std::string;

#include "item.h"

class creationDialog : public QDialog {
    Q_OBJECT
private:
    QVBoxLayout* v1;
    QLabel* introLabel;
    QListWidget* listTipi;
    QGroupBox* modGB;
    QVBoxLayout* v2;
    QLabel* modLabel;
    QHBoxLayout* h1;
    QLabel* tipolabel;
    QComboBox* tipobox;
    QVBoxLayout* v3;
    QHBoxLayout* h2;
    QLabel* hplabel;
    QLineEdit* effettoLineEdit;
    QHBoxLayout* h2Turni;
    QLabel* turnilabel;
    QLineEdit* turniLineEdit;
    QHBoxLayout* h3;
    QLabel* nomelabel;
    QComboBox* nomeComboBox;
    QPushButton* creaButton;

    int rowSel;
    string fromComboTipo;
    int effetto;
    string nome;
    int turni;

    bool tipo;
    bool effect;
    bool nomeCheck;

    void setupDialog();
    void comboBoxTipo();
    void comboBoxNome();
    bool doneEverything() const;
public:
    creationDialog(QWidget* parent = nullptr);
    void resetDialog();
private slots:
    void onListWidget(int);
    void onTipoBox(QString);
    void onNomeBox(QString);
    void onEffetto(QString);
    void onCreateButton();
    void onturni(QString);
signals:
    void onCreationButton(Item*);
};

#endif // CREATIONDIALOG_H
