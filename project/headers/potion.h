#ifndef POTION_H
#define POTION_H

#include "consumable.h"
#include<string>
using std::string;

/* -- Per lettura/scrittura file JSON -- */
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

namespace potion {

    #define POTIONT_PIC  ":/consumabili/images/curaT.png"
    #define POTIONP_PIC ":/consumabili/images/curaV.png"

    enum tipo{POISON, TOXIC};

    namespace classe {
        class Potion : public Consumable
        {
            Q_OBJECT
        private:
            tipo t;
            virtual bool pathCorrectness() const;
            virtual void pathCorrect();
            Potion();
            static tipo intToTipo(int);
        public:
            Potion(tipo, const string& = "unnamed_item");
            Potion(const Potion&);
            Potion* clone() const override;
            tipo getType() const;
            string getTypeString() const;
            virtual string description() const;
            static Potion fromJson(const QJsonObject&);
            QJsonObject toJson() const;
        };
    }
}

#endif // POTION_H
