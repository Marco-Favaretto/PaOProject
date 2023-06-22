#include "inventario.h"

Inventario::Inventario() : first(0) {}

void Inventario::aggiungiInTesta(Item *x) {
    first = new nodo(x,first);
}

Inventario::nodo::nodo(Item* x, nodo* p)
    : itm(x), next(p){}

bool Inventario::iteratore::operator==(const iteratore& i) const  {
    return ptr == i.ptr;
}

bool Inventario::iteratore::operator!= (const iteratore& i) const {
    return ptr != i.ptr;
}

Inventario::iteratore& Inventario::iteratore::operator++() {
    if(ptr) ptr = ptr->next; return *this;
}

Inventario::iteratore Inventario::iteratore::operator++(int) {
    iteratore aux = *this; if(ptr) {ptr = ptr->next;} return aux;
}

Item& Inventario::iteratore::operator*() const {
    return *(ptr->itm);
}

Item* Inventario::iteratore::operator->() const {
    return ptr->itm;
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

