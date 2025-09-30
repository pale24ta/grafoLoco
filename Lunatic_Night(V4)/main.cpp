#include<iostream>
#include<list>
#include<unordered_map>
#include "grafoNoDirigido.hpp"
#include "grafoDirigido.hpp"
#include <fstream>


using namespace std;


int main(){
    // UndirectedGraph<char> grafoNuevo;
    Graph<char> nuevoGrafo;
    // ifstream in("in.txt");
    char a,b;

    while(cin >> a >> b)
        nuevoGrafo.addArco(a,b,0);



    cout<<"Antes =";
    // Mostrar arcos antes del invertir
    cout<<'[';
    for(const auto&n : nuevoGrafo.getArcos()){
        cout<<'[';
        for(const auto&m : n){
            cout<<m<<",";
        }
        cout<<"],";
    }
    cout<<"]"<<endl;
    
    nuevoGrafo.getReverse();

    
    cout<<"Despues =";
    // Mostrar arcos antes del invertir
    cout<<'[';
    for(const auto&n : nuevoGrafo.getArcos()){
        cout<<'[';
        for(const auto&m : n){
            cout<<m<<",";
        }
        cout<<"],";
    }
    cout<<"]"<<endl;

    // // mapeamos el grafo

    // UndirectedGraph<int> mapeado = grafoNuevo.getMapGrafo();
    // map<int,char> dic = grafoNuevo.getMapVertices();

    // cout<<"[";
    // for(const auto&n : puentesGrafo(mapeado)){
    //     cout<<"[";
    //     for(const auto& m : n){
    //         cout<<dic[m] << ",";
    //     }
    //     cout<<"],";
    // }
    // cout<<"]";
    
    return 0;
}



bool grafoEsConexo(UndirectedGraph<int> &g){

    bool respuesta = true;
    bool visitados[g.orden()];

    for(int i = 0 ; i < g.orden() ; i++){
        visitados[i] = false;
    }

    // hacemos el recorrido dfs

    dfs(g,g.getFuente(),visitados);

    // revisamos los visitados,
    // SI alguno de ellos no ha sido visitado por los recorrido, implica que no es conexo

    for(int i = 0 ; i < g.orden() && respuesta ; i++){
        respuesta = visitados[i];
    }

    return respuesta;
}
list<list<int> > puentesGrafo(UndirectedGraph<int> &g){

    // Vamos a resolver este ejercicio por el camino largo
    int v,w;
    list<list<int> > arcosGrafo = g.getArcos(); // Obtenemos la lista de los arcos disponibles
    list<list<int> > puentes;
    // bool res = true;

    while(!arcosGrafo.empty()){
        v = arcosGrafo.front().front();
        w = arcosGrafo.front().back();
        
        // Eliminamos esos arcos

        g.eliminarArco(v,w);
        // probamos si, eliminando esos grafos sigue siendo conexo
        
        if(!grafoEsConexo(g)){
            puentes.push_front(list<int>({v,w}));   // Guardamos esas vertices
        }
        g.addArco(v,w,0); // Restauramos ese arco de nuevo en el grafo
        arcosGrafo.pop_front();
    }

    return puentes;
}
void dfs(UndirectedGraph<int> &g,int v, bool visitados[]){

    if(!visitados[v]){
        visitados[v] = true;

        list<int> vecinos = g.getVecinos(v);
        while(!vecinos.empty()){
            dfs(g,vecinos.front(),visitados);
            vecinos.pop_front();
        }
    }
}
