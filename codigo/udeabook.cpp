#include "udeabook.h"
#include <fstream>
#include <random>
const string udeaBook::subruta = "/users/udeabook2026";
udeaBook::udeaBook() : usuario_actual(-1){}

udeaBook::udeaBook(const udeaBook& otro): amistades(otro.amistades), usuarios(otro.usuarios),usuario_actual(otro.usuario_actual){}

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


//get()
const relaciones& udeaBook::getAmistades() const { return amistades; }
relaciones& udeaBook::getAmistades() { return amistades; }
const lista<usuario>& udeaBook::getUsuarios() const { return usuarios; }
lista<usuario>& udeaBook::getUsuarios() { return usuarios; }
int udeaBook::getUsuarioActual() const { return usuario_actual; }
//funciones
void udeaBook::limpiarCampo(string& campo)
{
    if(!campo.empty())
    {
        if(campo[campo.size()-1]=='\r' || campo[campo.size()-1]=='\n')
            campo.erase(campo.size()-1);
    }
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

int udeaBook::mostrar_solicitudes(unsigned long int& iteraciones)const
{
    int c_u=usuarios.tamanio();
    int cuantos=0;
    for(int j=0;j<c_u;j++)
    {
        iteraciones++;
        if(amistades.getMarca(usuario_actual,j) && !amistades.getMarca(j,usuario_actual))
        {
            cuantos++;
            cout<<"identificador: "<<j<<". nombre: "<<usuarios.en(j,iteraciones).getNombre()<<endl;
        }
    }
    if(cuantos==0)
        cout<<"tranqui ya te llegaran las solicitudes ;)"<<endl;
    return cuantos;
}
bool udeaBook::aceptar_solicitudes(const int j)
{
    if(j<0)
    {
        cout<<"este usuario no existe"<<endl;
        return false;
    }
    if (!amistades.getMarca(usuario_actual, j) || amistades.getMarca(j, usuario_actual))
    {
        cout << "No hay una solicitud pendientes de este usuario" << endl;
        return false;
    }
    amistades.setMarca(j, usuario_actual, true);
    cout << "Ahora son amigos." << endl;
    return true;
}
int udeaBook::mostrar_albums(const string& nombre,unsigned long int& iteraciones)
{
    if (usuario_actual < 0)
    {
        cout << "Debe iniciar sesion." << endl;
        return -1;
    }
    int j = b_inidicePorNombre(nombre, iteraciones);
    if (j < 0)
    {
        cout << "usuario ingresado no valido" << endl;
        return -1;
    }
    bool esDueno = (j == usuario_actual);
    bool esAmigo = amistades.getMarca(j, usuario_actual) &&
                   amistades.getMarca(usuario_actual, j);
    const lista<album>& al = usuarios.en(j, iteraciones).getAlbums();
    int tam = al.tamanio();
    int visibles = 0;
    for (int i = 0; i < tam; i++)
    {
        iteraciones++;
        const album& a = al.en(i, iteraciones);
        if (a.visiblePara(esAmigo, esDueno))
        {
            visibles++;
            cout << "identificador: " << i << ". nombre: " << a.getNombre() << endl;
        }
    }
    if (visibles == 0)
    {
        cout << "no hay albums que usted pueda ver" << endl;
        return -1;
    }
    return j;
}
void udeaBook::recorrer_album(int j,int i,unsigned long int& iteraciones)
{
    usuario& dueno = usuarios.en(j, iteraciones);
    lista<album>& albums = dueno.getAlbums();
    if (i < 0 || i >= albums.tamanio())
    {
        cout << "ese album no existe" << endl;
        return;
    }
    album& elegido = albums.en(i, iteraciones);
    bool esDueno = (j == usuario_actual);
    bool esAmigo = amistades.getMarca(j, usuario_actual) &&
                   amistades.getMarca(usuario_actual, j);
    if (!elegido.visiblePara(esAmigo, esDueno))
    {
        cout << "ese album no esta disponible" << endl;
        return;
    }
    lista<foto>& fotos = elegido.getColeccionFotos();
    int tam = fotos.tamanio();
    if (tam == 0)
    {
        cout << "ese album no tiene fotos" << endl;
        return;
    }

    string rutaAlbum = subruta + "/" + dueno.getNombre() + "/albums/" + elegido.getNombre();
    int actual = 0;
    int opcion = 0;

    while (opcion != 5)
    {
        iteraciones++;
        foto& f = fotos.en(actual, iteraciones);
        cout << endl;
        cout << "foto " << (actual + 1) << " de " << tam << endl;
        cout << f.rutaFoto(rutaAlbum) << endl;
        cout << "capturada: " << f.getPublicada()
             << "   " << f.getTamanio() << " KB"
             << "   " << f.getLikes() << " likes" << endl;
        cout << "1. siguiente  2. anterior  3. dar like  4. quitar like  5. salir" << endl;
        opcion = leerEntero("opcion: ");
        if (opcion == 1)
            actual = (actual + 1) % tam;
        else if (opcion == 2)
            actual = (actual - 1 + tam) % tam;
        else if (opcion == 3)
        {
            if (!f.darLike())
                cout << "no se pudo dar like" << endl;
        }
        else if (opcion == 4)
        {
            if (!f.quitarLike())
                cout << "la foto no tiene likes" << endl;
        }
        else if (opcion != 5)
            cout << "opcion invalida" << endl;
    }
}
int udeaBook::leerEntero(const string& mensaje)
{
    int valor;
    cout << mensaje;
    while (!(cin >> valor))
    {
        cin.clear();
        cin.ignore(30000, '\n');
        cout << "debe ingresar un numero: ";
    }
    cin.ignore(30000, '\n');
    return valor;
}
string udeaBook::leerTexto(const string& mensaje, bool obligatorio)
{
    string texto;
    while (true)
    {
        cout << mensaje;
        getline(cin, texto);
        limpiarCampo(texto);
        if (!obligatorio || !texto.empty())
            return texto;
        cout << "no puede estar vacio" << endl;
    }
}
int udeaBook::calcAmigos(int* indices, unsigned long int& iteraciones)
{
    if (indices == 0 || usuario_actual < 0)
        return 0;

    int c_u = amistades.getCantidad_usuarios();
    int amigos = 0;
    for (int j = 0; j < c_u; j++)
    {
        iteraciones++;
        if (j != usuario_actual &&
            amistades.getMarca(usuario_actual, j) &&
            amistades.getMarca(j, usuario_actual))
            amigos++;
    }

    if (amigos == 0)
        return 0;
    int* ind = new int[amigos];
    int* prob = new int[amigos];
    int  k = 0;
    int  total = 0;

    for (int j = 0; j < c_u && k < amigos; j++)
    {
        iteraciones++;
        if (j != usuario_actual &&
            amistades.getMarca(usuario_actual, j) &&
            amistades.getMarca(j, usuario_actual))
        {
            int comunes = amistades.amigosEnComun(usuario_actual, j, iteraciones);

            if (comunes <= 10)
                {prob[k] = 10;}
            else if (comunes <= 20)
                {prob[k] = 25;}
            else
                {prob[k] = 35;}
            ind[k] = j;
            total += prob[k];
            k++;
        }
    }

    //ruleta del gamblin
    int cuantos = (amigos < 6) ? amigos : 6;
    mt19937 generador(random_device{}());
    for (int s = 0; s < cuantos; s++)
    {
        iteraciones++;
        uniform_int_distribution<int> dado(1, total);
        int tiro = dado(generador);
        int acumulado = 0;
        int sel = s;
        for (int t = s; t < amigos; t++)
        {
            iteraciones++;
            acumulado += prob[t];
            if (acumulado >= tiro)
                { sel = t; break; }
        }

        int ti = ind[s]; ind[s] = ind[sel]; ind[sel] = ti;
        int tp = prob[s]; prob[s] = prob[sel]; prob[sel] = tp;

        indices[s] = ind[s];
        total -= prob[s];
    }
    delete[] ind;
    delete[] prob;

    return cuantos;
}
void udeaBook::impAmigos(const usuario** amigos, int cantidad, int desde) const
{
    cout << "mejores amigos:" << endl;

    if (amigos == 0 || cantidad <= 0)
    {
        cout << "  (aun no tiene amigos)" << endl;
        return;
    }

    if (desde < 0)         desde = 0;
    if (desde >= cantidad) return;

    int fin = desde + AMIGOS_POR_PAG;
    if (fin > cantidad) fin = cantidad;

    for (int s = desde; s < fin; s++)
    {
        if (amigos[s] != 0)
            cout << "  " << amigos[s]->r_fotoPerfil(subruta) << endl;
    }
}
void udeaBook::buscarMensajesPorFecha(const fecha& inicio, const fecha& fin, unsigned long int& iteraciones)
{
    if (usuario_actual < 0 || usuario_actual >= usuarios.tamanio()) {
        cout << "Error: No hay un usuario logueado." << endl;
        return;
    }
    usuario& u = usuarios.en(usuario_actual, iteraciones);
    lista<mensaje>& misMensajes = u.getRecibidos();
    int n = misMensajes.tamanio();
    int encontrados = 0;
    cout << "--- mensajes entre " << inicio << " y " << fin << " ---" << endl;
    for (int i = 0; i < n; i++)
    {
        iteraciones++;
        mensaje& m = misMensajes.en(i, iteraciones);
        fecha f = m.getFecha_envio();
        if (f >= inicio && f <= fin)
        {
            m.setleido(true);
            const usuario& emisor = usuarios.en(m.getEmisor(), iteraciones);
            cout << "De: " << emisor.getNombre() << " " << m.getFecha_envio() << endl;
            cout << m.getTexto() << endl << endl;
            encontrados++;
        }
        else if (!(f <= fin)) {
            break;
        }
    }

    if (encontrados == 0) {
        cout << "No se encontraron mensajes en este rango de fechas." << endl;
    }
}

void udeaBook::buscarMensajesNoLeidos(unsigned long int& iteraciones)
{
    if (usuario_actual < 0 || usuario_actual >= usuarios.tamanio()) {
        return;
    }
    usuario& u = usuarios.en(usuario_actual, iteraciones);
    lista<mensaje>& misMensajes = u.getRecibidos();
    int n = misMensajes.tamanio();
    int encontrados = 0;
    cout << "--- Mensajes No Leidos ---" << endl;
    for (int i = 0; i < n; i++)
    {
        iteraciones++;
        mensaje& m = misMensajes.en(i, iteraciones);
        if (!m.getleido())
        {
            m.setleido(true);
            const usuario& emisor = usuarios.en(m.getEmisor(), iteraciones);
            cout << "De: " << emisor.getNombre() << " " << m.getFecha_envio() << endl;
            cout << m.getTexto() << endl << endl;
            encontrados++;
        }
    }
    if (encontrados == 0) {
        cout << "No tienes mensajes nuevos por leer." << endl;
    }
}
bool udeaBook::enviarMensaje(int indice_receptor, const string& texto, unsigned long int& iteraciones)
{
    if (usuario_actual < 0)
    {cout << "debe iniciar sesion" << endl; return false;}
    if (indice_receptor < 0 || indice_receptor >= usuarios.tamanio())
    {cout << "el usuario receptor no existe" << endl; return false;}
    if (indice_receptor == usuario_actual)
    { cout << "no se puede enviar un mensaje a usted mismo" << endl; return false;}
    mensaje m;
    if (!m.setTexto(texto))
    { cout << "mensaje invalido: pasa de 512 caracteres o contiene ';'" << endl; return false;}

    m.setEmisor(usuario_actual);
    m.setFecha_envio(fecha::fechaHoy(iteraciones));
    m.setleido(false);

    usuarios.en(indice_receptor, iteraciones).recibirMensaje(m);
    cout << "mensaje enviado" << endl;
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
int udeaBook::recomendaciones_amistades(int k,int* indices,unsigned long int& iteraciones)
{
    if (indices == 0 || usuario_actual < 0)
        return 0;
    if (k < 1 || k > 20)
    {
        cout << "la cantidad debe estar entre 1 y 20" << endl;
        return 0;
    }
    int comunes[20];
    int c_u = amistades.getCantidad_usuarios();
    int cuantos = 0;
    for (int j = 0; j < c_u; j++)
    {
        iteraciones++;
        if (j == usuario_actual)
            continue;
        if (amistades.getMarca(usuario_actual, j) &&
            amistades.getMarca(j, usuario_actual))
            continue;
        int enComun = amistades.amigosEnComun(usuario_actual, j, iteraciones);
        if (enComun == 0)
            continue;
        //aqui hacemos la organizacion
        if (cuantos < k || enComun > comunes[cuantos - 1])
        {
            int pos = (cuantos < k) ? cuantos : k - 1;
            while (pos > 0 && comunes[pos - 1] < enComun)
            {
                iteraciones++;
                comunes[pos] = comunes[pos - 1];
                indices[pos] = indices[pos - 1];
                pos--;
            }
            comunes[pos] = enComun;
            indices[pos] = j;
            if (cuantos < k)
                cuantos++;
        }
    }
    return cuantos;
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
        limpiarCampo(campo);
        if(campo.empty())
            break;
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
        m.setFecha_envio(envio);
        m.setEmisor(emisor);
        m.setleido(leido);

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
            u.getAlbums().en(indiceAlbum, iteraciones).agregarFoto(f);
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
        archivo<<usuarios.en(i,iteraciones)<<'\n';
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
    if(!archivo.is_open())
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

            const lista<foto>& fotos = al.getColeccionFotos();
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
    }
    return *this;
}
bool udeaBook::operator==(const udeaBook& otro) const
{
    return usuarios == otro.usuarios && amistades == otro.amistades;
}

//aqui las cositas del main
bool udeaBook::iniciarSesion(unsigned long int& iteraciones)
{
    bool sesionActiva= false;

    while (!sesionActiva)
    {
        cout << endl;
        cout << "--- inicio de sesion ---" << endl;

        string nombre = leerTexto("usuario (vacio para salir): ", false);
        if (nombre.empty()) return false;

        int j = b_inidicePorNombre(nombre, iteraciones);

        if (j < 0)
        {
            cout << "ese usuario no existe" << endl;
        }
        else
        {
            string clave = leerTexto("clave: ", true);

            if (!usuarios.en(j, iteraciones).validarClave(clave))
            {
                cout << "clave incorrecta" << endl;
            }
            else
            {
                setUsuarioActual(j);
                cout << "bienvenido " << nombre << endl;
                sesionActiva = true;
            }
        }
    }
    return true;
}
void udeaBook::reportarEficiencia(unsigned long int& iteraciones)
{
    cout<<endl;
    cout<<"---reporte---"<<endl;
    cout << "iteraciones: " << iteraciones << endl;
    cout << "memoria: " << memoriaUdeaBook() << " bytes" << endl;
    iteraciones=0;
}
bool udeaBook::recargarAmigos(int& desde, int cantidad) const
{
    if (desde != 0)
        return false;  // ya recargo
    if (cantidad <= AMIGOS_POR_PAG)
        return false;  // no hay mas que mostrar
    desde = AMIGOS_POR_PAG;
    return true;
}
bool udeaBook::cargarTodo(unsigned long int&iteraciones)
{
    if (!cargarUsuarios_txt("usuarios.txt", iteraciones))
    {cout << "error al cargar usuarios.txt" << endl; return 1;}
    if (!cargarRelaciones_txt("relaciones.txt", iteraciones))
    {cout << "error al cargar relaciones.txt" << endl; return 1;}
    if (!cargarAlbums_txt("albumes.txt", iteraciones))
    { cout << "error al cargar albumes.txt" << endl; return 1;}
    if (!cargarMensajes_txt("mensajes.txt", iteraciones))
    { cout << "error al cargar mensajes.txt" << endl; return 1; }
    reportarEficiencia(iteraciones);
    return 0;
}

void udeaBook::guardarTodo(unsigned long int& iteraciones)
{
    if (!guardarUsuarios_txt("usuarios.txt", iteraciones))
        cout << "error al guardar usuarios.txt" << endl;
    if (!guardarRelaciones_txt("relaciones.txt", iteraciones))
        cout << "error al guardar relaciones.txt" << endl;
    if (!guardarAlbums_txt("albumes.txt", iteraciones))
        cout << "error al guardar albumes.txt" << endl;
    if (!guardarMensajes_txt("mensajes.txt", iteraciones))
        cout << "error al guardar mensajes.txt" << endl;
    reportarEficiencia(iteraciones);
    cout<<"+ ejecucion de libreria fstream"<<endl;
}
void udeaBook:: decision2(unsigned long int& iteraciones,short int decision)
{
    short int contador=0;
    while(decision!=9)
    {
        cout<<"--- amistades ---"<<endl;
        cout<<"1. enviar solicitud"<<endl;
        cout<<"2. ver y aceptar solicitudes"<<endl;
        cout<<"3. visitar el perfil de un usuario"<<endl;
        cout<<"9. volver"<<endl;
        decision=leerEntero("opcion: ");
        if(decision==1)
        {
            string nombre=leerTexto("nombre del usuario: ",true);
            enviar_solicitud(nombre,iteraciones);
            contador++;
            reportarEficiencia(iteraciones);
        }
        else if(decision==2)
        {
            if(mostrar_solicitudes(iteraciones)>0)
            {
                int quien=leerEntero("identificador del usuario (-1 para ninguno): ");
                if(quien>=0)
                {
                    aceptar_solicitudes(quien);
                    contador++;
                }
            }
            reportarEficiencia(iteraciones);
        }
        else if(decision!=9){cout<<"opcion no valida men"<<endl;}
    }
    if(contador>=5)
    {
        cout<<endl<<"---guardando relaciones.txt---"<<endl;
        guardarRelaciones_txt("relaciones.txt",iteraciones);
        reportarEficiencia(iteraciones);
    }
}
void udeaBook::decision4(unsigned long int& iteraciones,short int decision)
{
    short int contador=0;
    while (decision != 9)
    {
        iteraciones = 0;

        cout << endl;
        cout << "--- mensajes ---" << endl;
        cout << "1. enviar mensaje" << endl;
        cout << "2. ver mensajes no leidos" << endl;
        cout << "3. buscar mensajes por rango de fechas" << endl;
        cout << "9. volver" << endl;
        decision=leerEntero("opcion: ");
        if (decision == 1)
        {
            string nombre = leerTexto("para quien: ", true);
            int j =b_inidicePorNombre(nombre, iteraciones);
            if (j < 0)
            {cout << "ese usuario no existe" << endl;}
            else
            {
                string texto =leerTexto("mensaje: ", true);
                enviarMensaje(j, texto, iteraciones);
                contador+=3;
            }
            reportarEficiencia(iteraciones);
            cout << "+ ejecucion de libreria chrono" << endl;
        }
        else if(decision==2)
        {
            buscarMensajesNoLeidos(iteraciones);
            contador+=2;
            reportarEficiencia(iteraciones);
        }
        else if(decision==3)
        {
            fecha desde,hasta;
            string texto;
            texto=leerTexto("desde (AAAA-MM-DD): ",true);
            if (!desde.desdeTexto(texto, iteraciones))
                cout << "fecha invalida" << endl;
            else
            {
                texto = leerTexto("hasta (AAAA-MM-DD): ", true);
                if (!hasta.desdeTexto(texto, iteraciones))
                    {cout << "fecha invalida" << endl;}
                else if (!(desde <= hasta))
                    {cout << "la fecha final es anterior a la inicial" << endl;}
                else
                {
                    buscarMensajesPorFecha(desde, hasta, iteraciones);
                    contador++;
                }
            }
            reportarEficiencia(iteraciones);
        }
        else if(decision!=9)
            {cout<<"opcion no valida mon ami"<<endl;
        }
    }
    if(contador>=5)
    {
        cout<<endl<<"---guardando mensajes.txt---"<<endl;
        guardarMensajes_txt("mensajes.txt",iteraciones);
        reportarEficiencia(iteraciones);
    }
}
void udeaBook::decision5(unsigned long int& iteraciones)
{
    int indices[20];
    const usuario* sug[20];
    int k=leerEntero("cuantas sugerencias quiere ver? (1 a 20): ");
    int cuantas=recomendaciones_amistades(k,indices,iteraciones);
    if(cuantas==0)
        {cout<<"no hay usuarios que podamos recomendarte"<<endl;}
    else
    {
        buscarPorIndices(indices,cuantas,sug,iteraciones);
        for(int i=0;i<cuantas;i++)
        {
            iteraciones++;
            if(sug[i]!=0)
                {cout<<"*** "<<sug[i]->getNombre()<<" ***"<<endl;}
        }
    }
}