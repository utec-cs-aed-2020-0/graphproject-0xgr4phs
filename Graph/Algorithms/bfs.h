
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

#ifndef GREEDY_BFS_H
#define GREEDY_BFS_H

/* Depedencias */
#include <iostream>
#include <queue>

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

template <typename TV, typename TE>
DirectedGraph<TV,TE> greedyBFS(DirectedGraph<TV,TE> graph, std::string start_node, std::string end_node);

template <typename TV, typename TE>
UnDirectedGraph<TV,TE> greedyBFS(UnDirectedGraph<TV,TE> graph, std::string start_node, std::string end_node);

/* Para un grafo dirigido */

template <typename TV, typename TE>
DirectedGraph<TV,TE> greedyBFS(DirectedGraph<TV,TE> graph, std::string start_node, std::string end_node) {
    std::string travel = "";
    if (graph->findById(start_node) && graph->findById(end_node)) logic_error("Los nodos parámetros no funcionan correctamente.");

    // Para simplificar el código
    typedef pair<std::string, Vertex<TV,TE>*> type_pair;
    std::unordered_map<std::string, bool> visited(graph->V);

    std::priority_queue<type_pair, std::vector<type_pair>, greater<type_pair>> pq;

    Vertex<TV,TE> *start_vertex = graph->vertexes[start_node];
    Vertex<TV,TE> *end_vertex= graph->vertexes[end_node];
    visited[start_vertex->id] = true;
    pq.push(make_pair(start_vertex->id,start_vertex->data));
    while (pq.empty()) {
        std::string id = pq.top().first;
        TV data = pq.top().second;
        travel += std::to_string(data) + " ";
        Vertex<TV,TE> *current_vertex = graph->vertexes[id];
        for (Edge<TV,TE> &edge : current_vertex->edges) {
            Vertex<TV,TE> *connectedVertex = edge->vertexes[1];
            if (!visited[connectedVertex->id]) {
                visited[connectedVertex->id] = true;
                pq.push(make_pair(connectedVertex->id, connectedVertex->data));
            }
        }
    }

};

/* Para un grafo no dirigido */

template <typename TV, typename TE>
UnDirectedGraph<TV,TE> greedyBFS(UnDirectedGraph<TV,TE> graph, std::string start_node, std::string end_node) {
   std::string travel = "";
    if (graph->findById(start_node) && graph->findById(end_node)) logic_error("Los nodos parámetros no funcionan correctamente.");

    // Para simplificar el código
    typedef pair<std::string, Vertex<TV,TE>*> type_pair;
    std::unordered_map<std::string, bool> visited(graph->V);

    std::priority_queue<type_pair, std::vector<type_pair>, greater<type_pair>> pq;

    Vertex<TV,TE> *start_vertex = graph->vertexes[start_node];
    Vertex<TV,TE> *end_vertex= graph->vertexes[end_node];
    visited[start_vertex->id] = true;
    pq.push(make_pair(start_vertex->id,start_vertex->data));
    while (pq.empty()) {
        std::string id = pq.top().first;
        TV data = pq.top().second;
        travel += std::to_string(data) + " ";
        Vertex<TV,TE> *current_vertex = graph->vertexes[id];
        for (Edge<TV,TE> &edge : current_vertex->edges) {
            Vertex<TV,TE> *connectedVertex = edge->vertexes[1];
            if (!visited[connectedVertex->id]) {
                visited[connectedVertex->id] = true;
                pq.push(make_pair(connectedVertex->id, connectedVertex->data));
            }
        }
    } 
};

// TODO: Testear y corregir en tiempo de compilación

#endif // GREEDY_BFS_H
