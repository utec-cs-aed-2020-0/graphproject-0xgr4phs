#ifndef UNDIRECTEDGRAPH_H
#define UNDIRECTEDGRAPH_H

#include <string>
#include "graph.h"

template<typename TV, typename TE>
class UnDirectedGraph : public Graph<TV, TE>{
public:
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
bool UnDirectedGraph<TV, TE>::insertVertex(string id, TV vertex) {
    return false;
}

template<typename TV, typename TE>
bool UnDirectedGraph<TV, TE>::createEdge(string id1, string id2, TE w) {
    return false;
}

template<typename TV, typename TE>
bool UnDirectedGraph<TV, TE>::deleteVertex(string id) {
    return false;
}

template<typename TV, typename TE>
bool UnDirectedGraph<TV, TE>::deleteEdge(string id) {
    return false;
}

template<typename TV, typename TE>
TE &UnDirectedGraph<TV, TE>::operator()(string start, string end) {
    return <#initializer#>;
}

template<typename TV, typename TE>
float UnDirectedGraph<TV, TE>::density() {
    return 0;
}

template<typename TV, typename TE>
bool UnDirectedGraph<TV, TE>::isDense(float threshold) {
    return false;
}

template<typename TV, typename TE>
bool UnDirectedGraph<TV, TE>::isConnected() {
    return false;
}

template<typename TV, typename TE>
bool UnDirectedGraph<TV, TE>::isStronglyConnected() throw() {
    return Graph::isStronglyConnected();
}

template<typename TV, typename TE>
bool UnDirectedGraph<TV, TE>::empty() {
    return Graph::empty();
}

template<typename TV, typename TE>
void UnDirectedGraph<TV, TE>::clear() {

}

template<typename TV, typename TE>
void UnDirectedGraph<TV, TE>::displayVertex(string id) {

}

template<typename TV, typename TE>
bool UnDirectedGraph<TV, TE>::findById(string id) {
    return false;
}

template<typename TV, typename TE>
void UnDirectedGraph<TV, TE>::display() {

}

#endif
