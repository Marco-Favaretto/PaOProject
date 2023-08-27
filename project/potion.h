#ifndef POTION_H
#define POTION_H

#include "consumable.h"
#include<string>
using std::string;

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
            bool pathCorrectness() const;
            void pathCorrect();
        public:
            Potion(tipo, string = "unnamed_item", string = "error");
            Potion(const Potion&);
            Potion* clone() const override;
            tipo getType() const;
            string getTypeString() const;
            virtual string description() const;
        };
    }
}
#endif // POTION_H
