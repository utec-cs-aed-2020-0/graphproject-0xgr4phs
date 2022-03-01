#ifndef PRIM_H
#define PRIM_H

#include "../DirectedGraph.h"
#include "../UndirectedGraph.h"
#include"data_estructures/ds.h"
#include<utility>
#include<vector>
#include<algorithm>
#include<stack>

using namespace std;

/**
 * Funcion que emplea el algoritmo de Prim para retornar un grafo (DIRIGIDO) con el arbol de minima expansion
 * Se utiliza una pila para regresar a vertices previamente visitados
 * Si el disjoint set se unifica, se retorna previamente
 * @tparam TV Tipo de dato para la informacion del vertice
 * @tparam TE Tipo de dato para el peso de la arista
 * @param grafo grafo a ser evaluado
 * @param inicio vertice inicial para el algoritmo
 * @return Grafo que representa el arbol de minima expansion
 */
template<typename TV, typename TE>
DirectedGraph<TV, TE> prim(DirectedGraph<TV, TE> grafo, string inicio){
    DirectedGraph<TV, TE> retorno;
    DisjointSetGrafoDirigido gSet(grafo);
    stack<Vertex<TV, TE>*> pilaVertice;
    pilaVertice.push(grafo.vertexes[inicio]);
    for(const pair<string,Vertex<TV, TE>*>& vertice: grafo.vertexes){
        retorno.insertVertex(vertice.first, vertice.second->data);
    }

    while(!pilaVertice.empty()){
        sort(pilaVertice.top()->edges.begin(), pilaVertice.top()->edges.end(), [](Edge<TV, TE>* a, Edge<TV, TE>* b){return a->weight<b->weight;});
        std::list<Edge<TV, TE>*>& edgesAlias = pilaVertice.top()->edges;
        int edgesLength = edgesAlias.size();
        for(int i = 0; i<edgesLength; i++){
            if(gSet.Union(edgesAlias.front()->vertexes[0]->id, edgesAlias.front()->vertexes[1]->id)){
                retorno.createEdge(edgesAlias.front()->vertexes[0]->id, edgesAlias.front()->vertexes[1]->id);
                pilaVertice.push(edgesAlias.front()->vertexes[1]);
                break;
            }
            edgesAlias.pop_front();
        }
        if(edgesAlias.size() == 0) {
            pilaVertice.pop();
        }
        if(gSet.getSets()==1){
            return retorno;
        }
    }

    return retorno;
}

/**
 * Funcion que emplea el algoritmo de Prim para retornar un grafo (NO DIRIGIDO) con el arbol de minima expansion
 * Se utiliza una pila para regresar a vertices previamente visitados
 * Si el disjoint set se unifica, se retorna previamente
 * @tparam TV Tipo de dato para la informacion del vertice
 * @tparam TE Tipo de dato para el peso de la arista
 * @param grafo grafo a ser evaluado
 * @param inicio vertice inicial para el algoritmo
 * @return Grafo que representa el arbol de minima expansion
 */
template<typename TV, typename TE>
UnDirectedGraph<TV, TE> prim(UnDirectedGraph<TV, TE> grafo, string inicio){
    UnDirectedGraph<TV, TE> retorno;
    DisjointSetGrafoNoDirigido gSet(grafo);
    stack<Vertex<TV, TE>*> pilaVertice;
    pilaVertice.push(grafo.vertexes[inicio]);
    for(const pair<string,Vertex<TV, TE>*>& vertice: grafo.vertexes){
        retorno.insertVertex(vertice.first, vertice.second->data);
    }

    while(!pilaVertice.empty()){
        sort(pilaVertice.top()->edges.begin(), pilaVertice.top()->edges.end(), [](Edge<TV, TE>* a, Edge<TV, TE>* b){return a->weight<b->weight;});
        std::list<Edge<TV, TE>*>& edgesAlias = pilaVertice.top()->edges;
        int edgesLength = edgesAlias.size();
        for(int i = 0; i<edgesLength; i++){
            if(gSet.Union(edgesAlias.front()->vertexes[0]->id, edgesAlias.front()->vertexes[1]->id)){
                retorno.createEdge(edgesAlias.front()->vertexes[0]->id, edgesAlias.front()->vertexes[1]->id);
                pilaVertice.push(edgesAlias.front()->vertexes[1]);
                break;
            }
            edgesAlias.pop_front();
        }
        if(edgesAlias.size() == 0) {
            pilaVertice.pop();
        }
        if(gSet.getSets()==1){
            return retorno;
        }
    }

    return retorno;
}

#endif