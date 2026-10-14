#ifndef ALBUM_H
#define ALBUM_H
#include <string>
#include "lista.h"
#include "foto.h"

class album {
private:
    std::string nombre;
    unsigned char privacidad;
    lista<foto> coleccion_fotos;
public:
    album();
    album(const std::string& nom, unsigned char priv);
    ~album();
    std::string getNombre() const;
    unsigned char getPrivacidad() const;
    bool setNombre(const std::string& nom);
    bool setPrivacidad(unsigned char priv);
    lista<foto>& getColeccionFotos();
    const lista<foto>& getColeccionFotos() const;
    void agregarFoto(const foto& f);
};

#endif // ALBUM_H