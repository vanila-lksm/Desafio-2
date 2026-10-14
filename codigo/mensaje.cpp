#include "mensaje.h"
mensaje::mensaje() {
    texto="";
    leido=false;
    emisor=nullptr;
    receptor=nullptr;

}
mensaje::mensaje(const std::string& txt,usuario* emi,usuario* rec,fecha f) {
    if (txt.length() > 512) {
        texto=txt.substr(0, 512);
    } else {
        texto=txt;
    }
    leido=false;
    emisor=emi;
    receptor=rec;
    fecha_envio=f;
}
mensaje::~mensaje() {}
std::string mensaje::gettexto() const {
    return texto;
}
bool mensaje::esleido() const {
    return leido;
}
void mensaje::marcarleido() {
    leido = true;
}
usuario* mensaje::getemisor() const {
    return emisor;
}
usuario* mensaje::getreceptor() const {
    return receptor;
}
fecha mensaje::getfecha() const {
    return fecha_envio;
}
ostream& operator<<(std::ostream& os, const mensaje& m)
{
    os << m.getEmisor() << ';'
       << m.getEnvio() << ';'
       << (m.getLeido() ? 1 : 0) << ';'
       << m.getTexto();
    return os;
}