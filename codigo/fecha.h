#ifndef FECHA_H
#define FECHA_H
#include <string>
using namespace std;

class fecha
{
private:
    short int anio;
    unsigned char mes;
    unsigned char dia;
public:
    fecha();
    fecha(short int anio, unsigned char mes, unsigned char dia);
    bool esBisiesto(int a);
    int diasDelMes(int a, int m);
    bool validar(short int a, short int m, short int d);
    bool setFecha(short int a, short int m, short int d);
    short int getAnio() const;
    unsigned char getMes() const;
    unsigned char getDia() const;
    bool desdeTexto(const string& texto, unsigned long int& iteraciones);
    fecha& operator=(const fecha& otra);
    bool operator==(fecha otra) const;
    bool operator<=(const fecha& otra) const;
    bool operator>=(const fecha& otra) const;
};

#endif // FECHA_H
