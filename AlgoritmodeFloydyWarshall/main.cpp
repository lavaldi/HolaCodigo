#include <cstdlib>
#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <sys\stat.h>
#define DELIM_C "*"

using namespace std;
struct nodo{
    double latd;
    double lond;
}r;
struct adyacente{
       int peso;
       int adya;
}d;
int P[72][72];
int I[72][72];
int x,y,cont=1,dist;
int C[1000];
void escribir()// permite crear un fichero para guardar la informacion de los vertices y aristas
{
     int fn,fa;
     int ln=sizeof(struct nodo);
     int la=sizeof(struct adyacente);
         cout<<"UBICACION DE VERTICES - CENTRO HISTORICO"<<endl;
     /*if((fn=creat("ch-ub.txt",S_IWRITE|S_IREAD))<0)
     {
          return;
     }
     for(int i=0;i<72;i++)         
     {
            fflush(stdin);
            cout<<"Ubicacion del vertice V["<<i+1<<"] :  "<<endl;
            cout<<"ingrese la latitud : ";
            cin>>r.latd;
            fflush(stdin);
            cout<<"ingrese la longitud :  ";
            cin>>r.lond;
            write(fn,&r,ln);
            fflush(stdin);
            cout<<endl;
    }            
    close(fn);*/
    if((fa=creat("ch-ady.txt",S_IWRITE|S_IREAD))<0)
     {
          return;
     }
     cout<<"ARISTAS"<<endl;
     for(int i=0;i<72;i++)
     {
             for(int j=0;j<72;j++)
             {
                     d.adya=0;
                     d.peso=10000;
                     write(fa,&d,la);
             }
     }
     close(fa);
                                                           
}
void configurar_V()
{
     int fn,pos,i,flag=1;
     int ln=sizeof(struct nodo);
     fn=open("ch-ub.txt",O_RDWR);
     cout<<"UBICACION DE VERTICES - CENTRO HISTORICO"<<endl;
      while(flag==1)
     {
             cout<<"Ingrese el numero de vertice:   ";
             cin>>i;
             pos=(i-1)*ln;
             lseek(fn,pos,0);
             cout<<"ingrese la latitud : ";
             cin>>r.latd;
             fflush(stdin);
             cout<<"ingrese la longitud :  ";
             cin>>r.lond;
             write(fn,&r,ln);
             fflush(stdin);
             cout<<endl;
             cout<<"continuar 0/1:  ";
             cin>>flag;
     }
     close(fn);
}
void configurar_A()
{
     int fa,pos,i,j,flag=1;
     int la=sizeof(struct adyacente);
     fa=open("ch-ady.txt",O_RDWR);
     cout<<"ARISTAS"<<endl;
     while(flag==1)
     {
                     fflush(stdin);
                     cout<<"ingrese la arista a leer de la matriz de adyacencia :"<<endl;
                     cout<<"Fila:  ";
                     cin>>i;
                     cout<<"Columna:  ";
                     cin>>j;
                     pos=(i-1)*la*72+(j-1)*la;
                     lseek(fa,pos,0);
                     d.adya=1;
                     fflush(stdin);
                     cout<<"Distancia:  ";
                     cin>>d.peso;
                     cout<<endl;
                     write(fa,&d,la);
                     cout<<"continuar 0/1:  ";
                     cin>>flag;
     }
     close(fa);
}
void leer_V(int v)
{
     int fn,pos,nsimo;
     int ln=sizeof(struct nodo);
     fn=open("ch-ub.txt",O_RDWR);
     pos=(v-1)*ln;
     lseek(fn,pos,0);
     read(fn,&r,ln);
     cout<<"La latitud del vertice "<<v<<" es:  "<<r.latd<<" metros"<<endl;
     cout<<"La longitud del vertice  "<<v<<" es:  "<<r.lond<<" metros"<<endl;
     close(fn);
}
void leer_A()
{
     int fa,pos,i,j;
     int la=sizeof(struct adyacente);
     fa=open("ch-ady.txt",O_RDWR);
     cout<<"ingrese la arista a leer de la matriz de adyacencia :"<<endl;
     cout<<"Fila:  ";
     cin>>i;
     cout<<"Columna:  ";
     cin>>j;
     pos=(i-1)*la*72+(j-1)*la;
     lseek(fa,pos,0);
     read(fa,&d,la);
     cout<<d.adya<<endl<<d.peso<<endl;
     close(fa);
}
void matriz_peso_int()
{
    int fa,pos,a,u;
    int la=sizeof(struct adyacente);
    fa=open("ch-ady.txt",O_TEXT);
    for(int i=1;i<=72;i++)
    {
        for(int j=1;j<=72;j++)
        {
            pos=(i-1)*la*72+(j-1)*la;
            lseek(fa,pos,0);
            read(fa,&d,la);
            u=d.peso;
            P[i][j]=u;
            I[i][j]=j;
            if(i==j)
            {
                P[i][j]=0;
                I[i][j]=0;
            }
        }
    }
    for(int k=1;k<=72;k++)
    {
        for(int i=1;i<=72;i++)
        {
            for(int j=1;j<=72;j++)
            {
                a=P[i][k]+P[k][j];
                if(a<P[i][j])
                {
                    P[i][j]=a;
                    I[i][j]=k;
                }
            }
        }
    }
                       
}

void camino(int v1,int v2)
{
     y=v2;
     
     while(y!=x)
     {
              y=v2;
              v2=I[v1][v2];
              x=v2;
              C[cont]=y;
              cont++;
     }
     C[cont]=v1;
     while(cont!=0)
     {
                   cout<<"v"<<C[cont]<<" -> ";
                   cont--;
     }
     cout<<"O!!!";              
}          
int main(int argc, char *argv[])
{
    int v1,v2;
    //escribir();
    matriz_peso_int();
    cout<<"       CENTRO HISTORICO"<<endl;
    cout<<"Tomando como referencia el mapa del centro historico"<<endl<<"tome los vertices para ayar el camino"<<"mas corto y hallar la ruta"<<endl<<endl<<endl;
    cout<<endl<<"Vertice inicial:  ";
    cin>>v1;
    leer_V(v1);
    cout<<endl<<"Vertice final:  ";
    cin>>v2;
    leer_V(v2);
    dist=P[v1][v2];
    cout<<endl<<"El el camino a recorrer es:"<<endl;
    camino(v1,v2);
    cout<<endl<<endl<<"La distancia total recorida:  "<<dist<<" metros."<<endl;
    //leer_A();
    //configurar_V();
    //configurar_A();
    system("PAUSE");
    return EXIT_SUCCESS;
}
