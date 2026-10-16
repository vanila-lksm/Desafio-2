#include "udeabook.h"
#include <fstream>
#include <random>
const string udeaBook::subruta = "/users/udeabook2026";
udeaBook::udeaBook() : amigos_imp_reservados(0),usuario_actual(-1)
{
    amigos_imp[0] = -1;
    amigos_imp[1] = -1;
    amigos_imp[2] = -1;
}
udeaBook::udeaBook(const udeaBook& otro)
    : amistades(otro.amistades), usuarios(otro.usuarios),
    amigos_imp_reservados(otro.amigos_imp_reservados)
{
    amigos_imp[0] = otro.amigos_imp[0];
    amigos_imp[1] = otro.amigos_imp[1];
    amigos_imp[2] = otro.amigos_imp[2];
}
udeaBook::~udeaBook() {}

//set()
void udeaBook::setAmistades(const relaciones& _amistades)
{
    amistades = _amistades;
}

void udeaBook::setUsuarios(const lista<usuario>& _usuarios)
{
    usuarios = _usuarios;
}
bool udeaBook::setUsuarioActual(int _usuario_actual)
{
    if (_usuario_actual < -1 || _usuario_actual >= usuarios.tamanio())
        return false;
    usuario_actual = _usuario_actual;
    return true;
}

bool udeaBook::setAmigosImp(const int* _amigos, int cantidad)
{
    if (_amigos == 0 || cantidad < 0 || cantidad > 3)
        return false;
    for (int i = 0; i < cantidad; i++)
        amigos_imp[i] = _amigos[i];
    amigos_imp_reservados = cantidad;
    return true;
}
//get()
const relaciones& udeaBook::getAmistades() const { return amistades; }
relaciones& udeaBook::getAmistades() { return amistades; }
const lista<usuario>& udeaBook::getUsuarios() const { return usuarios; }
lista<usuario>& udeaBook::getUsuarios() { return usuarios; }
int udeaBook::getUsuarioActual() const { return usuario_actual; }
int udeaBook::getAmigosImp(int posicion) const
{
    if (posicion < 0 || posicion >= amigos_imp_reservados)
        return -1;
    return amigos_imp[posicion];
}
int udeaBook::getAmigosImpReservados() const { return amigos_imp_reservados; }

//funciones
void udeaBook::limpiarCampo(string& campo)
{
    if(!campo.empty())
    {
        if(campo[campo.size()-1]=='\r' || campo[campo.size()-1]=='\n')
            campo.erase(campo.size()-1);
    }
}

void udeaBook::impAmigos(unsigned long int& iteraciones)
{
    amigos_imp_reservados=0;
    int c_u=amistades.getCantidad_usuarios(),amigos=0;
    for(int j=0; j<c_u;j++)
    {
        iteraciones++;
        if( amistades.getMarca(usuario_actual,j) && amistades.getMarca(j,usuario_actual))
            amigos++;
    }
    if(amigos==0)
    {
        cout<<"en este momento no tienes amigos para imprimir"<<endl;
        return;
    }
    int* indice_amigos=new int[amigos];
    int* prob_amigos=new int[amigos];
    int k=0;
    for (int j = 0; j < c_u && k < amigos; j++)
    {
        iteraciones++;
        if (amistades.getMarca(usuario_actual, j) && amistades.getMarca(j, usuario_actual))
        {
            int comunes = amistades.amigosEnComun(usuario_actual, j, iteraciones);
            indice_amigos[k] = j;
            if (comunes <= 10)
                prob_amigos[k] = 10;
            else if (comunes <= 20)
                prob_amigos[k] = 25;
            else
                prob_amigos[k] = 35;
            k++;
        }
    }
    amigos=k;
    mt19937 generador(random_device{}());
    short int cuantos=(amigos<6)?amigos:6;
    int primeros[3];
    short int c_primeros=0;

    int total=0;
    for(int i=0;i<amigos;i++)
    {
        iteraciones++;
        total+=prob_amigos[i];
    }
    int disponibles=amigos;

    for(short int e=0;e<cuantos;e++)
    {
        iteraciones++;
        uniform_int_distribution<int>dist(0,total-1);
        int r=dist(generador);
        int acumulado=0,sel=0;
        for(int i=0;i<disponibles;i++)
        {
            iteraciones++;
            acumulado+=prob_amigos[i];
            if(r<acumulado)
            {
                sel=i;break;
            }
        }
        if(e<3)
            primeros[c_primeros++]=indice_amigos[sel];
        else
            amigos_imp[amigos_imp_reservados++]=indice_amigos[sel];
        total-=prob_amigos[sel];
        indice_amigos[sel]=indice_amigos[disponibles-1];
        prob_amigos[sel]=prob_amigos[disponibles-1];
        disponibles--;
    }
    delete[]indice_amigos;
    delete[]prob_amigos;
    impRutasPerfil(primeros,c_primeros,iteraciones);
}

void udeaBook::buscarPorIndices(const int* indices, int cantidad,
                             const usuario** salida, unsigned long& iteraciones)
{
    for (int t = 0; t < cantidad; t++)
    {
        iteraciones++;
        salida[t] = 0;
    }

    int n = usuarios.tamanio();
    int encontrados = 0;

    for (int k = 0; k < n && encontrados < cantidad; k++)
    {
        iteraciones++;
        for (int t = 0; t < cantidad; t++)
        {
            iteraciones++;
            if (indices[t] == k)
            {
                salida[t] = &usuarios.en(k, iteraciones);
                encontrados++;
                break;
            }
        }
    }
}
int udeaBook::b_inidicePorNombre(const string& nombre, unsigned long int& iteraciones) const
{
    int n = usuarios.tamanio();
    for (int k = 0; k < n; k++)
    {
        iteraciones++;
        if (usuarios.en(k, iteraciones).getNombre() == nombre)
            return k;
    }
    return -1;
}
void udeaBook::impRutasPerfil(const int* indices, int cantidad,
                              unsigned long int& iteraciones)
{
    if (cantidad <= 0)
        return;

    const usuario** encontrados = new const usuario*[cantidad];
    buscarPorIndices(indices, cantidad, encontrados, iteraciones);

    for (int t = 0; t < cantidad; t++)
    {
        iteraciones++;
        if (encontrados[t] != 0) {
            cout << encontrados[t]->getNombre() << endl;
            cout << "   " << encontrados[t]->r_fotoPerfil("/users/udeaBook") << endl;
        }
    }
    delete[] encontrados;
}
unsigned long udeaBook::memoriaUdeaBook() const
{
    unsigned long total = sizeof(udeaBook);

    // la subruta
    if (subruta.capacity() > 15)
        total += subruta.capacity() + 1;
    // la matriz de relaciones
    total += amistades.memoriaRelaciones() - sizeof(relaciones);
    // los nodos de la lista de usuarios
    total += usuarios.memoria();
    // los usuarios
    unsigned long basura = 0;
    for (int i = 0; i < usuarios.tamanio(); i++)
        total += usuarios.en(i, basura).memoriaUsuario() - sizeof(usuario);
    return total;
}
bool udeaBook::enviar_solicitud(const string& nombre, unsigned long int& iteraciones)
{
    int j=b_inidicePorNombre(nombre,iteraciones);
    if(j<0)
    {
        cout<<"este usuario no existe crark"<<endl;
        return false;
    }
    if (j == usuario_actual)
    {
        cout << "No te puedes auto solicitar amistad :(" << endl;
        return false;
    }

    bool su_marca = amistades.getMarca(j, usuario_actual);
    bool mi_marca  = amistades.getMarca(usuario_actual, j);

    if (mi_marca && su_marca)
    {
        cout << "Ya son amigos." << endl;
        return false;
    }
    if (su_marca)
    {
        cout << "Ya le envio una solicitud a " << nombre << "." << endl;
        return false;
    }
    if (mi_marca)
    {
        cout << nombre << " ya le envio una solicitud a usted. Aceptela." << endl;
        return false;
    }
    amistades.setMarca(j, usuario_actual, true);
    cout << "Solicitud enviada a " << nombre << endl;
    return true;
}
//cargar()
bool udeaBook:: cargarUsuarios_txt(const string& ruta, unsigned long int& iteraciones)
{
    ifstream archivo(ruta.c_str());
    if(!archivo.is_open())
        return false;
    string campo;
    if(!getline(archivo,campo))
        return false;
    int c_u=stoi(campo);
    if(c_u<=0)
        return false;
    amistades.setCantidadUsuarios(c_u);
    for(int i=0;i<c_u;i++)
    {
        iteraciones++;
        string c[7];
        for(short int k=0;k<6;k++)
        {
            iteraciones++;
            if(!getline(archivo,c[k],';'))
                return false;
        }
        if(!getline(archivo,c[6]))
            return false;
        limpiarCampo(c[6]);
        fecha nacimiento, inscripcion;
        if(!nacimiento.desdeTexto(c[5],iteraciones))
            return false;
        if(!inscripcion.desdeTexto(c[6],iteraciones))
            return false;
        usuarios.agregarAlFinal(usuario(c[0],c[1],c[2],c[3],
                                        c[4],nacimiento,inscripcion));
    }
    return true;
}

bool udeaBook::cargarRelaciones_txt(const string& ruta,unsigned long int& iteraciones)
{
    ifstream archivo(ruta.c_str());
    if(!archivo.is_open())
        return false;
    string campo;
    int c_u=amistades.getCantidad_usuarios();
    while(getline(archivo,campo,';'))
    {
        iteraciones++;
        int i=stoi(campo);
        if(!getline(archivo,campo))
            return false;
        limpiarCampo(campo);
        int j=stoi(campo);
        if(i>=c_u || j>=c_u)
            return false;
        amistades.setMarca(i,j,1);
    }
    return true;
}

bool udeaBook:: cargarMensajes_txt(const string& ruta, unsigned long int& iteraciones)
{
    ifstream archivo(ruta.c_str());
    if (!archivo.is_open())
        return false;

    string campo, texto;

    while (getline(archivo, campo, ';'))
    {
        iteraciones++;
        limpiarCampo(campo);
        if (campo.empty())
            break;
        int receptor = stoi(campo);

        if (!getline(archivo, campo, ';'))
            return false;
        int emisor = stoi(campo);

        if (!getline(archivo, campo, ';'))
            return false;
        fecha envio;
        if (!envio.desdeTexto(campo, iteraciones))
            return false;

        if (!getline(archivo, campo, ';'))
            return false;
        bool leido = (campo == "1");

        if (!getline(archivo, texto))
            return false;
        limpiarCampo(texto);

        if (receptor < 0 || receptor >= usuarios.tamanio())
            return false;
        if (emisor < 0 || emisor >= usuarios.tamanio())
            return false;

        mensaje m;
        if (!m.setTexto(texto))
            return false;
        m.setEnvio(envio);
        m.setEmisor(emisor);
        m.setLeido(leido);

        usuarios.en(receptor, iteraciones).recibirMensaje(m);
    }
    return true;
}
bool udeaBook::cargarAlbums_txt(const string& ruta, unsigned long int& iteraciones)
{
    ifstream archivo(ruta.c_str());
    if (!archivo.is_open())
        return false;

    int indiceDueno = -1;
    int indiceAlbum = -1;
    string campo;

    while (getline(archivo, campo, ';'))
    {
        iteraciones++;
        limpiarCampo(campo);
        if (campo.empty())
            break;
        //aqui se guarda el album
        if (campo == "A")
        {
            if (!getline(archivo, campo, ';'))
                return false;
            indiceDueno = stoi(campo);
            if (indiceDueno < 0 || indiceDueno >= usuarios.tamanio())
                return false;
            string nombre;
            if (!getline(archivo, nombre, ';'))
                return false;

            if (!getline(archivo, campo))
                return false;
            limpiarCampo(campo);
            if (campo.empty())
                return false;
            album a;
            if (!a.setNombre(nombre))
                return false;
            if (!a.setPrivacidad(campo[0]))
                return false;
            usuario& u = usuarios.en(indiceDueno, iteraciones);
            u.agregarAlbum(a);
            indiceAlbum = u.getAlbums().tamanio() - 1;
        }
        //aqui se guardan las fotos del album anterior
        else if (campo == "F")
        {
            if (indiceDueno < 0 || indiceAlbum < 0)
                return false;
            string nombre;
            if (!getline(archivo, nombre, ';'))
                return false;
            if (!getline(archivo, campo, ';'))
                return false;
            fecha captura;
            if (!captura.desdeTexto(campo, iteraciones))
                return false;
            if (!getline(archivo, campo, ';'))
                return false;
            int tamanio = stoi(campo);
            if (!getline(archivo, campo))
                return false;
            limpiarCampo(campo);
            int likes = stoi(campo);
            foto f(nombre, captura, likes, tamanio);
            usuario& u = usuarios.en(indiceDueno, iteraciones);
            u.getAlbums().en(indiceAlbum, iteraciones).agregarfoto(f);
        }
        else
            return false;                           // marcador desconocido
    }
    return true;
}
//guardar()
bool udeaBook::guardarUsuarios_txt(const string& ruta, unsigned long int& iteraciones) const
{
    ofstream archivo(ruta.c_str());
    if(!archivo.is_open())
        return false;
    int n=usuarios.tamanio();
    archivo<<n<<'\n';
    for(int i=0;i<n;i++)
    {
        iteraciones++;
        //archivo<<usuarios.en(i,iteraciones)<<'\n';
    }
    return true;
}
bool udeaBook::guardarRelaciones_txt(const string& ruta, unsigned long int& iteraciones) const
{
    ofstream archivo(ruta.c_str());
    if (!archivo.is_open())
        return false;

    unsigned int c_u = amistades.getCantidad_usuarios();
    unsigned int espacios = amistades.getEspaciosFila();
    const unsigned long long* m = amistades.getAmistades();

    for (unsigned int i = 0; i < c_u; i++)
    {
        for (unsigned int k = 0; k < espacios; k++)
        {
            iteraciones++;
            unsigned long long w = m[i * espacios + k];
            while (w != 0)
            {
                iteraciones++;
                unsigned int j = k * 64 + relaciones::u_BitMasBajo(w);
                archivo << i << ';' << j << '\n';
                w &= w - 1;
            }
        }
    }
    return true;
}
bool udeaBook::guardarMensajes_txt(const string& ruta, unsigned long int& iteraciones) const
{
    ofstream archivo(ruta.c_str());
    if (!archivo.is_open())
        return false;
    int n = usuarios.tamanio();
    for (int i = 0; i < n; i++)
    {
        iteraciones++;
        const lista<mensaje>& recibidos = usuarios.en(i, iteraciones).getRecibidos();

        for (int m = 0; m < recibidos.tamanio(); m++)
        {
            iteraciones++;
            archivo << i << ';' << recibidos.en(m, iteraciones) << '\n';
        }
    }
    return true;
}
bool udeaBook::guardarAlbums_txt(const string& ruta, unsigned long int& iteraciones) const
{
    ofstream archivo(ruta.c_str());
    if(archivo.is_open())
        return false;
    int n = usuarios.tamanio();
    for (int i = 0; i < n; i++)
    {
        iteraciones++;
        const lista<album>& albumes = usuarios.en(i, iteraciones).getAlbums();

        for (int a = 0; a < albumes.tamanio(); a++)
        {
            iteraciones++;
            const album& al = albumes.en(a, iteraciones);
            archivo << "A;" << i << ';' << al << '\n';

            const lista<foto>& fotos = al.getcoleccionfotos();
            for (int f = 0; f < fotos.tamanio(); f++)
            {
                iteraciones++;
                archivo << "F;" << fotos.en(f, iteraciones) << '\n';
            }
        }
    }
    return true;
}
//operadores
udeaBook& udeaBook::operator=(const udeaBook& otro)
{
    if (this != &otro) {
        amistades = otro.amistades;
        usuarios = otro.usuarios;
        usuario_actual = otro.usuario_actual;
        amigos_imp_reservados = otro.amigos_imp_reservados;
        for (int i = 0; i < 3; i++)
            amigos_imp[i] = otro.amigos_imp[i];
    }
    return *this;
}
bool udeaBook::operator==(const udeaBook& otro) const
{
    return usuarios == otro.usuarios && amistades == otro.amistades;
}








