#ifndef UNDIRECTEDGRAPH_H
#define UNDIRECTEDGRAPH_H

#include <string>
#include "graph.h"

template<typename TV, typename TE>
class UnDirectedGraph : public Graph<TV, TE> {
private:
public:
    int V{};
    int E{};

    UnDirectedGraph() = default;

    Vertex<TV,TE> & getVertex(string id) override {

    };
    bool insertVertex(string id, TV vertex) override{
        if (findById(id)) return false;
        Vertex<TV,TE>* new_vertex = new Vertex<TV,TE>(vertex);
        this->vertexes[id] = new_vertex;
        this->V++;
        return true;
    };

    bool createEdge(string id1, string id2, TE w) override {
        Vertex<TV,TE>* val1 = this->vertexes[id1];
        Vertex<TV,TE>* val2 = this->vertexes[id2];
        Edge<TV,TE>* val1Edge = new Edge<TV,TE>(w);
        val1Edge->vertexes[0] = val1;
        val1Edge->vertexes[1] = val2;
        val1->edges.push_front(val1Edge);
        Edge<TV,TE>* val2Edge = new Edge<TV,TE>(w);
        val2Edge->vertexes[0] = val2;
        val2Edge->vertexes[1] = val1;
        val2->edges.push_back(val2Edge);
        return true;
    };

    bool deleteVertex(string id) override {
        delete this->vertexes[id];
        for(pair<string, Vertex<TV,TE>*> paired : this->vertexes)
        {
            cout << "(" << paired.first << ", " << id << ")"<< endl;
            if (paired.first != id)
            {
                deleteEdge(paired.first, id);
            }
        }
        this->vertexes.erase(id);
        return true;
    };

    bool deleteEdge(string start, string end) override {
        // TODO:
        Vertex<TV,TE>* startEdge = this->vertexes[start];
        Vertex<TV,TE>* endEdge = this->vertexes[end];
        Edge<TV,TE>* temp_edge;
        for(Edge<TV,TE>* edge : startEdge->edges) {
            if (edge->vertexes[1] == endEdge)
            {
                temp_edge = edge;
            }
        }
        startEdge->edges.remove(temp_edge);
        for(Edge<TV,TE>* edge : endEdge->edges) {
            if (edge->vertexes[1] == startEdge)
            {
                temp_edge = edge;
            }
        }
        endEdge->edges.remove(temp_edge);
        
        return true;
    };

    TE &operator()(string start, string end) override {
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

    float density() override {
        return (2*E)/V*(V-1);
    };

    bool isDense(float threshold) override {
        return density() >= threshold;
    };

    bool isConnected() override {
        return true;
    };

    bool isStronglyConnected() throw() override {
        return true;
    };

    bool empty() override {
        return (this->V == 0);
    };

    void clear() override {
        for(auto& paired : this->vertexes)
        {
            paired.second->edges.clear();
            delete paired.second;
        }
        this->vertexes.clear();
    };

    void displayVertex(string id) override
    {
         Vertex<TV,TE>* vertex = this->vertexes[id];
         cout << id << ": ";
         for(auto &edge: vertex->edges)
         {
             cout << edge->weight << " ";
         }
         cout << endl;
    };

    bool findById(string id) override {
        // TODO:
        return false;
    };

    void display() override {
        for(auto &val: this->vertexes) {
            displayVertex(val.first);
        }
        cout << endl;
    };
};
#endif
