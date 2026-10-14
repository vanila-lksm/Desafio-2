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
    mensaje(const std::string& txt, int emi, int rec, const fecha& f);
    ~mensaje();
    bool setTexto(const std::string& txt);
    bool setEmisor(int emi);
    bool setReceptor(int rec);
    const std::string& getTexto() const;
    bool esLeido() const;
    void marcarLeido();
    int getEmisor() const;
    int getReceptor() const;
    fecha getFecha() const;
};

#endif // MENSAJE_H