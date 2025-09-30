#include<iostream>
#include<list>
#include<unordered_map>
#include "grafoNoDirigido.hpp"
#include "grafoDirigido.hpp"
#include <fstream>


using namespace std;


int main(){
    GrafoNoDirigido<int> grafoNuevo;

    int a,b;

    while(cin >> a >> b)
        grafoNuevo.agregarArco(a,b,0);

    // mapeamos el grafo
    list<int> res = grafoNuevo.BFS(grafoNuevo);
    if(grafoNuevo.existeArco(1,4))
        cout<<"\nsi existe\n";
    else
        cout<<"\nno existe\n";

    cout<<endl;
    for( int n: res)
        cout<<n<<" ";
    cout<<endl;
    cout<<"\nlista de vertices:\n";
    list<int> vertices =grafoNuevo.getVertices();
    for( int n: vertices)
        cout<<n<<" ";
    cout<<endl;

    list<list<int>> arcos = grafoNuevo.getArcos();
    cout<<"\nImprimiendo arcos:\n";
    for(const auto& listaInterna: arcos){
        for(auto it = listaInterna.begin() ; it!= listaInterna.end(); it++){
            cout<<"["<<*it<<"] ";
            it++;
            cout<<"["<<*it<<"] ";
        }
        cout<<endl;
    }
    cout<<"\nEliminando el arco 4-5 ahora el grafo queda disconexo\n";
    grafoNuevo.eliminarArco(3,4);
    list<int> nuevoRec = grafoNuevo.BFS(grafoNuevo);
    for( int n: nuevoRec)
        cout<<n<<" ";
    cout<<endl;

    return 0;
}




