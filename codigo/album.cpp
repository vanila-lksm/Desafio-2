#include "album.h"
#include <string>
album::album() : nombre("SinNombre"), privacidad('P') {}
album::album(const std::string& nom, unsigned char priv) {
    if (!setNombre(nom)) nombre="SinNombre";
    if (!setPrivacidad(priv)) privacidad='P';
}
album::~album() {}
std::string album::getNombre() const {
    return nombre;
}
unsigned char album::getPrivacidad() const {
    return privacidad;
}
bool album::setNombre(const std::string& nom) {
    if (nom.empty() || nom.find(';') !=std::string::npos)
        return false;
    nombre = nom;
    return true;
}
bool album::setPrivacidad(unsigned char priv) {
    if (priv !='P' && priv !='R' && priv !='A')
        return false;
    privacidad = priv;
    return true;
}
lista<foto>& album::getColeccionFotos() {
    return coleccion_fotos;
}
const lista<foto>& album::getColeccionFotos() const {
    return coleccion_fotos;
}
void album::agregarFoto(const foto& f) {
    coleccion_fotos.agregarAlFinal(f);
}