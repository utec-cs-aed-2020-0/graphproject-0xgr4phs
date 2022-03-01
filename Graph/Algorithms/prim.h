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

template<typename TV, typename TE>
bool compEdge(Edge<TV, TE>*a, Edge<TV, TE>*b){
    return (a->weight<b->weight);
}

template<typename TV, typename TE>
DirectedGraph<TV, TE> prim(DirectedGraph<TV, TE> grafo, string inicio){
    DirectedGraph<TV, TE> retorno;
    DisjointSetGrafo gSet(grafo);
    stack<Vertex<TV, TE>*> pilaVertice;
    pilaVertice.push(grafo.vertexes[inicio]);
    for(const pair<string,Vertex<TV, TE>*>& vertice: grafo.vertexes){
        retorno.insertVertex(vertice.first, vertice.second->data);
    }

    while(!pilaVertice.empty()){
        sort(pilaVertice.top()->edges.begin(), pilaVertice.top()->edges.end(), compEdge);
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
    }

    return retorno;
}

template<typename TV, typename TE>
UnDirectedGraph<TV, TE> prim(const UnDirectedGraph<TV, TE>& grafo, string inicio){
    UnDirectedGraph<TV, TE> retorno;
    DisjointSetGrafo gSet(grafo);
    stack<Vertex<TV, TE>*> pilaVertice;
    pilaVertice.push(grafo.vertexes[inicio]);
    for(const pair<string,Vertex<TV, TE>*>& vertice: grafo.vertexes){
        retorno.insertVertex(vertice.first, vertice.second->data);
    }

    while(!pilaVertice.empty()){
        sort(pilaVertice.top()->edges.begin(), pilaVertice.top()->edges.end(), compEdge);
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