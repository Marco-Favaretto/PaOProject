#ifndef INVENTARIO_H
#define INVENTARIO_H

#include "item.h"

#define u_int unsigned int


class Inventario {
    private:                  //dopo C++03 non serve mettere "friend class iteratore;"
        class nodo {
            public:
                nodo();
                nodo(Item* x, nodo* p);
                Item* itm;
                nodo* next;
                // u_int quantity;
        };
        nodo* first;
    public:
        class iteratore {
            friend class Inventario;
            private:
                Inventario::nodo* ptr;
            public:
                bool operator== (const iteratore& i) const;
                bool operator!= (const iteratore& i) const;
                iteratore& operator++();
                iteratore operator++(int);
                Item& operator*() const;
                Item* operator->() const;
        };
        iteratore begin() const;
        iteratore end() const;
        Item& operator[] (const iteratore&) const;

        Inventario();
        void aggiungiInTesta(Item* x);
};

#endif // INVENTARIO_H
