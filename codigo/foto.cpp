#include "foto.h"

foto::foto() {}
foto:: foto(const string& _nombre,const fecha _publicada,
           unsigned int _likes=0,unsigned short int _tamanio=500): nombre("pachanga"), publicada(fecha()),tamanio(500),likes(0)
{
    if(_tamanio>65353 || _likes>4000000)
        return;
    nombre=_nombre;
    publicada=_publicada;
    tamanio=_tamanio;
    likes=_likes;
}
foto:: foto(const foto& otra)
{
    nombre=otra.nombre;
    publicada=otra.publicada;
    tamanio=otra.tamanio;
    likes=otra.likes;
}
//set()
bool foto:: setNombre(string& _nombre)
{
    nombre=_nombre;
    return true;
}
bool foto:: setPublicada(fecha _publicada)
{
    publicada=_publicada;
    return true;
}
bool foto:: setTamanio(unsigned int _tamanio)
{
    if(_tamanio>65353)
        return false;
    tamanio=static_cast<unsigned short int>(_tamanio);
    return true;
}
bool foto:: setLikes(unsigned int _likes)
{
    if(_likes>4000000)
        return false;
    likes=_likes;
    return true;
}

//get()
const string& foto::getNombre()const {return nombre;}
fecha foto::getPublicada()const {return publicada;}
unsigned short int foto:: getTamanio()const{return tamanio;}
unsigned int foto:: getLikes()const{return likes;}

//funciones
bool foto::darLike()
{
    if(likes>=4294967293)
        return false;
    likes++;
    return true;
}
bool foto::quitarLike()
{
    if(likes==0)
        return false;
    likes--;
    return true;
}
unsigned long int foto:: memoriaFoto()
{
    unsigned long int total=sizeof(foto);
    if(nombre.capacity()>15)
    {
        total+=nombre.capacity()+1;
    }
    return total;
}
string foto::rutaFoto(string& rutaAlbum)
{
    return rutaAlbum + "/" + nombre +".png";
}
//operadores
foto& foto:: operator=(const foto& otra)
{
    nombre=otra.nombre;
    publicada=otra.publicada;
    tamanio=otra.tamanio;
    likes=otra.likes;
    return *this;
}

bool foto:: operator==(const foto& otra) const
{
    if(nombre==otra.nombre && publicada==otra.publicada &&
        tamanio==otra.tamanio && likes==otra.likes)
        return true;
    else
        return false;
}

ostream& operator<<(ostream& os, const foto& f)
{
    os << f.nombre << ';' << f.publicada << ';' << f.tamanio << ';' << f.likes;
    return os;
}




