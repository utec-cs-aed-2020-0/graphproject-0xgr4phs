#ifndef UNDIRECTEDGRAPH_H
#define UNDIRECTEDGRAPH_H

#include "graph.h"

template<typename TV, typename TE>
class UnDirectedGraph : public Graph<TV, TE>{
public:
    bool insertVertex(string id, TV data);
    bool createEdge(string id1, string id2, TE w = 0);
    bool deleteVertex(string id);
    bool deleteEdge(string id1, string id2);
    TE &operator()(string id1, string id2);
    float density();
    bool isDense(float threshold = 0.5);
    bool isConnected();
    bool isStronglyConnected() throw();
    void clear();

    void displayVertex(string id);
    bool findById(string id);
    void display();
};

template<typename TV, typename TE>
float UnDirectedGraph<TV, TE>::density() {
    return this->E/(this->V*(this->V-1));
}

template<typename TV, typename TE>
bool UnDirectedGraph<TV, TE>::isDense(float threshold) {
    return this->density() >= threshold;
}

template<typename TV, typename TE>
bool UnDirectedGraph<TV, TE>::findById(string id){
    return this->vertexes.find(id) != this->vertexes.end();
}

template<typename TV, typename TE>
bool UnDirectedGraph<TV, TE>::insertVertex(string id, TV data) {
    // VERIFICAR QUE EL VERTICE NO EXISTA
    if(this->findById(id)) return false;
    // CREAR VERTICE
    this->vertexes.insert({id, new Vertex<TV, TE>{data, id}});
    this->V++;
    return true;
}

template<typename TV, typename TE>
bool UnDirectedGraph<TV, TE>::createEdge(string id1, string id2, TE w) {
    // VERIFICAR QUE AMBOS VERTICES EXISTAN
    if(!this->findById(id1) || !this->findById(id2)) return false;
    // VERIFICAR QUE ALGUNA DE LAS ARISTAS NO EXISTA
    for (auto it: this->vertexes.at(id1)->edges) {
        if (it.vertexes[0] == this->vertexes[id1] && it.vertexes[1] == this->vertexes[id2]) {
            return false;
        }
    }
    // CREAR ARISTAS
    this->vertexes.at(id1)->edges.push_back(new Edge<TV, TE>{{this->vertexes.at(id1), this->vertexes.at(id2)}, w});
    this->vertexes.at(id2)->edges.push_back(new Edge<TV, TE>{{this->vertexes.at(id2), this->vertexes.at(id1)}, w});

    this->E++;
    return true;
}

template<typename TV, typename TE>
bool UnDirectedGraph<TV, TE>::deleteVertex(string id) {
    // BUSCAR SI EXISTE EL NODO
    if (!this->findById(id)) return false;
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
bool UnDirectedGraph<TV, TE>::deleteEdge(string id1, string id2) {
    // VERIFICAR QUE AMBOS VERTICES EXISTAN
    if(!this->findById(id1) || !this->findById(id2)) return false;
    for(auto edge: this->vertexes.at(id1)->edges)
}


#endif