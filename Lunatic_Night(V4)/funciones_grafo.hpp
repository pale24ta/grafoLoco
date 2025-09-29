#ifndef FUNCIONESGRAFOS
#define FUNCIONESGRAFOS

#include "grafoDirigido.hpp"
#include<list>
#include<iostream>
#include<queue>

std::list<int> BFS(Graph<int> g);
void DFS(Graph<int> g, int fuente, std::list<int> &recorrido, bool *visitados);
std::list<int> DFS(Graph<int> &g);


#endif