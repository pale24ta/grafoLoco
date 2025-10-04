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

    GrafoNoDirigido<char> ng,ng2;
    Grafo<char> g,g2;

    char v,w;
    int i=0;
    //float coste=9;
    while (cin>> v >> w)
    {
        i++;
        g.agregarArco(v,w,i);
        ng.agregarArco(v,w,i);
        //ng.agregarArco(w,v,i);
        //g2.agregarArco(v,w,i);
    }
    //g.agregarVertice('W');
    //g2.agregarVertice('Z');
    Grafo<int> gMap=g.getMapGrafo();
    GrafoNoDirigido<int> ngMap=ng.getMapGrafo();

    cout<<"VERTICES "<<endl;
    cout<<"Dirigido: ";
    list<char> vertices=g.getVertices();
    for (auto &&i : vertices)
    {
        cout<<i<<" ";
    }
    cout<<endl;
    cout<<"Mapa: ";
    list<int> verticesMap=gMap.getVertices();
    for (auto &&i : verticesMap)
    {
        cout<<i<<" ";
    }
    cout<<endl;

    cout<<"NO Dirigido: ";
    vertices=ng.getVertices();
    for (auto &&i : vertices)
    {
        cout<<i<<" ";
    }
    cout<<endl;

    cout<<"Mapa: ";
    verticesMap=ngMap.getVertices();
    for (auto &&i : verticesMap)
    {
        cout<<i<<" ";
    }
    cout<<endl;

    cout<<"ARCOS"<<endl;
    cout<<"Dirigidos: "<<g.getMArcos()<<" arcos"<<endl;
    list<list<char>> arcos;
    list<list<int>> arcosMap;

    arcos=g.getArcos();
    for (auto &&i : arcos)
    {
        float v=i.front();
        float w=i.back();
        cout<<"( ";
        for (auto &&j : i)
        {
            cout<<j<<" ";
        }
        cout<<") = "<<g.getPesoArco(v,w)<<endl;
    }
    cout<<"Mapeado: "<<gMap.getMArcos()<<" arcos"<<endl;
    arcosMap=gMap.getArcos();
    for (auto &&i : arcosMap)
    {
        float v=i.front();
        float w=i.back();
        cout<<"( ";
        for (auto &&j : i)
        {
            cout<<j<<" ";
        }
        cout<<") = "<<gMap.getPesoArco(v,w)<<endl;
    }

    cout<<"No Dirigidos"<<ng.getMArcos()<<" arcos"<<endl;
    arcos=ng.getArcos();
    for (auto &&i : arcos)
    {
        float v=i.front();
        float w=i.back();
        cout<<"( ";
        for (auto &&j : i)
        {
            cout<<j<<" ";
        }
        cout<<") = "<<g.getPesoArco(v,w)<<endl;
    }
    cout<<"Mapeado:"<<ngMap.getMArcos()<<" arcos"<<endl;
    arcosMap=ngMap.getArcos();
    for (auto &&i : arcosMap)
    {
        float v=i.front();
        float w=i.back();
        cout<<"( ";
        for (auto &&j : i)
        {
            cout<<j<<" ";
        }
        cout<<") = "<<ngMap.getPesoArco(v,w)<<endl;
    }
    return 0;
}
