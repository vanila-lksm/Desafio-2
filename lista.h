#ifndef LISTA_H
#define LISTA_H
#include "mensaje.h"

class lista {
private:
    struct Nodo {
        mensaje* dato;
        Nodo* siguiente;
        Nodo* anterior;
        Nodo(mensaje*val):dato(val),siguiente(nullptr),anterior(nullptr){}
    };

    Nodo* cabeza;
    Nodo* cola;
    int cantidad;
public:
    lista();
    lista(const lista& otro);
    ~lista();
    lista& operator=(const lista& otro);
    void agregar(mensaje* elemento);
    mensaje* obtener(int indice) const;
    int tamano() const;
    void eliminar(int indice);
};

#endif // LISTA_H