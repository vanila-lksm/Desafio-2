#ifndef LISTA_CPP
#define LISTA_CPP
#include "lista.h"
template <typename T>
typename Lista<T>::Nodo* Lista<T>::caminar(Nodo* actual, int pos, int indice) const {
    while (pos < indice) {
        actual = actual->sig; pos++;
    }
    while (pos > indice) {
        actual = actual->ant; pos--;
    }
    return actual;
}
template <typename T>
typename Lista<T>::Nodo* Lista<T>::nodoEnConst(int indice) const {
    if (indice <= tam - 1 - indice){
        return caminar(cabeza, 0, indice);
    }
    return caminar(cola, tam - 1, indice);
}
template <typename T>
typename Lista<T>::Nodo* Lista<T>::nodoEn(int indice) {
    int dCab=indice;
    int dCol=tam-1-indice;
    int dCur=tam;
    if (cursor !=0) {
        dCur=indice-indiceCursor;
        if (dCur<0){
            dCur=-dCur;
        }
    }
    Nodo* n;
    if (dCur<dCab && dCur<dCol){
        n=caminar(cursor,indiceCursor,indice);
    }
    else if (dCab<=dCol){
        n=caminar(cabeza,0,indice);
    }
    else{
        n=caminar(cola,tam-1,indice);
    }
    cursor=n;
    indiceCursor=indice;
    return n;
}
template <typename T>
void Lista<T>::enlazarAntesDe(Nodo* pos, Nodo* nuevo) {
    if (pos==0){
        nuevo->ant=cola;
        if (cola !=0){
            cola->sig=nuevo;
        }
        else{
            cabeza=nuevo;
        }
        cola=nuevo;
    }
    else {
        nuevo->sig=pos;
        nuevo->ant=pos->ant;
        if (pos->ant != 0){
            pos->ant->sig=nuevo;
        }
        else{
            cabeza = nuevo;
        }
        pos->ant = nuevo;
    }
    tam++;
}
template <typename T>
void Lista<T>::quitarNodo(Nodo* n) {
    if (n->ant != 0){
        n->ant->sig = n->sig;
    }
    else{
        cabeza = n->sig;
    }
    if (n->sig != 0){
        n->sig->ant = n->ant;
    }
        else{
        cola = n->ant;
    }
    delete n;
    tam--;
    cursor = 0;
}
template <typename T>
Lista<T>::Lista() : cabeza(0), cola(0), tam(0), cursor(0), indiceCursor(0) {}
template <typename T>
Lista<T>::Lista(const Lista& otra)
    : cabeza(0), cola(0), tam(0), cursor(0), indiceCursor(0) {
    for (Nodo* n = otra.cabeza; n != 0; n = n->sig) {
        agregarAlFinal(n->dato);

    }
}
template <typename T>
Lista<T>::~Lista() {
    vaciar();
}
template <typename T>
Lista<T>& Lista<T>::operator=(const Lista& otra) {
    if (this != &otra) {
        vaciar();
        for (Nodo* n = otra.cabeza; n != 0; n = n->sig) {
            agregarAlFinal(n->dato);

        }
    }
    return *this;
}
template <typename T>
T& Lista<T>::operator[](int indice) {
    return nodoEn(indice)->dato;
}
template <typename T>
const T& Lista<T>::operator[](int indice) const {
    return nodoEnConst(indice)->dato;
}
template <typename T>
Lista<T>& Lista<T>::operator+=(const T& dato) {
    agregarAlFinal(dato);
    return *this;
}
template <typename T>
Lista<T>& Lista<T>::operator+=(const Lista& otra) {
    int cantidad = otra.tam;
    Nodo* p = otra.cabeza;
    for (int i = 0; i < cantidad; i++) {
        agregarAlFinal(p->dato);
        p = p->sig;

    }
    return *this;
}
template <typename T>
void Lista<T>::agregarAlFinal(const T& dato) {
    enlazarAntesDe(0, new Nodo(dato));
}
template <typename T>
void Lista<T>::agregarAlInicio(const T& dato) {
    enlazarAntesDe(cabeza, new Nodo(dato));
    if (cursor != 0) indiceCursor++;
}
template <typename T>
bool Lista<T>::insertarEn(int indice, const T& dato) {
    if (indice<0 || indice>tam)
        return false;
    if (indice==tam) {
        agregarAlFinal(dato);
        return true;
    }
    if (indice==0){
        agregarAlInicio(dato);
        return true;
    }
    enlazarAntesDe(nodoEn(indice), new Nodo(dato));
    cursor=0;
    return true;
}
template <typename T>
void Lista<T>::insertarOrdenado(const T& dato) {
    Nodo* pos=0;
    Nodo* n=cola;
    while (n !=0 && dato< n ->dato) {
        pos=n;
        n=n->ant;

    }
    enlazarAntesDe(pos,new Nodo(dato));
    cursor = 0;
}
template <typename T>
bool Lista<T>::eliminarPrimero() {
    if (cabeza == 0)
        return false;
    quitarNodo(cabeza);
    return true;
}
template <typename T>
bool Lista<T>::eliminarUltimo() {
    if (cola == 0) return false;
    quitarNodo(cola);
    return true;
}

template <typename T>
bool Lista<T>::eliminarEn(int indice) {
    if (indice < 0 || indice >= tam)
        return false;
    quitarNodo(nodoEn(indice));
    return true;
}
template <typename T>
void Lista<T>::vaciar() {
    Nodo* n =cabeza;
    while (n !=0) {
        Nodo* sig=n->sig;
        delete n;
        n=sig;

    }
    cabeza=0;
    cola=0;
    tam=0;
    cursor=0;
}

#endif // LISTA_CPP


