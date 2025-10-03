#include<iostream>
#include<list>
#include<unordered_map>
#include <utility>
#include "grafoNoDirigido.hpp"
#include "grafoDirigido.hpp"
#include <fstream>


using namespace std;


list<int> caminoMasCortoIntermedio(GrafoNoDirigido<int> &g, int a, int b, int intermedio);

int main(){

    GrafoNoDirigido<char> ng;
    Grafo<char> g,g2;
    char v,w;
    int i=0;
    while (cin>> v >> w)
    {
        i++;
        g.agregarArco(v,w,i);
        ng.agregarArco(v,w,i);
        g2.agregarArco(v,w,i);
    }
    g.agregarVertice('Z');
    //g2.agregarVertice('Z');
    ng.agregarVertice('Z');
    //g.vaciar();
    //ng.vaciar();

    cout<< (g==g2? "Son Iguales":"No Son Iguales")<<endl;

    cout<<"Grado de  salida de a: "<<g.getGradoSalida('A')<<endl;
    cout<<"Grado de  entrada de a: "<<g.getGradoEntrada('A')<<endl;
    cout<<"Tiene "<<g.getNVertices()<<" Vertives y "<<g.getMArcos()<<" Arcos."<<endl;

    
    cout<<"Vertices: ";
    list<char> vertices=g.getVertices();
    for (char e : vertices)
    {
        cout<< e << ", ";
    }
    cout<<endl;

    //mapeado
    Grafo<int> gMap=g.getMapGrafo();
    list<int> mapa=gMap.getVertices();
    cout<<"Mapa: ";
    for (int e : mapa)
    {
        cout<< e << ", ";
    }
    cout<<endl;
    //Arcos sin mapear
    list<list<char>> arcos=g.getArcos(),conexas=g.getCompConexas();
    float peso;
    char from,to;
    for (list<char> par: arcos)
    {
        from=par.front();
        to=par.back();
        cout<<"(";
        for (char e : par)
        {
            cout<<e<<" ";
            
        }
        peso=g.getPesoArco(from,to);
        cout<<")= "<<peso<<endl;
    }
    cout<<endl;
    cout<<"Numero de componentes conexas: "<<g.getNumCompConexas()<<endl;
    for (list<char> par: conexas)
    {
        cout<<"Comp: ";
        for (char e : par)
        {
            cout<<e<<" ";
            
        }
        cout<<endl;
    }
    cout<<endl;

    //arcos mapeados
    list<list<int>> arcosMap=gMap.getArcos(),compConexas=gMap.getCompConexas();
    for (list<int> par: arcosMap)
    {
        cout<<"(";
        for (int e : par)
        {
            cout<<e<<" ";
        }
        peso=gMap.getPesoArco(par.front(),par.back());
        cout<<")= "<<peso<<endl;
    }

    for (list<int> par: compConexas)
    {
        cout<<"comp: ";
        for (int e : par)
        {
            cout<<e<<" ";
        }
        cout<<endl;
    }

    //TEST Grafo no dirigido
    vertices=ng.getVertices();
    for (char e : vertices)
    {
        cout<< e << ", ";
    }
    cout<<endl;

    list<char> vecinos;
    vecinos=ng.getSucesores('B');
    for (char e : vecinos)
    {
        cout<<e<<" ";
    }
    cout<<endl<<"Componentes conexas: "<<ng.getNumCompConexas()<<endl;
    arcos=ng.getArcos();
    for (list<char> par: arcos)
    {
        from=par.front();
        to=par.back();
        cout<<"(";
        for (char e : par)
        {
            cout<<e<<" ";
            
        }
        peso=ng.getPesoArco(from,to);
        cout<<")= "<<peso<<endl;
    }
    cout<<endl;
    conexas=ng.getCompConexas();
    for (list<char> par: conexas)
    {
        cout<<"Comp";
        for (char e : par)
        {
            cout<<e<<" ";
            
        }
        cout<<endl;
    }
    cout<<endl;

    // Probando el getPuentes

    cout<<"[";
    for(const auto &n : g.getPuentes()){
        cout<<"[";
        for(const auto &m : n){
            cout<< m << ",";
        }
        cout<<"]";
    }
    cout<<"]";

    return 0;
}
