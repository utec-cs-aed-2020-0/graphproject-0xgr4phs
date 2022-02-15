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
    DirectedGraph(const unordered_map<string, Vertex<TV, TE>*> &vertexes);

    bool insertVertex(string id, TV vertex) override;

    bool createEdge(string id1, string id2, TE w) override;

    bool deleteVertex(string id) override;

    bool deleteEdge(string id) override;

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
bool DirectedGraph<TV, TE>::insertVertex(string id, TV vertex) {
    // If id exists in map
    if (vertexes.find(id)) return false;
    // Create new pointer of vertex
    Vertex < TV, TE > *new_vertex = new Vertex <TV, TE>();
    // Assign data
    new_vertex->data = vertex;
    // Insert data to map
    vertexes.insert(id, new_vertex);
    this->V++;
    return true;
}

template<typename TV, typename TE>
bool DirectedGraph<TV, TE>::createEdge(string id1, string id2, TE w) {
    Vertex < TV, TE > *v1 = vertexes.find(id1);
    Vertex < TV, TE > *v2 = vertexes.find(id2);
    auto edge = new Edge<TV, TE>();
    edge->vertexes[0] = v1;
    edge->vertexes[1] = v2;
    edge->weight = w;
    v1->edges.insert(edge);
    delete v1;
    delete v2;
    delete edge;
    this->E++;
    return false;
}

template<typename TV, typename TE>
bool DirectedGraph<TV, TE>::deleteVertex(string id) {
    if (vertexes.find(id) == 0) return false;
    Vertex < TV, TE > *v = vertexes.find(id);
    std::list<Edge<TV, TE> *> list = v->edges;
    for (auto &val: list) {
        delete val;
    }
    delete v->edges;
    delete v;
    this->E--;
    return true;
}

template<typename TV, typename TE>
bool DirectedGraph<TV, TE>::deleteEdge(string id) {

    return false;
}

template<typename TV, typename TE>
TE &DirectedGraph<TV, TE>::operator()(string start, string end) {
    Vertex<TV,TE>* v1 = vertexes.find(start);
    Vertex<TV,TE>* v2 = vertexes.find(end);
    list<Edge<TV,TE>> list = v1->edges;
    for(auto &edge : list)
    {
        if (edge == v2)
            return edge.weight;
    }
}

template<typename TV, typename TE>
float DirectedGraph<TV, TE>::density() {

    return 0;
}

template<typename TV, typename TE>
bool DirectedGraph<TV, TE>::isDense(float threshold) {
    return false;
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
bool DirectedGraph<TV, TE>::findById(string id) {
    return false;
}

template<typename TV, typename TE>
void DirectedGraph<TV, TE>::display() {

}

template<typename TV, typename TE>
DirectedGraph<TV, TE>::DirectedGraph(const unordered_map<string, Vertex<TV, TE> *> &vertexes) {

}

#endif
