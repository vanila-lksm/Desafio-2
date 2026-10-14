#ifndef NODO_H
#define NODO_H

template <typename T>
class Nodo {
public:
    T dato;
    Nodo<T>* sig;
    Nodo<T>* ant;
    Nodo(const T& d);
};

#include "nodo.cpp"
#endif // NODO_H