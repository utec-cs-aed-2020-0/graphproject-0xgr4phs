#ifndef KRUSKAL_H
#define KRUSKAL_H

#include "../DirectedGraph.h"
#include "../UndirectedGraph.h"
#include <unordered_map>
#include<utility>
#include<vector>
#include<algorithm>

using namespace std;

class DisjointSetGrafo{
private:
    unordered_map<string, string> almacen;
    int sets;
public:
    template<typename TV, typename TE>
    DisjointSetGrafo(const Graph<TV, TE>*& grafo){
        sets = 0;
        for(const pair<string, Vertex<TV, TE>*>& vertice: grafo->vertexes){
            almacen[vertice.first] = {vertice.first, 0};
            sets++;
        }
    }
    string Find(string id){
        return (almacen[id]!=id?Find(almacen[id]):id);
    }
    bool Union(string id1, string id2){
        string raiz1 = Find(id1), raiz2 = Find(id2);
        if(raiz1!=raiz2){
            almacen[raiz2] = raiz1;
            sets--;
            return true;
        }
        return false;
    }
    int getSets(){return sets;}
    ~DisjointSetGrafo(){}
};

template<typename TV, typename TE>
bool compEdge(Edge<TV, TE>*a, Edge<TV, TE>*b){
    return (a->weight<b->weight);
}

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