#ifndef BELLMAN_FORD_H
#define BELLMAN_FORD_H

#include "../DirectedGraph.h"
#include "../UndirectedGraph.h"
#include <unordered_map>
#include<string>

using namespace std;

/**
 * El algoritmo de Bellman-Ford se enfoca en hallar minimas distancias desde un nexo tomando en cuenta pesos positivos y negativos
 * Es de carácter similar al algoritmo Dijkstra
 * Su complejidad en tiempo es de O(|E|*|V|)
 * @tparam TV Tipo de variable para la informacion que almacena el vertice
 * @tparam TE Tipo de variable para la informacion que almacena la arista
 * @param grafo El grafo objetivo para el cual se realizara el algoritmo
 * @param nodoInicio El nodo el cual sera el punto de partida para el calculo de distancias
 * @return Un grafo arbol con solo aquellos vertices que generan las menores distancias
 */
template<typename TV, typename TE>
DirectedGraph<TV, TE> bellman_ford(const DirectedGraph<TV, TE> &grafo, const string &nodoInicio){
    unordered_map<string, int> distancias;
    for(int i = 0; i<grafo.V-1; i++){
        int nRelajaciones = 0;
        for(int j = 0; j<grafo.E; j++){

        }
        if(!nRelajaciones) break;
    }
}

#endif