#ifndef SHOWBUTTON_H
#define SHOWBUTTON_H

#include <QPushButton>
#include <QString>


namespace showbutton {
    enum tipo {TUTTI, CONSUMABILI, TEMPO, POZIONI, ARMI};

    class ShowButton : public QPushButton
    {
        Q_OBJECT
    private:
        tipo t;
    public:
        ShowButton(tipo, const QString& title, QWidget* parent = nullptr);
    public slots:
        void onClicked();
    signals:
        void click(showbutton::tipo);
    };
}

#endif // SHOWBUTTON_H
