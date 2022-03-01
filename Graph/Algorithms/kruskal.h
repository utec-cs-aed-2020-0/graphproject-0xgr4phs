#ifndef KRUSKAL_H
#define KRUSKAL_H

#include "../DirectedGraph.h"
#include "../UndirectedGraph.h"
#include <unordered_map>
#include<utility>

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
UnDirectedGraph<TV, TE> kruskal(const UnDirectedGraph<TV, TE>& grafo){
    UnDirectedGraph<TV, TE> retorno;
    DisjointSetGrafo gSet(grafo);
    for(const pair<string,Vertex<TV, TE>*>& vertice: grafo.vertexes){

    }




    return retorno;
}

#endif