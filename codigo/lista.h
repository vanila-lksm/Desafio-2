#ifndef LISTA_H
#define LISTA_H

template <typename T>
class Lista {
private:
    class Nodo {
    public:
        T dato;
        Nodo* sig;
        Nodo* ant;
        Nodo(const T& d) : dato(d), sig(0), ant(0) {}
    };
    Nodo* cabeza;
    Nodo* cola;
    int   tam;
    Nodo* cursor;
    int   indiceCursor;
    mutable long long ciclos;
    Nodo* caminar(Nodo* actual, int pos, int indice) const;
    Nodo* nodoEnConst(int indice) const;
    Nodo* nodoEn(int indice);
    void  enlazarAntesDe(Nodo* pos, Nodo* nuevo);
    void  quitarNodo(Nodo* n);
public:
    Lista();
    Lista(const Lista& otra);
    ~Lista();
    Lista& operator=(const Lista& otra);
    T& operator[](int indice);
    const T& operator[](int indice) const;
   void concatenar(const Lista& otra);
    void agregarAlFinal(const T& dato);
    void agregarAlInicio(const T& dato);
    bool insertarEn(int indice, const T& dato);
    void insertarOrdenado(const T& dato);
    bool eliminarPrimero();
    bool eliminarUltimo();
    bool eliminarEn(int indice);
    void vaciar();
    int  tamanio()const { return tam; }
    bool vacia()const { return tam == 0; }
    T& primero(){ return cabeza->dato; }
    const T& primero() const { return cabeza->dato; }
    T& ultimo(){ return cola->dato; }
    const T& ultimo()const { return cola->dato; }
    long long getCiclos() const { return ciclos; }
    void reiniciarCiclos() const { ciclos = 0; }
};
#include "lista.cpp"

#endif // LISTA_H
