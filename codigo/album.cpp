#include "album.h"
#include "lista.h"
#include "foto.h"

album::album():nombre(""),ruta_almacenamiento(""),privacidad("público") {}
album::album(const std::string& nom,const std::string& ruta,const std::string& priv)
    : nombre(nom),ruta_almacenamiento(ruta),privacidad(priv) {}
album::~album() {}
std::string album::getNombre() const {
    return nombre;
}
std::string album::getRutaAlmacenamiento() const {
    return ruta_almacenamiento;
}
std::string album::getPrivacidad() const {
    return privacidad;
}
void album::setNombre(const std::string& nom) {
    nombre = nom;
}
void album::setRutaAlmacenamiento(const std::string& ruta) {
    ruta_almacenamiento = ruta;
}
void album::setPrivacidad(const std::string& priv) {
    privacidad = priv;
}
lista<foto>& album::getcoleccionfotos() {
    return coleccion_fotos;
}
const lista<foto>& album::getcoleccionfotos() const {
    return coleccion_fotos;
}
void album::agregarfoto(const foto& f) {
    coleccion_fotos.agregarAlFinal(f);
}
//borrar