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
#include "../UndirectedGraph.h"
#include "../DirectedGraph.h"

/**
 * DFS
 *
 * La búsqueda en profundidad (DFS) es un algoritmo para atravesar o buscar estructuras de datos 
 * de árboles o gráficos. El algoritmo comienza en el nodo raíz (seleccionando algún nodo arbitrario 
 * como nodo raíz en el caso de un gráfico) y explora lo más lejos posible a lo largo de cada 
 * rama antes de retroceder.
 *
 * Fuente: https://bit.ly/3C1sy3E
 */

/* Implementación */
/* Implementación */
template <typename VertexType, typename EdgeType>
UnDirectedGraph<VertexType, EdgeType> DFS(UnDirectedGraph<VertexType, EdgeType> *graph, std::string start_node)
{
  // Verificar si existen los dos vértices en el grafo
  if (graph->findById(start_node))
    std::logic_error("No se encontró el nodo incial. ");

  // Variable de salida (recorrdigo del DFS)
  UnDirectedGraph<VertexType, EdgeType> output;
  typedef Vertex<VertexType, EdgeType> vertex_t;
  typedef Edge<VertexType, EdgeType> edge_t;
  typedef std::pair<EdgeType, std::pair<vertex_t *, vertex_t *>> type_pair;

  std::unordered_map<std::string, bool> visited(graph->V);
  std::stack<type_pair> stack_vertexes;

  Vertex<VertexType, EdgeType> *start_vertex = graph->vertexes[start_node];
  Vertex<VertexType, EdgeType> *end_vertex = graph->vertexes[start_node];

  visited[start_vertex->id] = true;
  stack_vertexes.push(make_pair(0, std::make_pair(start_vertex, start_vertex)));

  while (!stack_vertexes.empty())
  {
    auto weight = stack_vertexes.top().first;
    auto *left = stack_vertexes.top().second.first;
    auto *right = stack_vertexes.top().second.second;
    stack_vertexes.pop();
    output.insertVertex(right->id, right->data);
    output.insertVertex(left->id, left->data);

    output.createEdge(left->id, right->id, weight);
    for (edge_t *&edge : right->edges)
    {
      auto *connected_vertex = edge->vertexes[1];
      if (!visited[connected_vertex->id])
      {
        visited[connected_vertex->id] = true;
        stack_vertexes.push(std::make_pair(edge->weight, std::make_pair(right, connected_vertex)));
      }
    }
  }
  return output;
};

template <typename VertexType, typename EdgeType>
DirectedGraph<VertexType, EdgeType> DFS(DirectedGraph<VertexType, EdgeType> *graph, std::string start_node)
{
  // Verificar si existen los dos vértices en el grafo
  if (graph->findById(start_node))
    std::logic_error("No se encontró el nodo incial. ");

  // Variable de salida (recorrdigo del DFS)
  DirectedGraph<VertexType, EdgeType> output;
  typedef Vertex<VertexType, EdgeType> vertex_t;
  typedef Edge<VertexType, EdgeType> edge_t;
  typedef std::pair<EdgeType, std::pair<vertex_t *, vertex_t *>> type_pair;

  std::unordered_map<std::string, bool> visited(graph->V);
  std::stack<type_pair> stack_vertexes;

  Vertex<VertexType, EdgeType> *start_vertex = graph->vertexes[start_node];
  Vertex<VertexType, EdgeType> *end_vertex = graph->vertexes[start_node];

  visited[start_vertex->id] = true;
  stack_vertexes.push(make_pair(0, std::make_pair(start_vertex, start_vertex)));

  while (!stack_vertexes.empty())
  {
    auto weight = stack_vertexes.top().first;
    auto *left = stack_vertexes.top().second.first;
    auto *right = stack_vertexes.top().second.second;
    stack_vertexes.pop();
    output.insertVertex(right->id, right->data);
    output.insertVertex(left->id, left->data);

    output.createEdge(left->id, right->id, weight);

    for (edge_t *&edge : right->edges)
    {
      auto *connected_vertex = edge->vertexes[1];
      if (!visited[connected_vertex->id])
      {
        visited[connected_vertex->id] = true;
        stack_vertexes.push(std::make_pair(edge->weight, std::make_pair(right, connected_vertex)));
      }
    }
  }
  return output;
};
#endif // GREEDYBFS_H
