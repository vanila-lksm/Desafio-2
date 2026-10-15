#ifndef UDEABOOK_H
#define UDEABOOK_H
#include "lista.h"
#include "usuario.h"
#include "relaciones.h"

class udeaBook
{
private:
    static const string subruta;
    relaciones amistades;
    lista<usuario> usuarios;
    int amigos_imp[3];
    int amigos_imp_reservados;
    int usuario_actual;


public:
    udeaBook();
    udeaBook(const udeaBook& otro);
    ~udeaBook();
    //set()
    void setAmistades(const relaciones& _amistades);
    void setUsuarios(const lista<usuario>& _usuarios);
    bool setSubruta(const string& _subruta);
    bool setUsuarioActual(int _usuario_actual);
    bool setAmigosImp(const int* _amigos, int cantidad);
    //get()
    const relaciones& getAmistades() const;
    relaciones& getAmistades();
    const lista<usuario>& getUsuarios() const;
    lista<usuario>& getUsuarios();
    int getUsuarioActual() const;
    int getAmigosImp(int posicion) const;
    int getAmigosImpReservados() const;

    //funciones(){
    void limpiarCampo(string& campo);
    void impAmigos(unsigned long int& iteraciones);
    void buscarPorIndices(const int* indices, int cantidad,
                        const usuario** salida, unsigned long int& iteraciones);
    void impRutasPerfil(const int* indices,int cantidad,unsigned long int& iteraciones);
    unsigned long memoriaUdeaBook() const;
    //cargar()
    bool cargarUsuarios_txt(const string& ruta,unsigned long int& iteraciones);
    bool cargarRelaciones_txt(const string& ruta, unsigned long int& iteraciones);
    //guardar()
    bool guardarUsuarios_txt(const string& ruta, unsigned long int& iteraciones) const;
    bool guardarRelaciones_txt(const string& ruta, unsigned long int& iteraciones) const;
    //operadores
    udeaBook& operator=(const udeaBook& otro);
    bool operator==(const udeaBook& otro) const;

};

#endif // UDEABOOK_H
