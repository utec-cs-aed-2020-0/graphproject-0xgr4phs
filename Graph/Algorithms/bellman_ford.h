#ifndef BELLMAN_FORD_H
#define BELLMAN_FORD_H

#include "../DirectedGraph.h"
#include "../UndirectedGraph.h"
#include <unordered_map>
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
DirectedGraph<TV, TE> bellman_ford( DirectedGraph<TV, TE> grafo, const string &nodoInicio){
    DirectedGraph<TV,TE> retorno;

    // Nodo actual, <<distancia, peso arista>, padre>
    //unordered_map<string, pair<TE, string>> distanciaPadre;
    unordered_map<string, pair<pair<TE,TE>, string>> distanciaPadre;
    for(auto vertice: grafo.vertexes){
        if(vertice.first == nodoInicio) distanciaPadre[vertice.first] = {{0,0}, string()};
        else distanciaPadre[vertice.first] = {{INT_MAX,0}, string()};

        retorno.insertVertex(vertice.first, vertice.second->data);
    }

    for(int i = 0; i<grafo.V-1; i++){
        for(auto vertice: grafo.vertexes){
            for(auto arista: vertice.second->edges){
                pair<pair<TE,TE>, string> inicio = distanciaPadre[arista->vertexes[0]->id];
                pair<pair<TE,TE>, string> &llegada= distanciaPadre[arista->vertexes[1]->id];
                if(inicio.first.first == llegada.first.first && inicio.first.first==INT_MAX){
                    continue;
                }
                else if(llegada.first.first > inicio.first.first+arista->weight){
                    llegada.first.first = inicio.first.first+arista->weight;
                    llegada.first.second = arista->weight;
                    llegada.second = arista->vertexes[0]->id;
                }
            }
        }
    }

    for(auto entrada: distanciaPadre){
        retorno.createEdge(entrada.second.second,entrada.first, entrada.second.first.second);
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
UnDirectedGraph<TV,TE> bellman_ford(UnDirectedGraph<TV, TE> grafo, const string &nodoInicio){
    UnDirectedGraph<TV, TE> retorno;
    // Nodo actual, <<distancia, peso arista>, padre>
    //unordered_map<string, pair<TE, string>> distanciaPadre;
    unordered_map<string, pair<pair<TE,TE>, string>> distanciaPadre;
    for(auto vertice: grafo.vertexes){
        if(vertice.first == nodoInicio) distanciaPadre[vertice.first] = {{0,0}, string()};
        else distanciaPadre[vertice.first] = {{INT_MAX,0}, string()};

        retorno.insertVertex(vertice.first, vertice.second->data);
    }

    for(int i = 0; i<grafo.V-1; i++){
        for(auto vertice: grafo.vertexes){
            for(auto arista: vertice.second->edges){
                pair<pair<TE,TE>, string> inicio = distanciaPadre[arista->vertexes[0]->id];
                pair<pair<TE,TE>, string> &llegada= distanciaPadre[arista->vertexes[1]->id];
                if(inicio.first.first == llegada.first.first && inicio.first.first==INT_MAX){
                    continue;
                }
                else if(llegada.first.first > inicio.first.first+arista->weight){
                    llegada.first.first = inicio.first.first+arista->weight;
                    llegada.first.second = arista->weight;
                    llegada.second = arista->vertexes[0]->id;
                }
            }
        }
    }

    for(auto entrada: distanciaPadre){
        retorno.createEdge(entrada.second.second,entrada.first, entrada.second.first.second);
    }
    return retorno;
}

#endif