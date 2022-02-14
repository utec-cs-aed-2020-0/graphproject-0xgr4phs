#ifndef BFS_H
#define BFS_H

#include "../DirectedGraph.h"
#include "../UndirectedGraph.h"
#include <iostream>
#include <deque>
using namespace std;

template <typename TV, typename TE>
string BFS(Graph<TV, TE> graph, int startIndex)
{
    auto* root = graph->getVertex(startId);
    deque<Vertex<TV,TE>*> pass;
    bool[] 
    pass.push_back(root);
    while (!pass.empty())
    {
        
    }
    
    delete root;

    
}
#endif // BFS_H