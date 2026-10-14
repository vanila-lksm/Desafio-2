#ifndef LISTA_H
#define LISTA_H
#include "nodo.h"

template <typename T>
class lista {
private:
    Nodo<T>* cabeza;
    Nodo<T>* cola;
    int tam;
    mutable Nodo<T>* cursor;
    mutable int   indiceCursor;
    mutable long long ciclos;
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
    T& primero() { return cabeza->dato; }
    const T& primero() const { return cabeza->dato; }
    T& ultimo() { return cola->dato; }
    const T& ultimo() const { return cola->dato; }
    long long getCiclos() const { return ciclos; }
    void reiniciarCiclos() const { ciclos = 0; }
    unsigned long memoria() const;
};
#include "lista.cpp"
#endif // LISTA_H