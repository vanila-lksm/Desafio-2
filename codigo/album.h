#ifndef ALBUM_H
#define ALBUM_H
#include <string>
#include"foto.h"
#include"lista.h"

class album
{
private:
    std::string nombre;
    std::string ruta_almacenamiento;
    std::string privacidad;
    lista<foto> coleccion_fotos;
public:
    album();
    album(const std::string& nom,const std::string& ruta,const std::string& priv);
    ~album();
    std::string getNombre() const;
    std::string getRutaAlmacenamiento() const;
    std::string getPrivacidad() const;
    void setNombre(const std::string& nom);
    void setRutaAlmacenamiento(const std::string& ruta);
    void setPrivacidad(const std::string& priv);
    lista<foto>& getcoleccionfotos();
    const lista<foto>& getcoleccionfotos() const;
    void agregarfoto(const foto& f);
};
//borrar

#endif // ALBUM_H
