#ifndef PRIM_H
#define PRIM_H

#include "../DirectedGraph.h"
#include "../UndirectedGraph.h"

using namespace std;

template<typename TV, typename TE>
DirectedGraph<TV, TE> prim(const DirectedGraph<TV, TE>& grafo, string inicio){
    DirectedGraph<TV, TE> retorno;
    for(const pair<string,Vertex<TV, TE>*>& vertice: grafo.vertexes){
        retorno.insertVertex(vertice.first, vertice.second->data);
    }


    return retorno;
}

#endif