#ifndef BELLMAN_FORD_H
#define BELLMAN_FORD_H

#include "../DirectedGraph.h"
#include "../UndirectedGraph.h"
#include <unordered_map>
#include<string>
#include<climits>
#include<utility>

using namespace std;

/**
 * Funcion de algoritmo Bellman-Ford en grafo Dirigido
 * El algoritmo de Bellman-Ford se enfoca en hallar minimas distancias desde un nexo tomando en cuenta pesos positivos y negativos
 * Es de carácter similar al algoritmo Dijkstra
 * Su complejidad en tiempo es de O(|E|*|V|)
 * El proceso de relajacion consiste en tomar una arista y evaluar si existe un menor peso de llegado al que previamente el vertice objetivo tiene
 * Se realiza la relajacion en todos los vertices por la cantidad total exceptuando al nexo (|V|-1)
 * @tparam TV Tipo de variable para la informacion que almacena el vertice
 * @tparam TE Tipo de variable para la informacion que almacena la arista
 * @param grafo El grafo objetivo para el cual se realizara el algoritmo
 * @param nodoInicio El nodo el cual sera el punto de partida para el calculo de distancias
 * @return Un grafo arbol con solo aquellos vertices que generan las menores distancias
 */
template<typename TV, typename TE>
DirectedGraph<TV, TE> bellman_ford(const DirectedGraph<TV, TE> &grafo, const string &nodoInicio){
    DirectedGraph<TV,TE> retorno;

    unordered_map<string, pair<int, string>> distanciaPadre;
    for(const pair<string, Vertex<TV, TE>*>& vertice: grafo.vertexes){
        if(vertice.first == nodoInicio) distanciaPadre[vertice.first] = {INT_MAX, string()};
        else distanciaPadre[vertice.first] = {INT_MAX, string()};
        retorno.insertVertex(vertice.first, vertice.second->data);
    }

    for(int i = 0; i<grafo.V-1; i++){
        for(const pair<string, Vertex<TV, TE>*>& vertice: grafo.vertexes){
            for(const Edge<TV, TE>*& arista: vertice.second->edges){
                pair<int, string> inicio = distanciaPadre[arista->vertexes[0]->id];
                pair<int, string> &llegada= distanciaPadre[arista->vertexes[1]->id];
                if(inicio.first == llegada.first && inicio.first==INT_MAX){
                    continue;
                }
                else if(llegada.first > inicio.first+arista->weight){
                    llegada.first = inicio.first+arista->weight;
                    llegada.second = inicio.second;
                }
            }
        }
    }

    for(const pair<string, pair<int, string>>& entrada: distanciaPadre){
        retorno.createEdge(entrada.second.second,entrada.first);
    }
    return retorno;
}

/**
 * Funcion de algoritmo Bellman-Ford en grafo NO-Dirigido
 * El algoritmo de Bellman-Ford se enfoca en hallar minimas distancias desde un nexo tomando en cuenta pesos positivos y negativos
 * Es de carácter similar al algoritmo Dijkstra
 * Su complejidad en tiempo es de O(|E|*|V|)
 * El proceso de relajacion consiste en tomar una arista y evaluar si existe un menor peso de llegado al que previamente el vertice objetivo tiene
 * Se realiza la relajacion en todos los vertices por la cantidad total exceptuando al nexo (|V|-1)
 * @tparam TV Tipo de variable para la informacion que almacena el vertice
 * @tparam TE Tipo de variable para la informacion que almacena la arista
 * @param grafo El grafo objetivo para el cual se realizara el algoritmo
 * @param nodoInicio El nodo el cual sera el punto de partida para el calculo de distancias
 * @return Un grafo arbol con solo aquellos vertices que generan las menores distancias
 */
template<typename TV, typename TE>
UnDirectedGraph<TV,TE> bellman_ford(const UnDirectedGraph<TV, TE> &grafo, const string &nodoInicio){
    UnDirectedGraph<TV, TE> retorno;
    unordered_map<string, pair<int, string>> distanciaPadre;

    for(const pair<string, Vertex<TV, TE>*>& vertice: grafo.vertexes){
        if(vertice.first == nodoInicio) distanciaPadre[vertice.first] = {INT_MAX, string()};
        else distanciaPadre[vertice.first] = {INT_MAX, string()};
        retorno.insertVertex(vertice.first, vertice.second->data);
    }

    for(int i = 0; i<grafo.V-1; i++){
        for(const pair<string, Vertex<TV, TE>*>& vertice: grafo.vertexes){
            for(const Edge<TV, TE>*& arista: vertice.second->edges){
                pair<int, string> inicio = distanciaPadre[arista->vertexes[0]->id];
                pair<int, string> &llegada= distanciaPadre[arista->vertexes[1]->id];
                if(inicio.first == llegada.first && inicio.first==INT_MAX){
                    continue;
                }
                else if(llegada.first > inicio.first+arista->weight){
                    llegada.first = inicio.first+arista->weight;
                    llegada.second = inicio.second;
                }
            }
        }
    }

    for(const pair<string, pair<int, string>>& entrada: distanciaPadre){
        retorno.createEdge(entrada.second.second,entrada.first);
    }
    return retorno;
}

#endif