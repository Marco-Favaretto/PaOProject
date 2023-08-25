#ifndef WINDOW_H
#define WINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <QMainWindow>
#include "showbutton.h"
#include "model.h"

class Window : public QMainWindow
{
    Q_OBJECT

private:
    model* mod;
    int rowSel;
    int colSel;

    void connectModel();
    void fillInv();
    void loadInv();
    void loadRow(u_int);
    void loadPlayerPic();
public:
    explicit Window(QWidget *parent = nullptr);
    ~Window();

private slots:
    // model
    void hpChanged();
    void statusChanged();
    void atkChanged();
    void defChanged();
    // tabella
    void cellSelected(int,int);
    // bottom Buttons
    void onRemoveButton();
    void onCreateButton();
    void onUseButton();
    void onEquipButton();
    // up Buttons
    void showOnly(tipo);
    // menu

// elementi gui
private:
    // metodi per la costruzione della gui
    void setupGui();
    void connectGui();

    // menu
    QMenuBar *menubar;
    // menu->file
    QMenu *menuFile;
    QAction *actionSalva;
    QAction *actionCarica;
    // menu->opzioni
    QMenu *menuOpzioni;
    QAction *actionCrea_oggetto;
    // menu->opzioni->mostra solo
    QMenu *menuMostra_Solo;
    QAction *actionTutti;
    QAction *actionConsumabili;
    QAction *actionOggetti_a_Tempo;
    QAction *actionPozioni;
    QAction *actionArmi_e_Scudi;
    // central widget
    QWidget *centralWidget; // QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *centralHL;

    // infodisplay
    QWidget *infoDisp;
    QVBoxLayout* infoLayout;
    // info display -> img
    QWidget *imgDisp;
    QHBoxLayout* imgLayout;
    QLabel *imgItem;
    QLabel *imgPlayer;
    // statDisp
    QWidget *statDisp;
    QVBoxLayout *statLayout; // QWidget *verticalLayoutWidget;
    // hp
    QHBoxLayout *statHL1;
    QLabel *hpLabel;
    QProgressBar *hpProgressBar;
    QLabel *hpValue;
    // status
    QHBoxLayout *statHL2;
    QLabel *statusLabel;
    QTextEdit *statusTxt;
    // atk
    QHBoxLayout *statHL3;
    QLabel *atkLabel;
    QTextEdit *atkTxt;
    // def
    QHBoxLayout *statHL4;
    QLabel *defLabel;
    QTextEdit *defTxt;
    // buttons for save and load
    QWidget *widgetSaveLoad; // QWidget *horizontalLayoutWidget;
    QHBoxLayout *layoutSaveLoad;
    QPushButton *saveButton;
    QPushButton *loadButton;

    // inventario
    QVBoxLayout *inv_layout;
    // buttons on top -> diventano buttons del mio tipo
    QHBoxLayout *upButtonLayout;
    ShowButton *dispTutto;
    ShowButton *dispCons;
    ShowButton *dispOT;
    ShowButton *dispPot;
    ShowButton *dispWeap;
    // table
    QTableWidget *invDisplay;
    // buttons on bottom
    QHBoxLayout *bottomButtonLayout;
    QPushButton *createButton;
    QPushButton *useButton;
    QPushButton *equipButton;
    QPushButton *removeButton;

};

#endif // WINDOW_H
