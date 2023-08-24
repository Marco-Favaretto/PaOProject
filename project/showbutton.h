#ifndef SHOWBUTTON_H
#define SHOWBUTTON_H

#include <QPushButton>
#include <QString>

class ShowButton : public QPushButton
{
    Q_OBJECT
public:
    ShowButton(QString title, QWidget* parent = nullptr);
};

#endif // SHOWBUTTON_H
