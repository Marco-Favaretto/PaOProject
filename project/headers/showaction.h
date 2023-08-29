#ifndef SHOWACTION_H
#define SHOWACTION_H

#include <QAction>
#include <QString>
#include "showbutton.h"


namespace showaction {

    class ShowAction : public QAction
    {
        Q_OBJECT
    private:
        showbutton::tipo t;
    public:
        ShowAction(showbutton::tipo, const QString& title, QObject* parent = nullptr);
    public slots:
        void onClicked();
    signals:
        void trig(showbutton::tipo);
    };
}

#endif // SHOWACTION_H
