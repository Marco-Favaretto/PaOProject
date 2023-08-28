#ifndef INVENTARIO_H
#define INVENTARIO_H

#include "item.h"

#define u_int unsigned int

/* -- Per lettura/scrittura file JSON -- */
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

class Inventario {
    private:
        class nodo {
            public:
                nodo();
                nodo(Item* x, nodo* p);
                ~nodo();
                Item* itm;
                nodo* next;
                static Item* fromJson(const QJsonObject&);
                QJsonObject toJson() const;
        };
        nodo* first;
        u_int getHighestID() const;
        void setID(Item*);
        static nodo* copia(const Inventario&);
        static void distruggi(nodo*);
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

        void fromJson(const QJsonObject&);
        QJsonObject toJson() const;

        Inventario();
        Inventario(const Inventario&);
        Inventario& operator=(const Inventario&);
        // ~Inventario();
        u_int size() const;
        void insert(Item*);
        void remove(Item*);
        void clear();
};

#endif // INVENTARIO_H
