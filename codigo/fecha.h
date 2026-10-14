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
    static bool esBisiesto(short int a);
    static short int diasDelMes(short int a, short int m);
    static bool validar(short int a, short int m, short int d);
    bool validar() const;
    static fecha fechaHoy(unsigned long int& iteraciones);
    bool desdeTexto(const string& texto, unsigned long int& iteraciones);
    //operadores
    fecha& operator=(const fecha otra);
    bool operator==(fecha otra) const;
    bool operator<=(const fecha otra) const;
    bool operator>=(const fecha otra) const;
    friend ostream& operator<<(ostream& os, const fecha f);
};

#endif // FECHA_H
