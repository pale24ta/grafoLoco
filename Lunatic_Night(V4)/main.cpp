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


    for (auto &&i : vertices)
    {
        cout<<"Recorrido DFC desde "<<i<<": ";
        list<char> recorrdio =g.DFS(i);
        for (auto &&j : recorrdio)
        {
            cout<<j<<" ";
        }
        cout<<endl;

        cout<<"Recorrido BFC desde "<<i<<": ";
        recorrdio =g.BFS(i);
        for (auto &&j : recorrdio)
        {
            cout<<j<<" ";
        }
        cout<<endl;
        cout<<endl;
    }


    cout<<"NO Dirigido: "<<ng.getPeso();
    vertices=ng.getVertices();
    for (auto &&i : vertices)
    {
        cout<<i<<" ";
    }
    cout<<endl;

    for (auto &&i : vertices)
    {
        cout<<"Recorrido DFC desde "<<i<<": ";
        list<char> recorrdio =ng.DFS(i);
        for (auto &&j : recorrdio)
        {
            cout<<j<<" ";
        }
        cout<<endl;

        cout<<"Recorrido BFC desde "<<i<<": ";
        recorrdio =ng.BFS(i);
        for (auto &&j : recorrdio)
        {
            cout<<j<<" ";
        }

        cout<<endl;
        cout<<endl;
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

    for(list<char> pares : g.getArcos()){
        char x = pares.front();
        char y = pares.back();
        cout<<"(";
        for(char i : pares){
            cout<<i<<" ";
        }
        cout<<")";

        // su peso
        cout<<"="<<g.getPesoArco(x,y)<<endl;
    }

    cout<<"Total ="<<g.getPeso()<<endl;


    // No dirigido
    
    for(list<char> pares : ng.getArcos()){
        char x = pares.front();
        char y = pares.back();
        cout<<"(";
        for(char i : pares){
            cout<<i<<" ";
        }
        cout<<")";

        // su peso
        cout<<"="<<ng.getPesoArco(x,y)<<endl;
    }

    cout<<"Total ="<<ng.getPeso()<<endl;



    return 0;
}
