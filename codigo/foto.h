#ifndef FOTO_H
#define FOTO_H
#include "fecha.h"
#include <string>
using namespace std;

class foto
{
private:
    string nombre;
    fecha publicada;
    unsigned short int tamanio;
    unsigned int likes;

public:
    foto();
    foto(const string& _n, const fecha _p, unsigned int _l, unsigned short int _t);
    foto(const foto& otra);
    ~foto();
    //set()
    bool setNombre(string& _n);
    bool setPublicada(fecha _p);
    bool setTamanio(unsigned int _t);
    bool setLikes(unsigned int _l);
    //get()
    const string& getNombre() const;
    fecha getPublicada() const;
    unsigned short int getTamanio() const;
    unsigned int getLikes() const;
    //funciones
    bool darLike();
    bool quitarLike();
    unsigned long int memoriaFoto();
    string rutaFoto(string& rutaAlbum);
    //operadores
    foto& operator=(const foto& otra);
    bool operator==(const foto& otra) const;

};

ostream& operator<<(ostream& os, const foto& f);

#endif // FOTO_H
