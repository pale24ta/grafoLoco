#include "funciones_grafo.hpp"

std::list<int> BFS(Graph<int> g)
{
    bool visitados[g.orden()]; //vector de nodos visitados
    std::queue<int> c;    // Contenedor de recorrer el recorrido
    std::list<int> recorrido,sucesores;  // listas
    int i,v,m;


    // begin

    // Llenamos el vector visitados de falso
    i = 0;
    while(i < g.orden()){
        visitados[i] = false;
        i++;
    }

    // Empezamos a partir del nodo dado por grafo g
    // estamos parado en el primer nodo, asi que

    visitados[g.getFuente()-1]  = true;     // El primero nodo del grafo visitado
    c.push(g.getFuente());  // Encolamos el nodo Fuente

    // Mientras la cola no este vacia, trabaja con el grafo
    while(!c.empty()){
        v = c.front();  // obtenemos el fuente de la cola c
        c.pop();   // Desencolamos

        recorrido.push_back(v); // insertamos en la lista, el nodo ya recorrido
        sucesores = g.sucesores(v); // obtenemos la lista de sucesores de v, es decir, los nodos que estan enlazados al vertice v

        while(!sucesores.empty()){
            m = sucesores.front();  // tomamos el frente de la lista
            
            // si ese sucesor no ha sido visitado anteriormente
            if(!visitados[m-1]){
                visitados[m-1] = true;  // Lo marcamos como visitado
                c.push(m);
            }

            sucesores.pop_front();    // eliminamo el sucesor de la lista de sucesores
        }
    }
}

void DFS(Graph<int> g, int fuente, std::list<int> &recorrido, bool *visitados)
{
    std::list<int> sucesores;
    if(!visitados[fuente-1]){
        int i,j,k;

        // Estamos en el recorrido del nodo actual, asi que
        visitados[fuente-1] = true; // se tacha como nodo recorrido
        recorrido.push_back(fuente);    // inserta la fuente en la lista de recorridos

        // tomamos los sucesores de la fuente
        sucesores = g.sucesores(fuente);

        while(!sucesores.empty()){
            DFS(g,sucesores.front(),recorrido,visitados);   // Recursion al primer elemento de los sucesores del siguiente sucesor
            sucesores.pop_front();  // Eliminamos ese sucesor
        }   
    }
}

std::list<int> DFS(Graph<int> &g)
{
    std::list<int> recorrido;
    bool visitados[g.orden()];

    for(int i = 0; i < g.orden(); i++)
        visitados[i] = false;   // Llenamos el vector de falsos

    DFS(g,g.getFuente(),recorrido,visitados); // Opera la funcion recursiva

    return recorrido;
}
