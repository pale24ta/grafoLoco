#include<iostream>
#include<list>
#include<unordered_map>
#include <utility>
#include "grafoNoDirigido.hpp"
#include "grafoDirigido.hpp"
#include <fstream>


using namespace std;

int main(){
    Graph<char> g;

    UndirectedGraph<char> ng;
    char v,w;
    int i=0;
    while (cin>> v >> w)
    {
        i++;
        g.agregarArco(v,w,i);
        ng.agregarArco(v,w,i);
        
    }

    cout<<"Grado de  salida de a: "<<g.getGradoSalida('A')<<endl;
    cout<<"Grado de  entrada de a: "<<g.getGradoEntrada('A')<<endl;
    cout<<"Tiene "<<g.getNVertices()<<" Vertives y "<<g.getMArcos()<<" Arcos."<<endl;

    /*Graph<char> t(g);
    if(t.getMArcos()==g.getMArcos())
        cout<<"merequetengue"<<endl;*/
    //sin mapear
    cout<<"Vertices: ";
    list<char> vertices=g.getVertices();
    for (char e : vertices)
    {
        cout<< e << ", ";
    }
    cout<<endl;

    //mapeado
    Graph<int> gMap=g.getMapGrafo();
    list<int> mapa=gMap.getVertices();
    cout<<"Mapa: ";
    for (int e : mapa)
    {
        cout<< e << ", ";
    }
    cout<<endl;
    //Arcos sin mapear
    list<list<char>> arcos=g.getArcos();
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

    //arcos mapeados
    list<list<int>> arcosMap=gMap.getArcos();
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

    //TEST Grafo no dirigido
    vertices=ng.getVertices();
    for (char e : vertices)
    {
        cout<< e << ", ";
    }
    cout<<endl;

    return 0;
}
