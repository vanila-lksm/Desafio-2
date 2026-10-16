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
public:
    mensaje();
    mensaje(const std::string& txt, int emi,const fecha& f);
    ~mensaje();
    mensaje(const mensaje& otra);
    mensaje& operator=(const mensaje& otra);
    bool operator==(const mensaje& otra) const;
    bool setTexto(const std::string& txt);
    bool setEmisor(int emi);
    const std::string& getTexto() const;
    bool getleido() const;
    void setleido(bool estado = true);
    int getEmisor() const;
    fecha getFecha_envio() const;
    void setFecha_envio(const fecha& f);
    friend std::ostream& operator<<(std::ostream& os, const mensaje& m);
    unsigned long memoriaMensaje() const;

};
#endif // MENSAJE_H