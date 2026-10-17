#ifndef LISTA_H
#define LISTA_H
#include "nodo.h"
#include <stdexcept>

template <typename T>
class lista {
private:
    Nodo<T>* cabeza;
    Nodo<T>* cola;
    int tam;
    mutable Nodo<T>* cursor;
    mutable int   indiceCursor;
    Nodo<T>* caminar(Nodo<T>* actual, int pos, int indice, unsigned long& iteraciones) const;
    Nodo<T>* nodoEn(int indice, unsigned long& iteraciones) const;
    void  enlazarAntesDe(Nodo<T>* pos, Nodo<T>* nuevo);
    void  quitarNodo(Nodo<T>* n);
public:
    lista();
    lista(const lista& otra);
    ~lista();
    lista& operator=(const lista& otra);
    T& operator[](int indice);
    const T& operator[](int indice) const;
    T& en(int indice, unsigned long& iteraciones);
    const T& en(int indice, unsigned long& iteraciones) const;
    bool operator==(const lista& otra) const;
    void concatenar(const lista& otra);
    void agregarAlFinal(const T& dato);
    void agregarAlInicio(const T& dato);
    bool insertarEn(int indice, const T& dato);
    void insertarOrdenado(const T& dato);
    bool eliminarPrimero();
    bool eliminarUltimo();
    bool eliminarEn(int indice);
    void vaciar();
    int  tamanio() const { return tam; }
    bool vacia() const { return tam == 0; }
    T* primero() { return (cabeza != 0) ? &cabeza->dato : 0; }
    const T* primero() const { return (cabeza != 0) ? &cabeza->dato : 0; }
    T* ultimo() { return (cola != 0) ? &cola->dato : 0; }
    const T* ultimo() const { return (cola != 0) ? &cola->dato : 0; }
    unsigned long memoria() const;
    int buscar(const T& dato, unsigned long& iteraciones) const;
};
#include "lista.cpp"
#endif // LISTA_H