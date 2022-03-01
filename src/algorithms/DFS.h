//
//        $$$$$$$\  $$$$$$$$\  $$$$$$\      $$\
//        $$  __$$\ $$  _____|$$  __$$\     $$ |
//        $$ |  $$ |$$ |      $$ /  \__|    $$$$$$$\
//        $$ |  $$ |$$$$$\    \$$$$$$\      $$  __$$\
//        $$ |  $$ |$$  __|    \____$$\     $$ |  $$ |
//        $$ |  $$ |$$ |      $$\   $$ |    $$ |  $$ |
//        $$$$$$$  |$$ |      \$$$$$$  |$$\ $$ |  $$ |
//        \_______/ \__|       \______/ \__|\__|  \__|
//

#ifndef DFS_H
#define DFS_H

/* Depedencias */
#include <iostream>
#include <stack>
#include <stdexcept>

/* Archivos importados */
#include "../Graph.h"


/**
 * DFS
 *
 * El codicioso algoritmo de búsqueda mejor primero siempre selecciona la ruta que parece mejor
 * en ese momento. Es la combinación de algoritmos de búsqueda primero en profundidad y primero
 * en amplitud. Utiliza la función heurística y la búsqueda. La búsqueda Best-first nos permite
 * aprovechar las ventajas de ambos algoritmos.
 *
 * Fuente: https://bit.ly/3C1sy3E
 */

/* Implementación */
template <typename VertexType,typename EdgeType>
std::string DFS(Graph<VertexType,EdgeType> *graph, std::string start_node){
    // Verificar si existen los dos vértices en el grafo
    if (graph->findById(start_node)) std::logic_error("No se encontró el nodo incial. ");

    // Variable de salida (recorrdigo del DFS)
    std::string path = "";

    typedef Vertex<VertexType, EdgeType> vertex_t;
    typedef Edge<VertexType, EdgeType> edge_t;
    typedef std::pair<EdgeType, std::pair<vertex_t*, vertex_t*>> type_pair;

    std::unordered_map<std::string, bool> visited(graph->V);
    std::stack<type_pair> stack_vertexes;

    Vertex<VertexType,EdgeType> *start_vertex = graph->vertexes[start_node];
    Vertex<VertexType,EdgeType> *end_vertex= graph->vertexes[start_node];

    visited[start_vertex->id] = true;
    stack_vertexes.push(make_pair(0, std::make_pair(start_vertex, start_vertex)));

    while (!stack_vertexes.empty()) {
        auto weight = stack_vertexes.top().first;
        auto* left = stack_vertexes.top().second.first;
        auto* right = stack_vertexes.top().second.second;
        stack_vertexes.pop();
        path += "(Left: " + std::to_string(left->data) + ", Weight: " + std::to_string(weight) + ", Right: " + std::to_string(right->data) + ")\n";

        for (edge_t* &edge : right->edges) {
            auto *connected_vertex = edge->vertexes[1];
            if (!visited[connected_vertex->id]) {
                visited[connected_vertex->id] = true;
                stack_vertexes.push(std::make_pair(edge->weight, std::make_pair(right, connected_vertex)));
            }
        }
    }
    return path;
};

#endif // GREEDYBFS_H

