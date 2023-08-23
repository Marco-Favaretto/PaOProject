#ifndef POTION_H
#define POTION_H

#include "consumable.h"
#include<string>
using std::string;

namespace potion {

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
        };
    }
}
#endif // POTION_H
