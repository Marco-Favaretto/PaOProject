#ifndef REGULAR_H
#define REGULAR_H

#include "weapon.h"

/* -- Per lettura/scrittura file JSON -- */
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

#define SPADA_PIC ":/weapon/images/spada.png"
#define STOCCO_PIC ":/weapon/images/stocco.png"
#define ASCIA_PIC ":/weapon/images/ascia.png"
#define MAZZA_PIC ":/weapon/images/mazza.png"

namespace regular {

    namespace Tipo {
        enum tipo{SPADA, STOCCO, ASCIA, MAZZA};
    }
    
    class Regular : public Weapon {
        Tipo::tipo t;
        bool pathCorrectness() const;
        void pathCorrect();
        static Tipo::tipo intToTipo(int);
    public:
        Regular(Tipo::tipo, u_int = 10, string = "unnamed_item", string = "error");
        Regular(const Regular&);
        Regular* clone() const override;
        virtual string description() const;
        u_int getATK() const;
        static Regular fromJson(const QJsonObject&);
        QJsonObject toJson() const;
    };
}
#endif // REGULAR_H
