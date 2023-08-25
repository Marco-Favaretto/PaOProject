#ifndef POTION_H
#define POTION_H

#include "consumable.h"
#include<string>
using std::string;

namespace potion {

#define TOXIC_PIC  ":/consumabili/images/curaT.png"
#define POISON_PIC ":/consumabili/images/curaV.png"

    enum tipo{POISON, TOXIC};

    namespace classe {
        class Potion : public Consumable
        {
            Q_OBJECT
        private:
            tipo t;
        public:
            Potion(tipo, string = "unnamed_item", string = "error");
            tipo getType() const;
            string getTypeString() const;
            virtual string description() const;
        };
    }
}
#endif // POTION_H
