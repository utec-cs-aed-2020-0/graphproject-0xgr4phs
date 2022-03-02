#include <iostream>

#include "Parser/json_test_astar.h"
#include "Parser/json_test_bellman_ford.h"
#include "Parser/json_test_dfs.h"
#include "Parser/json_test_dijkstra.h"
#include "Parser/json_test_floyd_warshall.h"
#include "Parser/json_test_greedy_bfs.h"
#include "Parser/json_test_kruskal.h"
#include "Parser/json_test_prim.h"

function<void(void)> tests[8]{AstarTest, BellmanFordTest, DFSTest, DijkstraTest, FloydWarshallTest, GreedyBFSTest, KruskalTest, PrimTest};

using namespace std;

int main(int argc, char *argv[]) {

    std::cout << "================================================" << std::endl;
    std::cout << "MENU GRAPH TESTER" << std::endl;
    std::cout << "================================================" << std::endl;
    int i;
    do
    {
        cout<<"Elija la opcion para realizar una prueba utilizando un algorimto:"<<endl;
        cout<<"0: Astar\n1: Bellman-ford\n2: DFS\n3: Dijkstra\n4: Floyd-warshall\n5: GreedyBFS\n6: Kruskal\n7: Prim"<<endl;
        cout<<"Opcion: ";
        cin>>i;
    }while(i>=0 && i<8);    
    cout<<"ADIOS"<<endl;

    return EXIT_SUCCESS; 
}