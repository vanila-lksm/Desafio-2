#include "relaciones.h"

relaciones::relaciones() {}
relaciones::relaciones(unsigned int c_u)
{
    setCantidadUsuarios(c_u);
}
relaciones::relaciones(const relaciones& otra)
{
    amistades=otra.amistades;
    cantidad_usuarios=otra.cantidad_usuarios;
}
relaciones::~relaciones()
{
    delete[] amistades;
}
//set()
void relaciones::setCantidadUsuarios(unsigned int n)
{
    delete[] amistades;
    cantidad_usuarios = n;
    unsigned int total = n * getEspaciosFila();
    amistades = (total > 0) ? new unsigned long long[total]() : nullptr;
}
void relaciones::setAmistades(const unsigned long long int* nuevas, unsigned int n)
{
    if (nuevas == amistades) return;
    setCantidadUsuarios(n);
    unsigned int total = n * getEspaciosFila();
    for (unsigned int k = 0; k < total; k++)
    {
        amistades[k] = nuevas[k];
    }
}
void relaciones::setMarca(unsigned int i, unsigned int j, unsigned char valor)
{
    unsigned int ubicacion=i*getEspaciosFila()+j/64;
    unsigned long long int mascara=valor<<(j%64);
    if(valor)
        amistades[ubicacion]|=mascara;
    else
        amistades[ubicacion]|=~mascara;
}
//get()
short int relaciones::getEspaciosFila()const
{return(cantidad_usuarios+63/64);}

unsigned int relaciones::getCantidad_usuarios()const
{return cantidad_usuarios;}

unsigned long long int* relaciones::getAmistades()const
{return amistades;}

bool relaciones::getMarca(unsigned int i, unsigned int j)const
{
    unsigned int ubicacion=i*getEspaciosFila()+j/64;
    return(amistades[ubicacion]>>(j%64)&1Ull);
}
//funciones
unsigned int relaciones::amigosEnComun(unsigned int i,unsigned int j, unsigned int& iteraciones)
{
    unsigned int c_u=getCantidad_usuarios();
    unsigned int abyacencias=0;
    for(unsigned short int k=0;k<c_u;k++)
    {
        iteraciones++;
        unsigned long long combinado=amistades[i*c_u+k]&amistades[j*c_u+k];
        while(combinado!=0)
        {
            iteraciones++;
            unsigned int x=k * c_u + u_BitMasBajo(combinado);
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
relaciones& relaciones::operator=(const relaciones& otra)
{
    if(this != &otra)
    {
        setAmistades(otra.amistades,otra.cantidad_usuarios);
    }
    return *this;
}

bool relaciones:: operator==(const relaciones& otra)
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


