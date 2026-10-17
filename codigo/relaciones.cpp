#include "relaciones.h"

relaciones::relaciones() {}
relaciones::relaciones(int c_u)
{
    setCantidadUsuarios(c_u);
}
relaciones::relaciones(const relaciones& otra)
{
    setAmistades(otra.amistades,otra.cantidad_usuarios);
}
relaciones::~relaciones()
{
    delete[] amistades;
}
//set()
void relaciones::setCantidadUsuarios(int n)
{
    delete[] amistades;
    cantidad_usuarios = n;
    unsigned int total = n * getEspaciosFila();
    amistades = (total > 0) ? new unsigned long long[total]() : nullptr;
}
void relaciones::setAmistades(const unsigned long long int* nuevas, int n)
{
    if (nuevas == amistades) return;
    setCantidadUsuarios(n);
    unsigned int total = n * getEspaciosFila();
    for (unsigned int k = 0; k < total; k++)
    {
        amistades[k] = nuevas[k];
    }
}
void relaciones::setMarca(int i, int j, bool valor)
{
    if(i>=cantidad_usuarios || j>=cantidad_usuarios)
        return;
    unsigned int ubicacion=i*getEspaciosFila()+j/64;
    unsigned long long int mascara=1ULL<<(j%64);
    if(valor)
        amistades[ubicacion]|= mascara;
    else
        amistades[ubicacion]&= ~mascara;
}
//get()
short int relaciones::getEspaciosFila()const
{return(cantidad_usuarios+63)/64;}

unsigned int relaciones::getCantidad_usuarios()const
{return cantidad_usuarios;}

const unsigned long long int* relaciones::getAmistades()const
{return amistades;}

bool relaciones::getMarca(int i, int j)const
{
    unsigned int ubicacion=i*getEspaciosFila()+j/64;
    return((amistades[ubicacion]>>(j%64))&1Ull);
}
//funciones
unsigned int relaciones::amigosEnComun(int i,int j, unsigned long int& iteraciones)
{
    unsigned int espacios=getEspaciosFila();
    unsigned int abyacencias=0;
    for(unsigned int k=0;k<espacios;k++)
    {
        iteraciones++;
        unsigned long long combinado=amistades[i*espacios+k] & amistades[j*espacios+k];
        while(combinado!=0)
        {
            iteraciones++;
            unsigned int x=k * 64 + u_BitMasBajo(combinado);
            if(getMarca(x,i) && getMarca(x,j))
                abyacencias++;
            combinado&=combinado-1;
        }
    }
    return abyacencias;
}

unsigned char relaciones::u_BitMasBajo(unsigned long long int combinado)
{
    unsigned char posicion=0;
    if ((combinado & 0xFFFFFFFFULL) == 0) { combinado >>= 32; posicion += 32; }
    if ((combinado & 0xFFFFULL) == 0)     { combinado >>= 16; posicion += 16; }
    if ((combinado & 0xFFULL) == 0)       { combinado >>= 8;  posicion += 8;  }
    if ((combinado & 0xFULL) == 0)        { combinado >>= 4;  posicion += 4;  }
    if ((combinado & 0x3ULL) == 0)        { combinado >>= 2;  posicion += 2;  }
    if ((combinado & 0x1ULL) == 0)        { posicion += 1; }
    return posicion;
}
unsigned long relaciones::memoriaRelaciones() const
{
    unsigned long total = sizeof(relaciones);
    total += (unsigned long)cantidad_usuarios * getEspaciosFila() * sizeof(unsigned long long);
    return total;
}
relaciones& relaciones::operator=(const relaciones& otra)
{
    if(this != &otra)
    {
        setAmistades(otra.amistades,otra.cantidad_usuarios);
    }
    return *this;
}

bool relaciones:: operator==(const relaciones& otra) const
{
    if(cantidad_usuarios != otra.cantidad_usuarios)
        return false;
    unsigned int espacios= cantidad_usuarios*getEspaciosFila();
    for(unsigned int i=0;i<espacios;i++)
    {
        if(amistades[i] != otra.amistades[i])
            return false;
    }
    return true;
}


