#include <iomanip>
#include "./src/UndirectedGraph.h"
#include "./src/DirectedGraph.h"
#include "./src/algorithms/GreedyBFS.h"
#include "./src/algorithms/DFS.h"
using namespace std;

int main() {
    Graph<int, int> *graph = new DirectedGraph<int, int>();
    cout << boolalpha;
    graph->insertVertex("1", 1);
    graph->insertVertex("2", 2);
    graph->insertVertex("3", 3);
    graph->insertVertex("4", 4);
    graph->insertVertex("5", 5);
    graph->createEdge("1", "2", 3);
    graph->createEdge("2","3", 4);
    graph->createEdge("1","3", 9);
//    cout << greedyBFS(graph, "1", "3");

    cout << DFS(graph, "1");
    delete graph;
    return 0;
}