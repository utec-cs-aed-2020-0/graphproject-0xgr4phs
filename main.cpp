#include <iostream>
#include "./DirectedGraph.h"
#include "./UndirectedGraph.h"
#include "Tester/tester.h"
#include "Parser/parser.h"

using namespace std;

int main(int argc, char *argv[]) {
    std::cout << "================================================" << std::endl;
    std::cout << "MENU GRAPH TESTER" << std::endl;
    std::cout << "================================================" << std::endl;
    UnDirectedGraph<int,int>* graph = new UnDirectedGraph<int,int>();
    graph->insertVertex("1",1);
    graph->insertVertex("2",2);
    delete graph;
    //Tester::executeExamples();
    //Tester::executeParser();
    
    return EXIT_SUCCESS;
}