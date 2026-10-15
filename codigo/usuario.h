#ifndef USUARIO_H
#define USUARIO_H
#include "album.h"
#include "fecha.h"
#include "mensaje.h"
#include <iostream>
using namespace std;
class usuario
{
private:
    string nombre;
    string clave;
    string correo;
    string ciudad;
    string pais;
    fecha nacimiento;
    fecha inscripcion;
    lista<album> colecion_albums;
    lista<mensaje> recibidos;
public:
    usuario();
    usuario(const string& _nombre, const string& _clave, const string& _correo,
            const string& _ciudad, const string& _pais, fecha _nacimiento, fecha _inscripcion);
    usuario(const usuario&);
    ~usuario();
    //set()
    bool setNombre(const string& _nombre);
    bool setClave(const string& _clave);
    bool setCorreo(const string& _correo);
    bool setCiudad(const string& _ciudad);
    bool setPais(const string& _pais);
    bool setNacimiento(const fecha _nac);
    bool setInscripcion(const fecha _inscrip);
    void setAlbums(const lista<album>& _albums);
    void setRecibidos(const lista<mensaje>& _recibidos);
    //get()
    const string& getNombre() const;
    const string& getClave() const;
    const string& getCorreo() const;
    const string& getCiudad() const;
    const string& getPais() const;
    fecha getNacimiento()const;
    fecha getInscripcion()const;
    lista<album>& getAlbums();
    const lista<album>& getAlbums() const;
    lista<mensaje>& getRecibidos();
    const lista<mensaje>& getRecibidos() const;
    int cantidadAlbums() const;
    int cantidadRecibidos() const;
    //funciones
    bool validarClave(const string& _clave);
    string r_fotoPerfil(const string& subruta) const;
    string rutaAlbum(const string& subruta) const;
    void recibirMensaje(const mensaje& m);
    void agregarAlbum(const album& a);
    unsigned long memoriaUsuario()const;
    //operadores
    usuario& operator=(const usuario& otro);
    bool operator==(const usuario& otro) const;
    friend ostream& operator<<(ostream& os, const usuario& usuario);
};

#endif // USUARIO_H
