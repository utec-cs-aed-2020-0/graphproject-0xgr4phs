#ifndef KRUSKAL_H
#define KRUSKAL_H

#include "../DirectedGraph.h"
#include "../UndirectedGraph.h"
#include"data_estructures/ds.h"
#include<utility>
#include<vector>
#include<algorithm>

using namespace std;

/**
 * Funcion para comparar aristas con respecto al peso
 */
template<typename TV, typename TE>
bool compEdge(Edge<TV, TE>*a, Edge<TV, TE>*b){
    return (a->weight<b->weight);
}

/**
 * Algoritmo Kruskal que retorna un grafo (DIRIGIDO) con el arbol de minima expansion
 * Se organizan las aristas desde su peso y se verifica que en el disjoint set no existan ciclos
 * @tparam TV tipo de dato que almacena el vertice
 * @tparam TE tipo de dato que almacena el peso de arista
 * @param grafo Grafo a ser evaluado
 * @return grafo que representa el arbol de minima expansion
 */
template<typename TV, typename TE>
DirectedGraph<TV, TE> kruskal(const DirectedGraph<TV, TE>& grafo){
    DirectedGraph<TV, TE> retorno;
    DisjointSetGrafo gSet(grafo);
    vector<Edge<TV,TE>*> aristas(grafo.E);
    int i = 0;
    for(const pair<string,Vertex<TV, TE>*>& vertice: grafo.vertexes){
        for(const Edge<TV, TE>*& arista: vertice.second->edges){
            aristas[i++] = arista;
        }
        retorno.insertVertex(vertice.first, vertice.second->data);
    }
    sort(aristas.begin(), aristas.end(), compEdge);

    for (i = 0;  i<grafo.E ; i++) {
        //aristas[i]->vertexes[0]
        //aristas[i]->vertexes[1]
        if(gSet.Union(aristas[i]->vertexes[0]->id, aristas[i]->vertexes[1]->id)){
            retorno.createEdge(aristas[i]->vertexes[0]->id, aristas[i]->vertexes[1]->id, aristas[i]->weight);
        }
        if(!gSet.getSets()) break;
    }

    return retorno;
}

/**
 * Algoritmo Kruskal que retorna un grafo (NO DIRIGIDO) con el arbol de minima expansion
 * Se organizan las aristas desde su peso y se verifica que en el disjoint set no existan ciclos
 * @tparam TV tipo de dato que almacena el vertice
 * @tparam TE tipo de dato que almacena el peso de arista
 * @param grafo Grafo a ser evaluado
 * @return grafo que representa el arbol de minima expansion
 */
template<typename TV, typename TE>
UnDirectedGraph<TV, TE> kruskal(const UnDirectedGraph<TV, TE>& grafo){
    UnDirectedGraph<TV, TE> retorno;
    DisjointSetGrafo gSet(grafo);
    vector<Edge<TV,TE>*> aristas(grafo.E);
    int i = 0;
    for(const pair<string,Vertex<TV, TE>*>& vertice: grafo.vertexes){
        for(const Edge<TV, TE>*& arista: vertice.second->edges){
            aristas[i++] = arista;
        }
        retorno.insertVertex(vertice.first, vertice.second->data);
    }
    sort(aristas.begin(), aristas.end(), compEdge);

    for (i = 0;  i<grafo.E ; i++) {
        //aristas[i]->vertexes[0]
        //aristas[i]->vertexes[1]
        if(gSet.Union(aristas[i]->vertexes[0]->id, aristas[i]->vertexes[1]->id)){
            retorno.createEdge(aristas[i]->vertexes[0]->id, aristas[i]->vertexes[1]->id, aristas[i]->weight);
        }
        if(!gSet.getSets()) break;
    }

    return retorno;
}

#endif