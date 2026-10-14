#ifndef NODO_CPP
#define NODO_CPP
#include "nodo.h"

template <typename T>
Nodo<T>::Nodo(const T& d) : dato(d), sig(0), ant(0) {}

#endif // NODO_CPP