#ifndef NONDIRECTEDGRAPH_H
#define NONDIRECTEDGRAPH_H

#include "graph.h"

template <typename TV, typename TE>
class DirectedGraph : public Graph<TV, TE>
{
private:
    std::unordered_map<string, Vertex<TV, TE> *> vertexes;
    int E{};
    int V{};

public:
    DirectedGraph() = default;

    Vertex<TV,TE> & getVertex(string id) override {

    };
    DirectedGraph(const unordered_map<string, Vertex<TV, TE> *

                                      > &vertexes) : vertexes(vertexes);

    bool insertVertex(string id, TV vertex) override
    {
        if (findById(id))
            return false;
        Vertex<TV, TE> *new_vertex = new Vertex<TV, TE>(vertex);
        this->vertexes[id] = new_vertex;
        V++;
        return true;
    };

    bool createEdge(string id1, string id2, TE w) override
    {
        if (!findById(id1) || !findById(id2))
            return false;

        Vertex<TV, TE> *val1 = this->vertexes[id1];
        Vertex<TV, TE> *val2 = this->vertexes[id2];

        Edge<TV, TE> *val1Edge = new Edge<TV, TE>(w);

        val1Edge->vertexes[0] = val1;
        val1Edge->vertexes[1] = val2;
        val1->edges.push_front(val1Edge);

        return true;
    };

    bool deleteVertex(string id) override{
        Vertex<TV,TE>* vertex = this->vertexes[id];
         cout << id << ": ";
         for(auto &edge: vertex->edges)
         {
             cout << edge->weight << " ";
         }
         cout << endl;
    };

    bool deleteEdge(string start, string end) override{
        Vertex<TV,TE>* startEdge = this->vertexes[start];
        Vertex<TV,TE>* endEdge = this->vertexes[end];
        Edge<TV,TE>* temp_edge;
        for(Edge<TV,TE>* edge : startEdge->edges) {
            if (edge->vertexes[1] == endEdge)
            {
                temp_edge = edge;
            }
        }
    };

    TE &operator()(string start, string end) override{
        Vertex<TV,TE>* vertex = this->vertexes[start];
        Vertex<TV,TE>* endEdge = this->vertexes[end];
        TE *value;
        for(Edge<TV,TE>* &edge : vertex->edges)
        {
            if(edge->vertexes[1] == endEdge)
            {
                value = &edge->weight;
                break;
            }
        }
        //TE *value = new TE;
        return (*value);
    };

    float density() override
    {
        return E / V * (V - 1);
    };

    bool isDense(float threshold) override
    {
        return density() > threshold;
    };

    bool isConnected() override {
        // TODO: 
    };

    bool isStronglyConnected() throw() override {
        // TODO:
    };

    bool empty() override
    {
        return (this->V == 0);
    };

    void clear() override;

    void displayVertex(string id) override
    {
        Vertex<TV, TE> *vertex = this->vertexes[id];
        cout << id << ": ";
        for (auto &edge : vertex->edges)
        {
            cout << edge->weight << " ";
        }
        cout << endl;
    };

    bool findById(string id) override;

    void display() override
    {
        for (auto &val : this->vertexes)
        {
            displayVertex(val.first);
        }
        cout << endl;
    };
};
#endif
