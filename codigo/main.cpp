#include <iostream>
#include "udeabook.h"

using namespace std;

int main()
{
    udeaBook plataforma;
    unsigned long int iteraciones=0;
    //cargar datos()
    cout<<"--cargando datos de los .txt--"<<endl;
    if(plataforma.cargarTodo(iteraciones)) {return 1;}
    cout << "+ ejecucion de libreria fstream, string" << endl;
    //iniciar sesion()
    if(!plataforma.iniciarSesion(iteraciones))
    {
        cout<<"chaos esperamos buena critica :)"<<endl;
        return 0;
    }
    plataforma.reportarEficiencia(iteraciones);
    short int decision=0;
    int amigos_ind[6],amigos_cantidad=0,amigos_desde=0; const usuario* amigos[6];
    amigos_cantidad=plataforma.calcAmigos(amigos_ind,iteraciones);
    //los amigos a imprimir
    cout<<endl<<"---eliguiendo amigos a imprimir---";
    plataforma.buscarPorIndices(amigos_ind,amigos_cantidad,amigos,iteraciones);
    plataforma.reportarEficiencia(iteraciones); cout << "+ ejecucion de libreria random" << endl;
    while(decision!=9)
    {
        cout<<endl<<"---udeaBook---"<<endl;
        plataforma.impAmigos(amigos,amigos_cantidad,amigos_desde);
        cout<<endl<<"1. recargar mejores amigos"<<endl;
        cout<<"2. administrar amistades"<<endl;
        cout<<"3. ver albums de un usuario"<<endl;
        cout<<"4. administrar mensajes"<<endl;
        cout<<"5. recomendaciones de amistad"<<endl;
        cout<<"9. salir"<<endl;
        decision=plataforma.leerEntero("opcion: ");
        cout<<endl;
        if(decision==1)
        {
            if(!plataforma.recargarAmigos(amigos_desde,amigos_cantidad))
            {cout << "ya no puedes recargar" << endl;}
            else
            {plataforma.reportarEficiencia(iteraciones);}
        }
        else if(decision==2)
        {
            plataforma.decision2(iteraciones,decision);
        }
        else if(decision==3)
        {
            string nombre=plataforma.leerTexto("de quien desea ver los albums: ",true);
            int j=plataforma.mostrar_albums(nombre,iteraciones);
            if(j>=0)
            {
                int i=plataforma.leerEntero("identificador del album elegido(-1 pa salir): ");
                if(i>=0)
                {plataforma.recorrer_album(j,i,iteraciones);}
            }
            plataforma.reportarEficiencia(iteraciones);
        }
        else if(decision==4)
        {
            plataforma.decision4(iteraciones,decision);
        }
        else if(decision==5)
        {
            plataforma.decision5(iteraciones);
        }
    }
    plataforma.guardarTodo(iteraciones);
    return 0;
}
















