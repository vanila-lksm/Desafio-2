#include "mensaje.h"
mensaje::mensaje() {
    texto="";
    leido=false;
    emisor=-1;
    receptor=-1;

}
mensaje::mensaje(const std::string& txt, int emi, int rec, fecha f)
    : leido(false), fecha_envio(f), emisor(emi), receptor(rec)  {
    if (!setTexto(txt)) {
        texto = "[mensaje invalido]";
    }
}
mensaje::~mensaje() {}
bool mensaje::setTexto(const std::string& txt) {
    if (txt.empty()) return false;
    if (txt.size() > 512) return false;
    texto = txt;
    return true;
}
std::string mensaje::gettexto() const {
    return texto;
}
bool mensaje::esleido() const {
    return leido;
}
void mensaje::marcarleido() {
    leido = true;
}
int mensaje::getemisor() const {
    return emisor;
}
int mensaje::getreceptor() const {
    return receptor;
}
fecha mensaje::getfecha() const {
    return fecha_envio;
}