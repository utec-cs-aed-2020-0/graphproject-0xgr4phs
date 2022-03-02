#ifndef GRAPHPROJECT_0XGR4PHS_DS_H
#define GRAPHPROJECT_0XGR4PHS_DS_H

#include "../UndirectedGraph.h"
#include "../DirectedGraph.h"
#include "../graph.h"
#include <unordered_map>
#include<utility>

/**
 * Funcion para comparar aristas con respecto al peso
 */

using namespace std;

/**
 * Clase que representa el disjoint set para los vertices de un grafo
 */
class DisjointSetGrafoDirigido{
private:
    unordered_map<string, string> almacen;
    int sets;
public:
    template<typename TV, typename TE>
    DisjointSetGrafoDirigido(DirectedGraph<TV, TE> &grafo){
        sets = 0;
        for(auto vertice: grafo.vertexes){
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
    ~DisjointSetGrafoDirigido(){}
};

class DisjointSetGrafoNoDirigido{
private:
    unordered_map<string, string> almacen;
    int sets;
public:
    template<typename TV, typename TE>
    DisjointSetGrafoNoDirigido(UnDirectedGraph<TV, TE> &grafo){
        sets = 0;
        for(auto vertice: grafo.vertexes){
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
    ~DisjointSetGrafoNoDirigido(){}
};

#endif
