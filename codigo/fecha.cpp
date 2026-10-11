#include "fecha.h"
#include <ctime>

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
bool fecha::desdeTexto(const string& texto, unsigned int& iteraciones)
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

fecha fecha:: fechaHoy()
{
    std::time_t tiempoActual = std::time(nullptr);
    std::tm* fechaLocal = std::localtime(&tiempoActual);
    short int anio = fechaLocal->tm_year + 1900; // tm_year cuenta los años desde 1900
    unsigned char mes  = static_cast<unsigned char>(fechaLocal->tm_mon + 1);     // tm_mon va de 0 (enero) a 11 (diciembre)
    unsigned char dia  = static_cast<unsigned char>(fechaLocal->tm_mday);
    return fecha(anio,mes,dia);
}
//operadores

fecha& fecha::operator=(const fecha& otra)
{
    anio = otra.anio;
    mes = otra.mes;
    dia = otra.dia;
    return *this;
}

bool fecha::operator==(fecha otra) const
{
    return (anio == otra.anio && mes == otra.mes && dia == otra.dia);
}

bool fecha::operator<=(const fecha& otra) const
{
    if (anio != otra.anio)
        return anio < otra.anio;
    if (mes != otra.mes)
        return mes < otra.mes;
    return dia <= otra.dia;
}

bool fecha::operator>=(const fecha& otra) const
{
    if (anio != otra.anio)
        return anio > otra.anio;
    if (mes != otra.mes)
        return mes > otra.mes;
    return dia >= otra.dia;
}

ostream& fecha::operator<<(ostream& os)
{
    os<<anio <<"/" <<mes <<"/" <<dia <<endl;
    return os;
}






















