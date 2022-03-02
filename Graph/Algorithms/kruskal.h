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
 * Algoritmo Kruskal que retorna un grafo (NO DIRIGIDO) con el arbol de minima expansion
 * Se organizan las aristas desde su peso y se verifica que en el disjoint set no existan ciclos
 * @tparam TV tipo de dato que almacena el vertice
 * @tparam TE tipo de dato que almacena el peso de arista
 * @param grafo Grafo a ser evaluado
 * @return grafo que representa el arbol de minima expansion
 */
template<typename TV, typename TE>
UnDirectedGraph<TV, TE> kruskal(UnDirectedGraph<TV, TE> grafo){
    UnDirectedGraph<TV, TE> retorno;
    DisjointSetGrafoNoDirigido gSet(grafo);
    vector<Edge<TV,TE>*> aristas(grafo.E*2);
    int i = 0;
    for(auto vertice = grafo.vertexes.begin(); vertice != grafo.vertexes.end(); vertice++){
        for(auto ari = vertice->second->edges.begin(); ari != vertice->second->edges.end(); ari++){
            aristas[i] = *ari;
            i++;
        }
        retorno.insertVertex(vertice->first, vertice->second->data);
    }
    sort(aristas.begin(), aristas.end(), [](Edge<TV, TE>* a, Edge<TV, TE>* b){return a->weight<b->weight;});

    for (i = 0;  i<aristas.size() ; i++) {
        if(gSet.Union(aristas[i]->vertexes[0]->id, aristas[i]->vertexes[1]->id)){
            retorno.createEdge(aristas[i]->vertexes[0]->id, aristas[i]->vertexes[1]->id, aristas[i]->weight);
        }
        if(gSet.getSets()==1) break;
    }

    return retorno;
}

#endif
