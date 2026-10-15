#include "mensaje.h"

mensaje::mensaje()
    : texto(""), leido(false), fecha_envio(), emisor(-1) {}

mensaje::mensaje(const std::string& txt, int emi, const fecha& f)
    : texto(""), leido(false), fecha_envio(f), emisor(-1)
{
    if (!setTexto(txt))
        texto = "[mensaje invalido]";
    setEmisor(emi);
}
mensaje::~mensaje() {}
mensaje& mensaje::operator=(const mensaje& otra) {
    if (this != &otra) {
        texto = otra.texto;
        leido = otra.leido;
        fecha_envio = otra.fecha_envio;
        emisor = otra.emisor;
    }
    return *this;
}
bool mensaje::operator==(const mensaje& otra) const {
    return texto == otra.texto &&
           emisor == otra.emisor &&
           fecha_envio == otra.fecha_envio;
}
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
const std::string& mensaje::getTexto() const { return texto; }
bool mensaje::esLeido() const {
    return leido; }
void mensaje::marcarLeido() {
    leido = true; }
int mensaje::getEmisor() const {
    return emisor; }
fecha mensaje::getFecha() const {
    return fecha_envio; }
std::ostream& operator<<(std::ostream& os, const mensaje& m)
{
    os << m.getEmisor() << ';'
       << m.getFecha() << ';'
       << (m.esLeido() ? 1 : 0) << ';'
       << m.getTexto();
    return os;
}