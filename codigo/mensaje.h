#ifndef MENSAJE_H
#define MENSAJE_H
#include <string>
#include "fecha.h"
class usuario;
class mensaje
{
private:
    std::string texto;
    bool leido;
    fecha fecha_envio;
    usuario* emisor;
    usuario* receptor;
public:
    mensaje();
    mensaje(const std::string& txt,usuario* emi,usuario* rec,fecha f);
    ~mensaje();
    std::string gettexto() const;
    bool esleido() const;
    void marcarleido();
    usuario* getemisor() const;
    usuario* getreceptor() const;
    fecha getfecha() const;
};
ostream& operator<<(std::ostream& os, const mensaje& m)

#endif // MENSAJE_H
