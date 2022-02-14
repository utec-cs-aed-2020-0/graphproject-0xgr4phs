cmake_minimum_required(VERSION 3.21)
project(graphproject_0xgr4phs)

set(CMAKE_CXX_STANDARD 14)

include_directories(Graph)
include_directories(Graph/Algorithms)

add_executable(graphproject_0xgr4phs
        Graph/Algorithms/astar.h
        Graph/Algorithms/bfs.h
        Graph/Algorithms/dfs.h
        Graph/Algorithms/dijkstra.h
        Graph/Algorithms/kruskal.h
        Graph/Algorithms/prim.h
        Graph/DirectedGraph.h
        Graph/graph.h
        Graph/UndirectedGraph.h
        main.cpp Tester/tester.h Parser/parser.h)
