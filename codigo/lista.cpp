#ifndef LISTA_CPP
#define LISTA_CPP
#include "lista.h"
#include <stdexcept>

template <typename T>
Nodo<T>* lista<T>::caminar(Nodo<T>* actual, int pos, int indice, unsigned long& iteraciones)
    const {
    while (pos<indice) {
        actual=actual->sig;pos++;
        iteraciones++;
    }
    while (pos > indice) {
        actual = actual->ant; pos--;
        iteraciones++;
    }
    return actual;
}
template <typename T>
Nodo<T>* lista<T>::nodoEn(int indice, unsigned long& iteraciones) const {
    if (indice < 0 || indice >= tam)
        throw std::out_of_range("lista: indice fuera de rango");
    int dCab=indice;
    int dCol=tam-1-indice;
    int dCur=tam;
    if (cursor !=0) {
        dCur=indice-indiceCursor;
        if (dCur<0) {
            dCur=-dCur;
        }
    }
    Nodo<T>* n;
    if (dCur<dCab && dCur<dCol) {
        n = caminar(cursor,indiceCursor,indice,iteraciones);
    }
    else if (dCab <=dCol) {
        n =caminar(cabeza,0,indice,iteraciones);
    }
    else {
        n=caminar(cola,tam-1,indice,iteraciones);
    }
    cursor=n;
    indiceCursor=indice;
    return n;
}
template <typename T>
void lista<T>::enlazarAntesDe(Nodo<T>* pos, Nodo<T>* nuevo) {
    if (pos==0) {
        nuevo->ant=cola;
        if (cola !=0) {
            cola->sig=nuevo;
        }
        else {
            cabeza=nuevo;
        }
        cola=nuevo;
    }
    else {
        nuevo->sig=pos;
        nuevo->ant=pos->ant;
        if (pos->ant !=0) {
            pos->ant->sig=nuevo;
        }
        else {
            cabeza=nuevo;
        }
        pos->ant=nuevo;
    }
    tam++;
}
template <typename T>
void lista<T>::quitarNodo(Nodo<T>* n) {
    if (n->ant !=0) {
        n->ant->sig=n->sig;
    }
    else {
        cabeza=n->sig;
    }
    if (n->sig !=0) {
        n->sig->ant=n->ant;
    }
    else {
        cola=n->ant;
    }
    delete n;
    tam--;
    cursor=0;
}
template <typename T>
lista<T>::lista() : cabeza(0), cola(0), tam(0), cursor(0), indiceCursor(0) {}
template <typename T>
lista<T>::lista(const lista& otra)
    : cabeza(0),cola(0),tam(0),cursor(0),indiceCursor(0) {
    for (Nodo<T>* n=otra.cabeza; n !=0;n=n->sig) {
        agregarAlFinal(n->dato);
    }
}
template <typename T>
lista<T>::~lista() {
    vaciar();
}
template <typename T>
lista<T>& lista<T>::operator=(const lista& otra) {
    if (this !=&otra) {
        vaciar();
        for (Nodo<T>* n = otra.cabeza; n !=0;n=n->sig) {
            agregarAlFinal(n->dato);
        }
    }
    return *this;
}
template <typename T>
T& lista<T>::operator[](int indice) {
    unsigned long basura = 0;
    return nodoEn(indice, basura)->dato;
}
template <typename T>
const T& lista<T>::operator[](int indice) const {
    unsigned long basura=0;
    return nodoEn(indice,basura)->dato;
}
template <typename T>
T& lista<T>::en(int indice, unsigned long& iteraciones) {
    return nodoEn(indice,iteraciones)->dato;
}
template <typename T>
const T& lista<T>::en(int indice, unsigned long& iteraciones) const {
    return nodoEn(indice,iteraciones)->dato;
}
template <typename T>
bool lista<T>::operator==(const lista& otra) const {
    if (tam !=otra.tam) return false;
    Nodo<T>* a=cabeza;
    Nodo<T>* b=otra.cabeza;
    while (a !=0) {
        if (!(a->dato==b->dato)) return false;
        a=a->sig;
        b=b->sig;
    }
    return true;
}
template <typename T>
unsigned long lista<T>::memoria() const {
    return (unsigned long)tam * sizeof(Nodo<T>);
}
template <typename T>
void lista<T>::concatenar(const lista& otra) {
    int cantidad=otra.tam;
    Nodo<T>* p=otra.cabeza;
    for (int i=0;i<cantidad;i++) {
        agregarAlFinal(p->dato);
        p=p->sig;
    }
}
template <typename T>
void lista<T>::agregarAlFinal(const T& dato) {
    enlazarAntesDe(0,new Nodo<T>(dato));
}
template <typename T>
void lista<T>::agregarAlInicio(const T& dato) {
    enlazarAntesDe(cabeza, new Nodo<T>(dato));
    if (cursor !=0) indiceCursor++;
}
template <typename T>
bool lista<T>::insertarEn(int indice, const T& dato) {
    if (indice<0 || indice>tam)
        return false;
    if (indice==tam) {
        agregarAlFinal(dato);
        return true;
    }
    if (indice==0) {
        agregarAlInicio(dato);
        return true;
    }
    unsigned long basura=0;
    enlazarAntesDe(nodoEn(indice, basura), new Nodo<T>(dato));
    cursor=0;
    return true;
}
template <typename T>
void lista<T>::insertarOrdenado(const T& dato) {
    Nodo<T>* pos=0;
    Nodo<T>* n=cola;
    while (n !=0 && dato < n->dato) {
        pos=n;
        n=n->ant;
    }
    enlazarAntesDe(pos, new Nodo<T>(dato));
    cursor=0;
}
template <typename T>
bool lista<T>::eliminarPrimero() {
    if (cabeza==0)
        return false;
    quitarNodo(cabeza);
    return true;
}
template <typename T>
bool lista<T>::eliminarUltimo() {
    if (cola==0) return false;
    quitarNodo(cola);
    return true;
}
template <typename T>
bool lista<T>::eliminarEn(int indice) {
    if (indice<0 || indice>=tam)
        return false;
    unsigned long basura=0;
    quitarNodo(nodoEn(indice,basura));
    return true;
}
template <typename T>
void lista<T>::vaciar() {
    Nodo<T>* n=cabeza;
    while (n !=0) {
        Nodo<T>* sig=n->sig;
        delete n;
        n=sig;
    }
    cabeza=0;
    cola=0;
    tam=0;
    cursor=0;
    indiceCursor=0;
}
template <typename T>
int lista<T>::buscar(const T& dato, unsigned long& iteraciones) const {
    Nodo<T>* actual = cabeza;
    int pos = 0;
    while (actual != 0) {
        iteraciones++;
        if (actual->dato == dato) {
            cursor = actual;
            indiceCursor = pos;
            return pos;
        }
        actual = actual->sig;
        pos++;
    }
    return -1; // No encontrado
}

#endif // LISTA_CPP