#ifndef DFS_H
#define DFS_H
#include "../DirectedGraph.h"
#include "../UndirectedGraph.h"
#include <iostream>
#include <stack>
using namespace std;
template <typename TV, typename TE>
string DFS(Graph<TV,TE> graph, string startId)
{
    Vertex<TV,TE>* root = graph->getVertex(startId);
    stack<Vertex<TV,TE>*> pass;
    unordered_map<Vertex<TV,TE>*, bool> visited;
    pass.push_back(root);
    visited[root] = true;
    string output = "";
    while (!pass.empty())
    {
        Vertex<TV,TE>* s = pass.front();
        output += s->data;
        pass.pop();
        for (Edge<TV,TE>* &edge: s->edges)
        {
            edge->vertexes[1]
            // pass.push()
        }
    }
    
    delete root;
#endif // DFS_H
