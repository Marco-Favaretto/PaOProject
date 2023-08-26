#ifndef GAMEOVERDIALOG_H
#define GAMEOVERDIALOG_H

#include <QLabel>
#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>

class gameOverDialog : public QDialog {
    Q_OBJECT
    private:
        QLabel* lp;
        QLabel* l;
        QVBoxLayout* v;
        QVBoxLayout* v2;
        QHBoxLayout* h2;
        QPushButton* end;
        QPushButton* ng;
    public:
        gameOverDialog(QWidget* parent = nullptr);
    public slots:
        void endGameSlot();
        void newGameSlot();
    signals:
        void endgame();
        void reroll();
};

#endif // GAMEOVERDIALOG_H
