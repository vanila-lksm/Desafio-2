#include "fecha.h"
#include <chrono>

fecha::fecha(): anio(2026), mes(1), dia(1) {}

fecha::fecha(short int anio, unsigned char mes, unsigned char dia): anio(2026), mes(1), dia(1)
{
    setFecha(anio,mes,dia);
}

fecha:: fecha(const fecha& otra)
{
    anio=otra.anio;
    mes=otra.mes;
    dia=otra.dia;
}
fecha::~fecha(){}
//set()
bool fecha::setFecha(short int _anio, short int _mes, short int _dia)
{
    if (!validar(_anio, _mes, _dia)){return false;}
    anio=_anio;
    mes=static_cast<unsigned char>(_mes);
    dia=static_cast<unsigned char>(_dia);
    return true;
}

bool fecha::setAnio(short int _anio)
{
    if(!validar(_anio,mes,dia)){return false;}
    anio=_anio;
    return true;
}

bool fecha:: setMes(short int _mes)
{
    if(!validar(anio,_mes,dia)){return false;}
    mes=static_cast<unsigned char>(_mes);
    return true;
}

bool fecha:: setDia(short int _dia)
{
    if(!validar(anio,mes,_dia)){return false;}
    dia=static_cast<unsigned char>(_dia);
    return true;
}
//get()
short int fecha::getAnio() const{return anio;}
unsigned char fecha::getMes() const{return mes;}
unsigned char fecha::getDia() const{return dia;}

//funciones
bool fecha::desdeTexto(const string& texto, unsigned long int& iteraciones)
{
    if(texto.size() !=10 || texto[4]!='-' || texto[7]!='-')
        return false;
    short int componentes[3]{0,0,0};
    short int parte=0;
    for(short int i=0;i<10;i++)
    {
        iteraciones++;
        if(i==4 || i==7)
        {
            parte++;
            continue;
        }
        char c=texto[i];
        if(c<'0' || c>'9')
            return false;
        componentes[parte]=componentes[parte]*10+(c-'0');
    }
    return setFecha(componentes[0],componentes[1],componentes[2]);
}

bool fecha::esBisiesto(short int anio)
{
    return (anio % 4 == 0 && anio % 100 != 0) || anio % 400 == 0;
}
short int fecha::diasDelMes(short int anio, short int mes)
{
    if (mes == 2)
    {
        return esBisiesto(anio) ? 29 : 28;
    }
    if (mes == 4 || mes == 6 || mes == 9 || mes == 11)
    {
        return 30;
    }
    return 31;
}
bool fecha::validar(short int _anio, short int _mes, short int _dia)
{
    if (_anio < 1000 || _anio > 9999)
        return false;
    if (_mes < 1 || _mes > 12)
        return false;
    if (_dia < 1 || _dia > diasDelMes(_anio, _mes))
        return false;
    return true;
}
bool fecha::validar() const
{
    return validar(anio,mes,dia);
}
fecha fecha:: fechaHoy(unsigned long int& iteraciones)
{
    using namespace std::chrono;

    // system_clock cuenta desde 1970-01-01 en UTC. Colombia es UTC-5.
    long long int horas = duration_cast<hours>(system_clock::now().time_since_epoch()).count() - 5;
    long int dias  = horas / 24;

    // Descuenta años completos desde 1970.
    short int a = 1970;
    while (dias >= (esBisiesto(a) ? 366 : 365))
    {
        dias -= esBisiesto(a) ? 366 : 365;
        a++;
        iteraciones++;
    }
    // Descuenta meses completos del año que quedó.
    short int m = 1;
    while (dias >= diasDelMes(a, m))
    {
        dias -= diasDelMes(a, m);
        m++;
        iteraciones++;
    }

    // Lo que sobra son los días transcurridos del mes; el día 1 es el primero.
    return fecha(a, m, static_cast<short int>(dias) + 1);
}
//operadores

fecha& fecha::operator=(const fecha otra)
{
    anio = otra.anio;
    mes = otra.mes;
    dia = otra.dia;
    return *this;
}

bool fecha::operator==(const fecha otra) const
{
    return (anio == otra.anio && mes == otra.mes && dia == otra.dia);
}

bool fecha::operator<=(const fecha otra) const
{
    if (anio != otra.anio)
        return anio < otra.anio;
    if (mes != otra.mes)
        return mes < otra.mes;
    return dia <= otra.dia;
}

bool fecha::operator>=(const fecha otra) const
{
    if (anio != otra.anio)
        return anio > otra.anio;
    if (mes != otra.mes)
        return mes > otra.mes;
    return dia >= otra.dia;
}

ostream& operator<<(ostream& os,const fecha f)
{
    os << f.getAnio() << '-';
    if (f.getMes() < 10) os << '0';
    os << f.getMes() << '-';
    if (f.getDia() < 10) os << '0';
    os << f.getDia();
    return os;
}






















