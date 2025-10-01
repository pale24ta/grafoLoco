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

    GrafoNoDirigido<char> grafoActual;

    char a,b,inicio,fin,intermedio;

    ifstream in("in.txt");

    in >> inicio >> fin >> intermedio;
    while(in >> a >> b){
        grafoActual.agregarArco(a,b,0);
    }

    // Probando dfs
    cout<<"BFS = [";
    for(const auto&n : grafoActual.BFS()){
        cout<<n<<",";
    }
    cout<<"]\n";

    cout<<"DFS = [";
    for(const auto &n : grafoActual.DFS()){
        cout<<n<<",";
    }
    cout<<"]\n";
    return 0;
}


list<int> caminoMasCortoIntermedio(GrafoNoDirigido<int> &g, int a, int b, int intermedio){
    // Usaremos el bfs

    list<int> vecinos;
    queue<int> recorridoA,recorridoB;
    list<int> resultado;
    bool visitados[g.getNVertices()];
    // int distancias[g.getNVertices()];
    int previos[g.getNVertices()];

    int v,w;
    // int distanciaActual = 0;


    bool intermedioEncontrado = false;
    bool finalEncontrado =false;
    // inicializamos los booleanos y distancias

    for(int i = 0; i < g.getNVertices() ; i++){
        visitados[i] = false;
        // distancias[i] = 0;
        previos[i] = -1;
    }

    // Si alguna de las vertices no existe, devuelve la lista vacia
    if(!g.existeVertice(a) || !g.existeVertice(b) || !g.existeVertice(intermedio) || (a == b)) return resultado;
    
    // inciamos con el primero
    visitados[a] = true;
    // distancias[a] = 0;
    recorridoA.push(a);



    while((!recorridoA.empty() || !recorridoB.empty()) && !finalEncontrado){

        if(intermedioEncontrado){
            v = recorridoB.front();
            recorridoB.pop();
        }else{
            v = recorridoA.front();
            recorridoA.pop();
        }
        // distanciaActual += distancias[v];    // la distancia actual se suma con la distancia de ese vector registrada
        // anteriormente

        // Revisamos los vecinos
        vecinos = g.getVecinos(v);
        while(!vecinos.empty()){
            w = vecinos.front();
            vecinos.pop_front();

            if(!visitados[w]){

                // Revisamos si hay un vecino disponible
                if(w == intermedio){
                    intermedioEncontrado = true;
                }
                if(intermedioEncontrado && w == b){
                    finalEncontrado = true;
                }

                visitados[w] = true;

                if(intermedioEncontrado){
                    recorridoB.push(w);
                }else{
                    recorridoA.push(w);
                }
                previos[w] = v;
            }
        }
    }


    // iteramos en la lista de los previos

    resultado.push_front(b);
    int i = b;
    while(i != a){
        resultado.push_front(previos[i]);
        i = previos[i];
    }
    // resultado.push_back(a);

    return resultado;
}
