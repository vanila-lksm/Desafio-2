#include "fecha.h"

fecha::fecha(): anio(2026), mes(1), dia(1) {}

fecha::fecha(short int anio, unsigned char mes, unsigned char dia): anio(2026), mes(1), dia(1)
{
    setFecha(anio,mes,dia);
}
bool fecha::esBisiesto(int anio)
{
    return (anio % 4 == 0 && anio % 100 != 0) || anio % 400 == 0;
}
int fecha::diasDelMes(int anio, int mes)
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
bool fecha::validar(short int anio, short int mes, short int dia)
{
    if (anio < 1000 || anio > 9999)
        return false;
    if (mes < 1 || mes > 12)
        return false;
    if (dia < 1 || dia > diasDelMes(anio, mes))
        return false;
    return true;
}

bool fecha::setFecha(short int _anio, short int _mes, short int _dia)
{
    if (!validar(anio, mes, dia)) return false;
    anio=_anio;
    mes=static_cast<unsigned char>(_mes);
    dia=static_cast<unsigned char>(_dia);
    return true;
}
short int fecha::getAnio() const{return anio;}
unsigned char fecha::getMes() const{return mes;}
unsigned char fecha::getDia() const{return dia;}


bool fecha::desdeTexto(const string& texto, unsigned long int& iteraciones)
{
    if(texto.size() !=10 || texto[4]!='-' || texto[7]!='-')
        return false;
    short int componentes[3]{0,0,0};
    short int parte=0;
    for(short int i=0;i<10;i++)
    {
        if(i==4 || i==7)
        {
            parte++;
            continue;
        }
        char c=texto[i];
        if(c<'0' || c>'9')
            return false;
        componentes[parte]=componentes[parte]*10+(c-'0');
        iteraciones+=14;
    }
    return setFecha(componentes[0],componentes[1],componentes[2]);
}

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
























