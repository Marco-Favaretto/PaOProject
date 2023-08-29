#ifndef CONSUMABLE_H
#define CONSUMABLE_H

#include "item.h"

#include<string>
using std::string;
/* -- Per lettura/scrittura file JSON -- */
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

#define CURA_PIC ":/consumabili/images/curaHP.png"
#define PASTIGLIA_PIC ":/consumabili/images/pastiglia.png"

class Consumable : public Item {
    Q_OBJECT
    private:
        int hpEffect;
        bool pathCorrectness() const;
        void pathCorrect();
    public:
        Consumable(int=0, const string& = "unnamed_item", const string& = "error");
        Consumable(const Consumable&);
        virtual ~Consumable();
        int getEffect() const;
        void setEffect(int);
        virtual string description() const;
        Consumable* clone() const override;
        static Consumable fromJson(const QJsonObject&);
        QJsonObject toJson() const;
    public slots:
        virtual void effect();
    signals:
       void effectSignal(int);
};

#endif // CONSUMABLE_H
