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
    usuario* emisor;
    usuario* receptor;
public:
    mensaje(const std::string& txt,usuario* emi,usuario* rec,fecha f);
    ~mensaje();
    std::string gettexto();
    bool esleido() const;
    void marcarleido();
    usuario* getemisor() const;
    usuario* getreceptor() const;
    fecha getfecha() const;
};

#endif // MENSAJE_H
