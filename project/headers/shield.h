#ifndef SHIELD_H
#define SHIELD_H

#include "weapon.h"

/* -- Per lettura/scrittura file JSON -- */
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

#define SCUDOLEGNO_PIC ":/weapon/images/scudodilegno.png"
#define SCUDOMEDIO_PIC ":/weapon/images/scudomedio.png"
#define SCUDOGRANDE_PIC ":/weapon/images/scudogrande.png"

namespace shield {
    
    namespace Tipo {
        enum tipo{LEGNO, MEDIO, GRANDE};
    }

    class Shield : public Weapon {
        Tipo::tipo t;
        virtual bool pathCorrectness() const;
        virtual void pathCorrect();
        static Tipo::tipo intToTipo(int);
    public:
        Shield(Tipo::tipo, u_int = 10, const string& = "unnamed_item");
        Shield(const Shield&);
        Shield* clone() const override;
        virtual string description() const;
        u_int getDEF() const;
        static Shield fromJson(const QJsonObject&);
        QJsonObject toJson() const;
    };
}
#endif // SHIELD_H
