#include "usuario.h"

usuario::usuario() {}
usuario::usuario(const string& _nombre, const string& _clave, const string& _correo,
                 const string& _ciudad, const string& _pais,
                 fecha _nacimiento, fecha _inscripcion)
{
    setNombre(_nombre); setClave(_clave); setCorreo(_correo);
    setCiudad(_ciudad); setPais(_pais);
    setNacimiento(_nacimiento); setInscripcion(_inscripcion);
}

usuario::usuario(const usuario& otro)
    : nombre(otro.nombre), clave(otro.clave), correo(otro.correo),
    ciudad(otro.ciudad), pais(otro.pais),
    nacimiento(otro.nacimiento), inscripcion(otro.inscripcion),
    colecion_albums(otro.colecion_albums), recibidos(otro.recibidos){}

usuario::~usuario() {}

//set()
bool usuario:: setNombre(const string& _nombre)
{
    if (_nombre.empty() || _nombre.find(';') != string::npos)
        return false;
    nombre = _nombre;
    return true;
}
bool usuario::setClave(const string& _clave)
{
    if (_clave.empty() || _clave.find(';') != string::npos)
        return false;
    clave = _clave;
    return true;
}
bool usuario::setCorreo(const string& _correo)
{
    if (_correo.find('@') == string::npos || _correo.find(';') != string::npos)
        return false;
    correo = _correo;
    return true;
}
bool usuario::setCiudad(const string& _ciudad)
{
    if (_ciudad.empty() || _ciudad.find(';') != string::npos) return false;
    ciudad = _ciudad;
    return true;
}
bool usuario::setPais(const string& _pais)
{
    if (_pais.empty() || _pais.find(';') != string::npos) return false;
    pais = _pais;
    return true;
}
bool usuario::setNacimiento(const fecha _nacimiento)
{
    if (!_nacimiento.validar())
        return false;
    nacimiento = _nacimiento;
    return true;
}
bool usuario::setInscripcion(const fecha _inscripcion)
{
    if (!_inscripcion.validar())
        return false;
    inscripcion = _inscripcion;
    return true;
}
void usuario::setAlbums(const lista<album>& _albums)
{colecion_albums = _albums;}
void usuario::setRecibidos(const lista<mensaje>& _recibidos)
{recibidos = _recibidos;}

//get()
const string& usuario::getNombre() const { return nombre; }
const string& usuario::getClave() const { return clave; }
const string& usuario::getCorreo() const { return correo; }
const string& usuario::getCiudad() const { return ciudad; }
const string& usuario::getPais() const { return pais; }
fecha usuario::getNacimiento() const { return nacimiento; }
fecha usuario::getInscripcion() const { return inscripcion; }
lista<album>& usuario::getAlbums() {return colecion_albums;}
const lista<album>& usuario::getAlbums() const {return colecion_albums;}
lista<mensaje>& usuario::getRecibidos() {return recibidos;}
const lista<mensaje>& usuario::getRecibidos() const {return recibidos;}
int usuario::cantidadAlbums() const {return colecion_albums.tamanio();}
int usuario::cantidadRecibidos() const {return recibidos.tamanio();}
//funciones
bool usuario:: validarClave(const string& _clave) const
{
    return clave == _clave;
}
string usuario::r_fotoPerfil(const string& subruta) const
{
    return subruta + "/" + nombre + "/albums/profile.png";
}

string usuario::rutaAlbum(const string& subruta) const
{
    return subruta + "/" + nombre + "/albums";
}
void usuario::recibirMensaje(const mensaje& m)
{recibidos.agregarAlFinal(m);}
unsigned long usuario::memoriaUsuario() const
{
    unsigned long total = sizeof(usuario);
    if (nombre.capacity() > 15)
        total += nombre.capacity() + 1;
    if (clave.capacity()  > 15)
        total += clave.capacity()  + 1;
    if (correo.capacity() > 15)
        total += correo.capacity() + 1;
    if (ciudad.capacity() > 15)
        total += ciudad.capacity() + 1;
    if (pais.capacity()   > 15)
        total += pais.capacity()   + 1;

    total += colecion_albums.memoria();          // los nodos de la lista
    unsigned long basura = 0;
    for (int i = 0; i < colecion_albums.tamanio(); i++)
        total += colecion_albums.en(i, basura).memoriaAlbum() - sizeof(album);
    total += recibidos.memoria();
    for (int i = 0; i < recibidos.tamanio(); i++)
        total += recibidos.en(i, basura).memoriaMensaje() - sizeof(mensaje);
    return total;
}
//operadores
usuario& usuario::operator=(const usuario& otro)
{
    if (this != &otro) {
        nombre = otro.nombre; clave = otro.clave; correo = otro.correo;
        ciudad = otro.ciudad; pais = otro.pais;
        nacimiento = otro.nacimiento; inscripcion = otro.inscripcion;
        recibidos = otro.recibidos;
    }
    return *this;
}

bool usuario::operator==(const usuario& otro) const
{
    return nombre == otro.nombre && clave==otro.clave;
}
ostream& operator<<(std::ostream& os, const usuario& u)
{
    os << u.getNombre() << ';' << u.getClave() << ';'
       << u.getCorreo() << ';' << u.getCiudad() << ';'
       << u.getPais() << ';' << u.getNacimiento() << ';'
       << u.getInscripcion();
    return os;
}