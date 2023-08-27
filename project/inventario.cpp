#include "inventario.h"

#include "consumable.h"
#include "overTime.h"
#include "potion.h"
#include "regular.h"
#include "shield.h"

#include <iostream>
using std::cout; using std::endl;

Inventario::Inventario() : first(0) {}

Inventario::nodo::nodo() : itm(0), next(0) {}

Inventario::Inventario(const Inventario & other) : first(copia(other)) {}

Inventario& Inventario::operator=(const Inventario& other) {
    if(this != &other) {
        distruggi(first);
        first = copia(other);
    }
    return *this;
}

Inventario::nodo::~nodo() {
    delete itm;
}

void Inventario::distruggi(nodo* p) {
    if(p != nullptr) {
        nodo* q = p;
        while(p) {
            p = p->next;
            delete q;
            q = p;
        }
    }
}

Inventario::nodo* Inventario::copia(const Inventario& other) {
    Inventario inv;
    for(iteratore i = other.begin(); i != other.end(); i++) {
        inv.insert(other[i].clone());
    }
    return inv.first;
}

void Inventario::insert(Item *x) {
    setID(x);
    first = new nodo(x, first);
}

void Inventario::remove(Item *x) {
    if(first->itm != x) {
        nodo *current = first;
        nodo *prev = first;
        while(current && current->itm != x) {
            prev = current;
            current = current->next;
        }
        if(current) { // itm == x
            prev->next = current->next;
            current->next = nullptr;
            delete current;
        }
    } else {
        nodo *aux = first;
        first = first->next;
        delete aux;
    }
}

Inventario::nodo::nodo(Item* x, nodo* p)
    : itm(x), next(p) {  }

bool Inventario::iteratore::operator==(const iteratore& i) const  {
    return ptr == i.ptr;
}

bool Inventario::iteratore::operator!= (const iteratore& i) const {
    return ptr != i.ptr;
}

Inventario::iteratore& Inventario::iteratore::operator++() {
    if(ptr) ptr = ptr->next;
    return *this;
}

Inventario::iteratore Inventario::iteratore::operator++(int) {
    iteratore aux = *this;
    if(ptr) {ptr = ptr->next;}
    return aux;
}

Item& Inventario::iteratore::operator*() const {
    return *(ptr->itm);
}

Item* Inventario::iteratore::operator->() const {
    return ptr->itm;
}

u_int Inventario::getHighestID() const {
    u_int max = 0;
    for(iteratore i = begin(); i != end(); i++) {
        if(i->getID() > max) max = i->getID(); 
    }
    return max;
}

void Inventario::setID(Item* x) {
    if(first) x->setID(getHighestID()+1);
}

unsigned int Inventario::size() const {
    u_int size = 0;
    for(iteratore i = begin(); i != end(); i++) {
        size++;
    }
    return size;
}

Inventario::iteratore Inventario::begin() const {
    iteratore aux;
    aux.ptr = first;
    return aux;
}

Inventario::iteratore Inventario::end() const {
    iteratore aux;
    aux.ptr = nullptr;
    return aux;
}

Item& Inventario::operator[] (const Inventario::iteratore& i) const {
    return *((i.ptr)->itm);
}

Item* Inventario::nodo::fromJson(const QJsonObject &json)
{
    if (const QJsonValue v = json["tipo"]; v.isString()){
        if(v.toString() == "consumable") return (Consumable::fromJson(json)).clone();
        if(v.toString() == "overtime")   return (overtime::classe::overTime::fromJson(json)).clone();
        if(v.toString() == "potion")     return (potion::classe::Potion::fromJson(json)).clone();
        if(v.toString() == "regular")    return (Regular::fromJson(json)).clone();
        if(v.toString() == "shield")     return (Shield::fromJson(json)).clone();
    }
}

QJsonObject Inventario::nodo::toJson() const
{
    QJsonObject obj;

    Consumable* c = dynamic_cast<Consumable*>(this->itm);
    overtime::classe::overTime* ot = dynamic_cast<overtime::classe::overTime*>(this->itm);
    potion::classe::Potion* pt = dynamic_cast<potion::classe::Potion*>(this->itm);
    Regular* r = dynamic_cast<Regular*>(this->itm);
    Shield* s = dynamic_cast<Shield*>(this->itm);

    if(s) {obj["tipo"] = "shield";     obj["item"] = s->toJson(); }
    if(r) {obj["tipo"] = "regular";    obj["item"] = r->toJson(); }
    if(ot) {obj["tipo"] = "overtime";  obj["item"] = ot->toJson(); }
    if(pt) {obj["tipo"] = "potion";    obj["item"] = pt->toJson(); }
    if(c) {obj["tipo"] = "consumable"; obj["item"] = c->toJson(); }

    return obj;
}

Inventario Inventario::fromJson(const QJsonObject &json)
{
    Inventario inv;
    if (const QJsonValue v = json["itms"]; v.isArray()) {
        const QJsonArray jinv = v.toArray();
        for (const QJsonValue &jitm : jinv) {
            inv.insert(nodo::fromJson(jitm.toObject()));
        }
    }
    return inv;
}

QJsonObject Inventario::toJson() const
{
    QJsonObject obj;
    QJsonArray jarray;
    for(iteratore i = begin(); i != end(); i++) {
        jarray.append(i.ptr->toJson());
    }
    obj["itms"] = jarray;
    return obj;
}

void Inventario::clear() {
    distruggi(first);
}
