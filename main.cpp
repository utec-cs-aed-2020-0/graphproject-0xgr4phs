#include <iostream>
#include"DirectedGraph.h"
#include"bellman_ford.h"
#include "kruskal.h"
#include "prim.h"

//#include "Tester/tester.h"
//#include "Parser/parser.h"

using namespace std;

int main(int argc, char *argv[]) {
    std::cout << "================================================" << std::endl;
    std::cout << "MENU GRAPH TESTER" << std::endl;
    std::cout << "================================================" << std::endl;

    DirectedGraph<char, int> grafo;
    grafo.insertVertex("A1", 'a');
    grafo.insertVertex("A2", 'a');
    grafo.insertVertex("A3", 'a');
    grafo.insertVertex("A4", 'a');
    grafo.insertVertex("A5", 'a');
    grafo.insertVertex("A6", 'a');
    grafo.insertVertex("A7", 'a');

    grafo.createEdge("A1", "A2", 6);
    grafo.createEdge("A1", "A3", 5);
    grafo.createEdge("A1", "A4", 5);
    grafo.createEdge("A2", "A5", -1);
    grafo.createEdge("A3", "A2", -2);
    grafo.createEdge("A3", "A5", 1);
    grafo.createEdge("A4", "A3", -2);
    grafo.createEdge("A4", "A6", -1);
    grafo.createEdge("A5", "A7", 3);
    grafo.createEdge("A6", "A7", 3);

    grafo.display();

    DirectedGraph<char, int> bell = bellman_ford(grafo, "A1");
    //DirectedGraph<char, int> bell = kruskal(grafo);

    bell.display();

    //Tester::executeExamples();
    //Tester::executeParser();
    
    return EXIT_SUCCESS;
}