#include "inventario.h"

#include <iostream>
using std::cout; using std::endl;

Inventario::Inventario() : first(0) {}

Inventario::Inventario(const Inventario & other) {
    for(iteratore i = other.begin(); i != other.end(); i++) {
//        insert(new Item(other[i]));
    }
}

Inventario::nodo::~nodo() {
    delete itm;
}

// void Inventario::distruggi(nodo* p) {
//     if(p) {
//         distruggi(p->next);  //scorre tutta la lista e dealloca dall'ultimo al primo
//         delete p;
//     }
// }

// Inventario::~Inventario() {
//     if(first) distruggi(first);
// }

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
