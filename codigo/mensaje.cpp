#include "mensaje.h"

mensaje::mensaje()
    : texto(""), leido(false), fecha_envio(), emisor(-1), receptor(-1) {}

mensaje::mensaje(const std::string& txt, int emi, int rec, const fecha& f)
    : texto(""), leido(false), fecha_envio(f), emisor(-1), receptor(-1)
{
    if (!setTexto(txt))
        texto = "[mensaje invalido]";
    setEmisor(emi);
    setReceptor(rec);
}
mensaje::~mensaje() {}
bool mensaje::setTexto(const std::string& txt)
{
    if (txt.empty() || txt.size()>512) return false;
    if (txt.find(';') != std::string::npos) return false;
    texto = txt;
    return true;
}
bool mensaje::setEmisor(int emi)
{
    if (emi<0) return false;
    emisor=emi;
    return true;
}
bool mensaje::setReceptor(int rec)
{
    if (rec<0) return false;
    receptor=rec;
    return true;
}

const std::string& mensaje::getTexto() const { return texto; }
bool mensaje::esLeido() const {
    return leido; }
void mensaje::marcarLeido() {
    leido = true; }
int mensaje::getEmisor() const {
    return emisor; }
int mensaje::getReceptor() const {
    return receptor; }
fecha mensaje::getFecha() const {
    return fecha_envio; }