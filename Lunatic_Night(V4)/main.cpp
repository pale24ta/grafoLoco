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
    //PRUEBA DE ARCOS Y VERTICES
////////////////////////////////////////////////////////////////////////////////////////////////
    cout<<"VERTICES "<<endl;
    cout<<"Dirigido: "<<g.getPeso();
    list<char> vertices=g.getVertices();
    for (auto &&i : vertices)
    {
        cout<<i<<" ";
    }
    cout<<endl;


    cout<<"NO Dirigido: "<<ng.getPeso();
    vertices=ng.getVertices();
    for (auto &&i : vertices)
    {
        cout<<i<<" ";
    }
    cout<<endl;

    for (auto &&i : vertices)
    {
        cout<<"Camino A -> "<<i<<endl;
        cout<<"DIRIGIDO: ";
        list<char> camino=g.getCamino('A',i);
        for (auto &&j : camino)
        {
            cout<<j<<" ";
        }
        cout<<endl;

        cout<<"NO DIRIGIDO: ";
        camino=ng.getCamino('A',i);
        for (auto &&j : camino)
        {
            cout<<j<<" ";
        }
        cout<<endl<<endl;
    }





    /*cout<<"ARCOS"<<endl;
    cout<<"Dirigidos: "<<g.getMArcos()<<" arcos y su peso es "<<g.getPeso()<<endl;
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


    cout<<"No Dirigidos"<<ng.getMArcos()<<" arcos"<<ng.getPeso()<<endl;
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
        cout<<") = "<<ng.getPesoArco(v,w)<<endl;
    }*/

////////////////////////////////////////////////////////////////////////////////////////////////////////
    //SUCESORES

    // Lista de arcos

    // dirigido



    return 0;
}
