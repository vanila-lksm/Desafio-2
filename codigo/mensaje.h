#ifndef MENSAJE_H
#define MENSAJE_H
#include <string>
#include "fecha.h"
class mensaje
{
private:
    std::string texto;
    bool leido;
    fecha fecha_envio;
    int emisor;
    int receptor;
public:
    mensaje();
    mensaje(const std::string& txt,int emi,int rec,fecha f);
    ~mensaje();
    bool setTexto(const std::string& txt);
    std::string gettexto() const;
    bool esleido() const;
    void marcarleido();
    int getemisor() const;
    int getreceptor() const;
    fecha getfecha() const;
};
#endif // MENSAJE_H
