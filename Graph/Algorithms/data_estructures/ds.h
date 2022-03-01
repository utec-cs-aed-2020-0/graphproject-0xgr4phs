#ifndef GRAPHPROJECT_0XGR4PHS_DS_H
#define GRAPHPROJECT_0XGR4PHS_DS_H

#include "../UndirectedGraph.h"
#include "../DirectedGraph.h"
#include <unordered_map>
#include<utility>

using namespace std;

/**
 * Clase que representa el disjoint set para los vertices de un grafo
 */
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

#endif
