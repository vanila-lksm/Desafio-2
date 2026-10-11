#ifndef FECHA_H
#define FECHA_H
#include <string>
#include <iostream>
using namespace std;

class fecha
{
private:
    short int anio;
    unsigned char mes;
    unsigned char dia;
public:
    fecha();
    fecha(short int _anio, unsigned char _mes, unsigned char _dia);
    fecha(const fecha& otra);
    ~fecha();
    //set()
    bool setFecha(short int _a, short int _m, short int _d);
    bool setAnio(short int _a);
    bool setMes(short int _m);
    bool setDia(short int _d);
    //get()
    short int getAnio() const;
    unsigned char getMes() const;
    unsigned char getDia() const;
    //funciones
    bool esBisiesto(short int a);
    short int diasDelMes(short int a, short int m);
    bool validar(short int a, short int m, short int d);
    fecha fechaHoy();
    bool desdeTexto(const string& texto, unsigned int& iteraciones);
    //operadores
    fecha& operator=(const fecha& otra);
    bool operator==(fecha otra) const;
    bool operator<=(const fecha& otra) const;
    bool operator>=(const fecha& otra) const;
    ostream& operator<<(ostream& os);
};

#endif // FECHA_H
