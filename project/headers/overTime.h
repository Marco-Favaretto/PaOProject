#ifndef OVERTIME_H
#define OVERTIME_H

#include "consumable.h"

#define u_int unsigned int
#include<string>
using std::string;

/* -- Per lettura/scrittura file JSON -- */
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

#include <QTimer>

namespace overtime {

    #define STDTIMERPOISON 2000
    #define STDTIMERTOXIC 500
    #define MAXCOUNTER 10
    #define INFCOUNTER -1
    #define TOXIC_PIC  ":/consumabili/images/tossicita.png"
    #define POISON_PIC ":/consumabili/images/veleno.png"

    enum tipo {POISON, TOXIC};

    namespace classe {

        class overTime : public Consumable {
            Q_OBJECT
        private:
            QTimer* timer;
            bool status;
            int counter;
            tipo t;
            virtual bool pathCorrectness() const;
            virtual void pathCorrect();
            overTime();
            void setTimer(int);
            static tipo intToTipo(int);
        public:
            overTime(tipo, int hp = -10, int c = INFCOUNTER, const string& = "unnamed_item");
            overTime(const overTime&);
            overTime* clone() const override;
            bool isActive() const;
            double getTimer() const;
            virtual string description() const;
            tipo getType() const;
            static overTime fromJson(const QJsonObject&);
            QJsonObject toJson() const;
        public slots:
            virtual void effect();
            void stopOT();
            void startOT();
        signals:
            void over(overtime::classe::overTime*);
        };
    }
}

#endif // OVERTIME_H
