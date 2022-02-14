#ifndef DFS_H
#define DFS_H
#include "../DirectedGraph.h"
#include "../UndirectedGraph.h"
#include <iostream>
using namespace std;
template <typename TV, typename TE>
string DFS(Graph<TV,TE> graph, string startId)
{
    auto* root = graph->getVertex(startId);
    
    delete root;
}

#endif // DFS_H
