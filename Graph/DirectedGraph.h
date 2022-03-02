#ifndef DIRECTEDGRAPH_H
#define DIRECTEDGRAPH_H

/* Dependencias */
#include <iostream>
#include <algorithm>
#include <queue>
#include <unordered_set>
#include <deque>

/* Archivos importados */
#include "Graph.h"
#include "./Algorithms/data_estructures/bst.h"

using namespace std;

/* Declaración de clases y funciones */
template<typename TV, typename TE>
class DirectedGraph;

// Funciones auxiliares
template<typename VertexType, typename EdgeType>
DirectedGraph<VertexType, EdgeType> greedyBFS(DirectedGraph<VertexType, EdgeType> *graph, std::string start_node, std::string end_node);

template<typename TE>
struct matrix_square_pair;

template<typename TV,typename TE>
matrix_square_pair<TE> floyd_warshall(DirectedGraph<TV,TE> & g);

template<typename TV,typename TE>
deque<distance_pair<TE>> astar(DirectedGraph<TV,TE> & gr,unordered_map<string,TE> & h ,string start_node,string end_node);

template<typename TV,typename TE>
DirectedGraph<TV,TE> dijkstra(DirectedGraph<TV,TE> & , string);

template<typename TV, typename TE>
DirectedGraph<TV, TE> bellman_ford(DirectedGraph<TV, TE> grafo, const string &nodoInicio);
template<typename TV,typename TE>
DirectedGraph<TV, TE> kruskal(DirectedGraph<TV, TE> grafo);

class DisjointSetGrafoDirigido;

class DisjointSetGrafoNoDirigido;

template<typename TV, typename TE>
DirectedGraph<TV, TE> prim( DirectedGraph<TV, TE> grafo, string inicio);



template<typename TV, typename TE>
class DirectedGraph : public Graph<TV, TE> {
public:
    DirectedGraph() = default;
    DirectedGraph(const unordered_map<string, Vertex<TV, TE> *

    > &vertexes);

    bool insertVertex(string id, TV vertex) override;

    bool createEdge(string id1, string id2, TE w) override;

    bool deleteVertex(string id) override;

    bool deleteEdge(string id1, string id2) override;

    TE &operator()(string start, string end) override;

    float density() override;

    bool isDense(float threshold) override;

    bool isConnected() override;

    bool isStronglyConnected() throw() override;

    bool empty() override;

    void clear() override;

    void displayVertex(string id) override;

    bool findById(string id) override;

    void display() override;
private:
    template<typename VertexType, typename EdgeType>
    friend DirectedGraph<VertexType, EdgeType> greedyBFS(DirectedGraph<VertexType, EdgeType> *graph, std::string start_node, std::string end_node);
};

template<typename TV, typename TE>
DirectedGraph<TV, TE>::DirectedGraph(const unordered_map<string, Vertex<TV, TE> *> &vertexes) {
    this->vertexes = vertexes;
}

template<typename TV, typename TE>
bool DirectedGraph<TV, TE>::insertVertex(string id, TV vertex) {
    if (this->vertexes.find(id) != this->vertexes.end()) return false;

    this->vertexes[id] = new Vertex<TV, TE>{id, vertex, std::list<Edge<TV, TE> *>{}};

    ++this->V;
    return true;
}

template<typename TV, typename TE>
bool DirectedGraph<TV, TE>::createEdge(string id1, string id2, TE w) {
    if (this->vertexes.find(id1) == this->vertexes.end() ||
        this->vertexes.find(id2) == this->vertexes.end())
        return false;
    auto v1 = this->vertexes[id1];
    auto v2 = this->vertexes[id2];

    for (auto it = v1->edges.begin(); it != v1->edges.end(); ++it) {
        if ((*it)->vertexes[1] == v2) return false;
    }

    v1->edges.push_front(new Edge<TV, TE>{{v1, v2}, w});

    ++this->E;
    return true;
}

template<typename TV, typename TE>
bool DirectedGraph<TV, TE>::deleteVertex(string id) {
    if (this->vertexes.find(id) == this->vertexes.end()) return false;
    auto v = this->vertexes[id];
    for (auto it = v->edges.begin(); it != v->edges.end(); ++it) {

        delete *it;
        --this->E;
    }
    v->edges.clear();

    for (auto it = this->vertexes.begin(); it != this->vertexes.end(); ++it)
        if (it->first != id)
            deleteEdge(it->first, id);


    delete this->vertexes[id];
    this->vertexes.erase(id);

    --this->V;

    return true;
}

template<typename TV, typename TE>
bool DirectedGraph<TV, TE>::deleteEdge(string id1, string id2) {
    if (this->vertexes.find(id1) == this->vertexes.end() ||
        this->vertexes.find(id2) == this->vertexes.end())
        return false;

    auto inicio = this->vertexes[id1];
    auto llegada = this->vertexes[id2];


    for (auto it = inicio->edges.begin(); it != inicio->edges.end(); ++it) {
        if ((*it)->vertexes[1] == llegada) {
            delete *it;
            inicio->edges.erase(it);
            --this->E;
            return true;
        }
    }
    return false;
}

template<typename TV, typename TE>
TE &DirectedGraph<TV, TE>::operator()(string start, string end) {
    if(this->vertexes.find(start) == this->vertexes.end()  ||
       this->vertexes.find(end) == this->vertexes.end()) throw "No se encuentra uno o ambos vertices";
    auto inicio = this->vertexes[start];
    auto llegada = this->vertexes[end];


    for(auto it = inicio->edges.begin();it!= inicio->edges.end();++it){
        if((*it)->vertexes[1] == llegada) return (*it)->weight;

    }

    throw "No se encuentra la arista";
}

template<typename TV, typename TE>
float DirectedGraph<TV, TE>::density() {
    return this->E / (this->V * (this->V - 1));
}

template<typename TV, typename TE>
bool DirectedGraph<TV, TE>::isDense(float threshold) {
    return density() >= threshold;
}

template<typename TV, typename TE>
bool DirectedGraph<TV, TE>::isConnected() {
    return false;
}

template<typename TV, typename TE>
bool DirectedGraph<TV, TE>::isStronglyConnected() throw() {
    unordered_set<string> visitados;
    queue<string> ayuda;
    for (auto it = this->vertexes.begin(); it != this->vertexes.end(); ++it) {
        auto v = it->second;
        ayuda.push(v->id);
        visitados.insert(v->id);
        while (!ayuda.empty()) {
            auto temp = ayuda.front();
            ayuda.pop();
            for (auto it = this->vertexes[temp]->edges.begin(); it != this->vertexes[temp]->edges.end(); ++it) {
                auto a_insertar = (*it)->vertexes[1]->id;
                if (visitados.find(a_insertar) == visitados.end()) {
                    ayuda.push(a_insertar);
                    visitados.insert(a_insertar);
                }
            }
        }
        if (visitados.size() != this->V) return false;
        visitados.clear();
    }
    return true;
}

template<typename TV, typename TE>
bool DirectedGraph<TV, TE>::empty() {
    return this->V == 0;
}

template<typename TV, typename TE>
void DirectedGraph<TV, TE>::clear() {
    while (this->vertexes.size() != 0) {

        deleteVertex(this->vertexes.begin()->first);

    }
}

template<typename TV, typename TE>
void DirectedGraph<TV, TE>::displayVertex(string id) {
    if (this->vertexes.find(id) == this->vertexes.end()) throw "No se encuentra ese vertice";
    auto v = this->vertexes[id];
    cout << "Las aristas de " << v->id << " son: ";
    for (auto it = v->edges.begin(); it != v->edges.end(); ++it) {
        cout << "({" << (*it)->vertexes[0]->id << "," << (*it)->vertexes[1]->id << "}, w: " << (*it)->weight << ") ";
    }
    cout << endl;
}

template<typename TV, typename TE>
bool DirectedGraph<TV, TE>::findById(string id) {
    return this->vertexes.find(id) != this->vertexes.end();
}

template<typename TV, typename TE>
void DirectedGraph<TV, TE>::display() {
    vector<string> keys;


    for (auto it = this->vertexes.begin(); it != this->vertexes.end(); ++it) {
        keys.push_back(it->first);

    }

    sort(keys.begin(), keys.end());
    for (auto &i: keys) {
        auto v = this->vertexes[i];
        cout << "Las aristas de " << v->id << " son: ";
        for (auto it = v->edges.begin(); it != v->edges.end(); ++it) {
            cout << "({" << (*it)->vertexes[0]->id << "," << (*it)->vertexes[1]->id << "}, w: " << (*it)->weight
                 << ") ";
        }
        cout << endl;
    }


}

#endif // DIRECTEDGRAPH_H
