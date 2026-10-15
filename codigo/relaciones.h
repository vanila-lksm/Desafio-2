#ifndef RELACIONES_H
#define RELACIONES_H

class relaciones
{
private:
    unsigned long long int* amistades=nullptr;
    int cantidad_usuarios=0;
public:
    //constructores y destructor
    relaciones();
    relaciones(int c_u);
    relaciones(const relaciones& otra);
    ~relaciones();
    //set()
    void setAmistades(const unsigned long long int* nuevas, int c_u);
    void setCantidadUsuarios(int c_u);
    void setMarca(int i, int j, bool valor);
    //get()
    short int getEspaciosFila()const;
    unsigned int getCantidad_usuarios()const;
    const unsigned long long int* getAmistades()const;
    bool getMarca(int i, int j)const;
    //funciones
    unsigned int amigosEnComun(int i,int j,unsigned long int& iteraciones);
    static unsigned char u_BitMasBajo(unsigned long long combinado);
    unsigned long memoriaRelaciones() const;
    //operadores
    relaciones& operator=(const relaciones& otra);
    bool operator==(const relaciones& otra) const;


};

#endif // RELACIONES_H
