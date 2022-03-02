
//   /$$$$$$                                      /$$                 /$$$$$$$  /$$$$$$$$ /$$$$$$
//  /$$__  $$                                    | $$                | $$__  $$| $$_____//$$__  $$
// | $$  \__/  /$$$$$$   /$$$$$$   /$$$$$$   /$$$$$$$ /$$   /$$      | $$  \ $$| $$     | $$  \__/
// | $$ /$$$$ /$$__  $$ /$$__  $$ /$$__  $$ /$$__  $$| $$  | $$      | $$$$$$$ | $$$$$  |  $$$$$$
// | $$|_  $$| $$  \__/| $$$$$$$$| $$$$$$$$| $$  | $$| $$  | $$      | $$__  $$| $$__/   \____  $$
// | $$  \ $$| $$      | $$_____/| $$_____/| $$  | $$| $$  | $$      | $$  \ $$| $$      /$$  \ $$
// |  $$$$$$/| $$      |  $$$$$$$|  $$$$$$$|  $$$$$$$|  $$$$$$$      | $$$$$$$/| $$     |  $$$$$$/
//  \______/ |__/       \_______/ \_______/ \_______/ \____  $$      |_______/ |__/      \______/
//                                                    /$$  | $$
//                                                   |  $$$$$$/
//                                                    \______/

#ifndef GREEDYBFS_H
#define GREEDYBFS_H

/* Depedencias */
#include <iostream>
#include <queue>
#include <stdexcept>
#include <string>

/* Archivos importados */
#include "../UndirectedGraph.h"
#include "../DirectedGraph.h"
/**
 * Greedy BFS
 *
 * El codicioso algoritmo de búsqueda mejor primero siempre selecciona la ruta que parece mejor
 * en ese momento. Es la combinación de algoritmos de búsqueda primero en profundidad y primero
 * en amplitud. Utiliza la función heurística y la búsqueda. La búsqueda Best-first nos permite
 * aprovechar las ventajas de ambos algoritmos.
 *
 * Fuente: https://bit.ly/3C1sy3E
 */

/* Implementación */
template <typename VertexType, typename EdgeType>
DirectedGraph<VertexType, EdgeType> greedyBFS(DirectedGraph<VertexType, EdgeType> *graph, std::string start_node,
                                              std::string end_node)
{
    // Verificar si existen los dos vértices en el grafo
    if (graph->findById(start_node) && graph->findById(end_node))
        std::logic_error("Los nodos parámetros no funcionan correctamente.");

    // Variable de salida (recorrdigo del greedyBFS)
    std::string path = "";
    DirectedGraph<VertexType, EdgeType> output;
    typedef Vertex<VertexType, EdgeType> vertex_t;
    typedef Edge<VertexType, EdgeType> edge_t;
    typedef std::pair<EdgeType, std::pair<vertex_t *, vertex_t *>> type_pair;

    std::unordered_map<std::string, bool> visited(graph->V);
    std::priority_queue<type_pair, std::vector<type_pair>, std::greater<type_pair>> pq;

    Vertex<VertexType, EdgeType> *start_vertex = graph->vertexes[start_node];
    Vertex<VertexType, EdgeType> *end_vertex = graph->vertexes[end_node];

    visited[start_vertex->id] = true;
    pq.push(make_pair(0, std::make_pair(start_vertex, start_vertex)));

    while (!pq.empty())
    {
        auto weight = pq.top().first;
        auto *left = pq.top().second.first;
        auto *right = pq.top().second.second;
        pq.pop();
        /* path += "(Left: " + std::to_string(left->data) + ", Weight: " + std::to_string(weight) + ", Right: " + std::to_string(right->data) + ")\n"; */
        output.insertVertex(right->id, right->data);
        output.insertVertex(left->id, left->data);

        output.createEdge(left->id, right->id, weight);

        if (right == end_vertex)
            break;

        for (edge_t *&edge : right->edges)
        {
            auto *connected_vertex = edge->vertexes[1];
            if (!visited[connected_vertex->id])
            {
                visited[connected_vertex->id] = true;
                pq.push(std::make_pair(edge->weight, std::make_pair(right, connected_vertex)));
            }
        }
    }
    cout << path;
    return output;
};

template <typename VertexType, typename EdgeType>
UnDirectedGraph<VertexType, EdgeType> greedyBFS(UnDirectedGraph<VertexType, EdgeType> *graph, std::string start_node,
                                                std::string end_node)
{
    // Verificar si existen los dos vértices en el grafo
    if (graph->findById(start_node) && graph->findById(end_node))
        std::logic_error("Los nodos parámetros no funcionan correctamente.");

    // Variable de salida (recorrdigo del greedyBFS)
    std::string path = "";
    UnDirectedGraph<VertexType, EdgeType> output;
    typedef Vertex<VertexType, EdgeType> vertex_t;
    typedef Edge<VertexType, EdgeType> edge_t;
    typedef std::pair<EdgeType, std::pair<vertex_t *, vertex_t *>> type_pair;

    std::unordered_map<std::string, bool> visited(graph->V);
    std::priority_queue<type_pair, std::vector<type_pair>, std::greater<type_pair>> pq;

    Vertex<VertexType, EdgeType> *start_vertex = graph->vertexes[start_node];
    Vertex<VertexType, EdgeType> *end_vertex = graph->vertexes[end_node];

    visited[start_vertex->id] = true;
    pq.push(make_pair(0, std::make_pair(start_vertex, start_vertex)));

    while (!pq.empty())
    {
        auto weight = pq.top().first;
        auto *left = pq.top().second.first;
        auto *right = pq.top().second.second;
        pq.pop();
        /* path += "(Left: " + std::to_string(left->data) + ", Weight: " + std::to_string(weight) + ", Right: " + std::to_string(right->data) + ")\n"; */
        output.insertVertex(right->id, right->data);
        output.insertVertex(left->id, left->data);

        output.createEdge(left->id, right->id, weight);

        if (right == end_vertex)
            break;

        for (edge_t *&edge : right->edges)
        {
            auto *connected_vertex = edge->vertexes[1];
            if (!visited[connected_vertex->id])
            {
                visited[connected_vertex->id] = true;
                pq.push(std::make_pair(edge->weight, std::make_pair(right, connected_vertex)));
            }
        }
    }
    cout << path;
    return output;
};

#endif // GREEDYBFS_H
