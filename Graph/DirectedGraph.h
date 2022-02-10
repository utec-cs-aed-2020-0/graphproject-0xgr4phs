#ifndef NONDIRECTEDGRAPH_H
#define NONDIRECTEDGRAPH_H

#include "graph.h"

template<typename TV, typename TE>
class DirectedGraph : public Graph<TV, TE> {
private:
    std::unordered_map<string, Vertex<TV, TE> *> vertexes;
    int E{};
    int V{};
public:
    DirectedGraph(const unordered_map<string, Vertex < TV, TE> *

    > & vertexes);

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
};

template<typename TV, typename TE>
bool DirectedGraph<TV, TE>::insertVertex(string id, TV data) {
    // VERIFICAR SI EL VERTICE EXISTE
    if (this->vertexes.find(id) == this->vertexes.end()) return false;
    // CREAR VERTICE
    this->vertexes.insert({id, new Vertex<TV, TE>{data}});
    this->V++;
    return true;
}

template<typename TV, typename TE>
bool DirectedGraph<TV, TE>::createEdge(string id1, string id2, TE w) {
    // VERIFICAR QUE LOS VERTICES EXISTAN 
    if (this->vertexes.find(id1) == this->vertexes.end() || this->vertexes.find(id2) == this->vertexes.end())
        return false;
    // VERIFICAR QUE LA ARISTA NO EXISTA
    for (auto it: this->vertexes.at(id1)->edges) {
        if (it.vertexes[0] == this->vertexes[id1] && it.vertexes[1] == this->vertexes[id2]) {
            return false;
        }
    }
    // AGREGAR LA ARISTA
    this->vertexes.at(id1)->edges.push_back(new Edge<TV, TE>{{this->vertexes.at(id1), this->vertexes.at(id2)}, w});
    this->E++;
    return true;
}

template<typename TV, typename TE>
bool DirectedGraph<TV, TE>::deleteVertex(string id) {
    // BUSCAR SI EXISTE EL NODO
    if (this->vertexes.find(id) == this->vertexes.end()) return false;
    // ELIMINAR ARISTAS QUE INVOLUCREN AL NODO
    for (auto it_vertexes = this->vertexes.begin(); it_vertexes != this->vertexes.end(); ++it_vertexes) {
        for (auto it_edges = it_vertexes->second->edges.begin(); it_edges != it_vertexes->second->edges.end();) {
            if ((*it_edges)->vertexes[0] == this->vertexes.at(id) ||
                (*it_edges)->vertexes[1] == this->vertexes.at(id)) {
                delete *it_edges;
                it_vertexes->second->edges.erase(it_edges++);
            } else {
                it_edges++;
            }
        }
    }
    // ELLIMINAR NODO
    delete this->vertexes.at(id);
    this->vertexes.erase(id);
    this->V--;
    return true;
}

template<typename TV, typename TE>
bool DirectedGraph<TV, TE>::deleteEdge(string id1, string id2) {
    // BUSCAR SI EXISTE EL NODO
    if (this->vertexes.find(id1) == this->vertexes.end()) return false;
    // BUSCAR SI ARISTA EXISTE
    for (auto it_edge = this->vertexes.at(id1).edges.begin();
         it_edge != this->vertexes.at(id1).edges.end(); it_edge++) {
        // ELIMINAR ARISTA
        if ((*it_edge)->vertexes[1] == this->vertexes.at(id2)) {
            delete *it_edge;
            this->vertexes.at(id1)->edges.erase(it_edge);
            this->E--;
            return true;
        }
    }
    return false;
}

template<typename TV, typename TE>
TE &DirectedGraph<TV, TE>::operator()(string id1, string id2) {
    // VERIFICAR QUE EXISTAN LOS VERTICES
    if (this->vertexes.find(id1) == this->vertexes.end()) throw ("No se encontro el vertice");
    // ENCONTRAR LA ARISTA QUE COINCIDA
    for (auto it_edge: this->vertexes.at(id1)->edges) {
        // RETORNAR SI COINCIDEN
        if (it_edge->vertexes[1] == this->vertexes.at(id2)) {
            return it_edge->weight;
        }
    }
    throw ("No existe la arista");
}

template<typename TV, typename TE>
float DirectedGraph<TV, TE>::density() {
    double e_abs = 0;
    // HALLAR TODAS LAS ARISTAS
    for (auto vert: this->vertexes) {
        e_abs += vert->edges.size();
    }
    return 2 * e_abs / (this->vertexes.size() * (this->vertexes.size() - 1));
}

template<typename TV, typename TE>
bool DirectedGraph<TV, TE>::isDense(float threshold) {
    return this->density() >= threshold;
}

template<typename TV, typename TE>
bool DirectedGraph<TV, TE>::isConnected() {

    return false;
}

template<typename TV, typename TE>
bool DirectedGraph<TV, TE>::isStronglyConnected() throw() {
    return false;
}

template<typename TV, typename TE>
bool DirectedGraph<TV, TE>::empty() {
    return (V == 0);
}

template<typename TV, typename TE>
void DirectedGraph<TV, TE>::clear() {
    for(auto &vertex : vertexes)
    {
        delete vertex.second;
    }
}

template<typename TV, typename TE>
void DirectedGraph<TV, TE>::displayVertex(string id) {

}

template<typename TV, typename TE>
bool DirectedGraph<TV, TE>::findById(string id){
    return this->vertexes.find(id) != this->vertexes.end();
}

template<typename TV, typename TE>
void DirectedGraph<TV, TE>::display() {

}

template<typename TV, typename TE>
DirectedGraph<TV, TE>::DirectedGraph(const unordered_map<string, Vertex<TV, TE> *> &vertexes) {

}

#endif
