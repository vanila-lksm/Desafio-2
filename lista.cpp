#include "lista.h"

lista::lista() {
    cabeza=nullptr;
    cola=nullptr;
    cantidad=0;
}
lista::~lista() {
    Nodo* actual=cabeza;
    while (actual !=nullptr) {
        Nodo* siguienteNodo=actual->siguiente;
        delete actual;
        actual=siguienteNodo;
    }
}
lista::lista(const lista& otro) {
    cabeza=nullptr;
    cola=nullptr;
    cantidad=0;
    Nodo* actual=otro.cabeza;
    while (actual !=nullptr) {
        agregar(actual->dato);
        actual=actual->siguiente;
    }
}
lista& lista::operator=(const lista& otro) {
    if (this == &otro) return *this;
    Nodo* actual=cabeza;
    while (actual !=nullptr) {
        Nodo* siguienteNodo=actual->siguiente;
        delete actual;
        actual=siguienteNodo;
    }
    cabeza=nullptr;
    cola=nullptr;
    cantidad=0;
    Nodo* actualOtro=otro.cabeza;
    while (actualOtro !=nullptr) {
        agregar(actualOtro->dato);
        actualOtro = actualOtro->siguiente;
    }
    return *this;
}
void lista::agregar(mensaje* elemento) {
    Nodo* nuevoNodo=new Nodo(elemento);
    if (cabeza==nullptr) {
        cabeza=nuevoNodo;
        cola=nuevoNodo;
    } else {
        cola->siguiente=nuevoNodo;
        nuevoNodo->anterior=cola;
        cola=nuevoNodo;
    }
    cantidad++;
}
mensaje* lista::obtener(int indice) const {
    if (indice<0 || indice>=cantidad) {
        return nullptr;
    }
    Nodo* actual=cabeza;
    for (int i=0;i<indice;i++) {
        actual=actual->siguiente;
    }
    return actual->dato;
}
int lista::tamano() const {
    return cantidad;
}
void lista::eliminar(int indice) {
    if (indice<0 || indice>=cantidad) return;
    Nodo* nodo_eliminar=cabeza;
    if (indice==0){
        cabeza=cabeza->siguiente;
        if (cabeza !=nullptr) {
            cabeza->anterior=nullptr;
        } else {
            cola=nullptr;
        }
    } else {
        for (int i=0;i<indice;i++) {
            nodo_eliminar=nodo_eliminar->siguiente;
        }
        nodo_eliminar->anterior->siguiente=nodo_eliminar->siguiente;
        if (nodo_eliminar->siguiente !=nullptr) {
            nodo_eliminar->siguiente->anterior=nodo_eliminar->anterior;
        } else {
            cola=nodo_eliminar->anterior;
        }
    }
    delete nodo_eliminar;
    cantidad--;
}
