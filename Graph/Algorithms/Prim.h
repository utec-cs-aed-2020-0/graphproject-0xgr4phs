#ifndef PRIM_H
#define PRIM_H

#include "../DirectedGraph.h"
#include "../UndirectedGraph.h"
#include"../Algorithms/data_structures/ds.h"
#include<utility>
#include<vector>
#include<algorithm>
#include<stack>

using namespace std;

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
    if(grafo.vertexes.find(inicio) == grafo.vertexes.end()) throw("Vertice no encontrado");
    DisjointSetGrafoNoDirigido gSet(grafo);
    UnDirectedGraph<TV, TE> retorno;
    stack<Vertex<TV, TE>*> pilaVertice;
    pilaVertice.push(grafo.vertexes[inicio]);
    for(const pair<string,Vertex<TV, TE>*>& vertice: grafo.vertexes){
        retorno.insertVertex(vertice.first, vertice.second->data);
        vector<Edge<TV, TE>*> aristas(vertice.second->edges.begin(), vertice.second->edges.end());
        sort(aristas.begin(), aristas.end(),[](Edge<TV, TE>* a, Edge<TV, TE>* b){return a->weight<b->weight;});
        vertice.second->edges = list<Edge<TV, TE>*>(aristas.begin(), aristas.end());
    }
    while(!pilaVertice.empty()){
        if(gSet.getSets()==1) return retorno;
        Vertex<TV, TE>* &temp = pilaVertice.top();
        int edgesLength = pilaVertice.top()->edges.size();
        auto i = temp->edges.begin();
        for(; i!= temp->edges.end(); i++){
            if(gSet.Union((*i)->vertexes[0]->id, (*i)->vertexes[1]->id)){
                retorno.createEdge((*i)->vertexes[0]->id, (*i)->vertexes[1]->id, (*i)->weight);
                pilaVertice.push((*i)->vertexes[1]);
                grafo.deleteEdge((*i)->vertexes[0]->id, (*i)->vertexes[1]->id);
                break;
            }
        }
        if(i==temp->edges.end()){
            pilaVertice.pop();
        }
    }

    return retorno;
}

#endif
