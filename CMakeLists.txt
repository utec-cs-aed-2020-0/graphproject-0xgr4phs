cmake_minimum_required(VERSION 3.21)
project(GraphsProject)

set(CMAKE_CXX_STANDARD 17)

add_executable(GraphsProject main.cpp src/Graph.h src/UndirectedGraph.h src/algorithms/GreedyBFS.h src/DirectedGraph.h src/algorithms/DFS.h)
