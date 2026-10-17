#ifndef UDEABOOK_H
#define UDEABOOK_H
#include "lista.h"
#include "usuario.h"
#include "relaciones.h"

class udeaBook
{
private:
    static const string subruta;
    static const int AMIGOS_POR_PAG= 3;
    relaciones amistades;
    lista<usuario> usuarios;
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
    //get()
    const relaciones& getAmistades() const;
    relaciones& getAmistades();
    const lista<usuario>& getUsuarios() const;
    lista<usuario>& getUsuarios();
    int getUsuarioActual() const;

    //funciones(){
    void limpiarCampo(string& campo);
    void buscarPorIndices(const int* indices, int cantidad,
                        const usuario** salida, unsigned long int& iteraciones);
    int b_inidicePorNombre(const string& nombre, unsigned long int& iteraciones)const;
    unsigned long memoriaUdeaBook() const;
    bool enviar_solicitud(const string& nombre, unsigned long int& iteraciones);
    int mostrar_solicitudes(unsigned long int& iteraciones)const;
    bool aceptar_solicitudes(const int j);
    int mostrar_albums(const string& nombre,unsigned long int& iteraciones);
    void recorrer_album(int j,int i,unsigned long int& iteraciones);
    int leerEntero(const string& mensaje);
    string leerTexto(const string& mensaje,bool vacio);
    int  calcAmigos(int* indices, unsigned long int& iteraciones);
    void impAmigos(const usuario** amigos, int cantidad, int desde) const;
    void buscarMensajesPorFecha(const fecha& inicio, const fecha& fin, unsigned long& iteraciones);
    void buscarMensajesNoLeidos(unsigned long& iteraciones);
    bool enviarMensaje(int indice_receptor, const std::string& texto, unsigned long int& iteraciones);
    int recomendaciones_amistades(int k,int* indices,unsigned long int& iteraciones);
    //cargar()
    bool cargarUsuarios_txt(const string& ruta,unsigned long int& iteraciones);
    bool cargarRelaciones_txt(const string& ruta, unsigned long int& iteraciones);
    bool cargarMensajes_txt(const string& ruta, unsigned long int&iteraciones);
    bool cargarAlbums_txt(const string& ruta, unsigned long int& iteraciones);
    //guardar()
    bool guardarUsuarios_txt(const string& ruta, unsigned long int& iteraciones) const;
    bool guardarRelaciones_txt(const string& ruta, unsigned long int& iteraciones) const;
    bool guardarMensajes_txt(const string& ruta, unsigned long int& iteraciones) const;
    bool guardarAlbums_txt(const string& ruta, unsigned long int& iteraciones) const;
    //operadores
    udeaBook& operator=(const udeaBook& otro);
    bool operator==(const udeaBook& otro) const;
    //aqui cositas del main
    bool iniciarSesion(unsigned long int& iteraciones);
    void reportarEficiencia(unsigned long int& iteraciones);
    bool recargarAmigos(int& desde, int cantidad) const;
    bool cargarTodo(unsigned long int& iteraciones);
    void guardarTodo(unsigned long int& iteraciones);
    void decision2(unsigned long int& iteraciones,short int decision);
    void decision4(unsigned long int& iteraciones,short int decision);
    void decision5(unsigned long int& iteraciones);
};

#endif // UDEABOOK_H
