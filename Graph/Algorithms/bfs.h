#ifndef BFS_H
#define BFS_H

#include "../DirectedGraph.h"
#include "../UndirectedGraph.h"
#include <iostream>
#include <deque>
using namespace std;

template <typename TV, typename TE>
string BFS(Graph<TV, TE> graph, int startId)
{
    Vertex<TV,TE>* root = graph->getVertex(startId);
    deque<Vertex<TV,TE>*> pass;
    unordered_map<Vertex<TV,TE>*, bool> visited;
    pass.push_back(root);
    visited[root] = true;
    string output = "";
    while (!pass.empty())
    {
        Vertex<TV,TE>* s = pass.front();
        output += s->data;
        pass.pop_front();

        for (Edge<TV,TE>* &edge: s->edges)
        {
            edge->vertexes[1]
        }
    }
    
    delete root;

    
}
#endif // BFS_H