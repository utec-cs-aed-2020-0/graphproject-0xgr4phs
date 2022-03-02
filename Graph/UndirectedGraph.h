//
//        /$$   /$$                 /$$ /$$                                 /$$                     /$$  /$$$$$$                               /$$           /$$
//        | $$  | $$                | $$|__/                                | $$                    | $$ /$$__  $$                             | $$          | $$
//        | $$  | $$ /$$$$$$$   /$$$$$$$ /$$  /$$$$$$   /$$$$$$   /$$$$$$$ /$$$$$$    /$$$$$$   /$$$$$$$| $$  \__/  /$$$$$$  /$$$$$$   /$$$$$$ | $$$$$$$     | $$$$$$$
//        | $$  | $$| $$__  $$ /$$__  $$| $$ /$$__  $$ /$$__  $$ /$$_____/|_  $$_/   /$$__  $$ /$$__  $$| $$ /$$$$ /$$__  $$|____  $$ /$$__  $$| $$__  $$    | $$__  $$
//        | $$  | $$| $$  \ $$| $$  | $$| $$| $$  \__/| $$$$$$$$| $$        | $$    | $$$$$$$$| $$  | $$| $$|_  $$| $$  \__/ /$$$$$$$| $$  \ $$| $$  \ $$    | $$  \ $$
//        | $$  | $$| $$  | $$| $$  | $$| $$| $$      | $$_____/| $$        | $$ /$$| $$_____/| $$  | $$| $$  \ $$| $$      /$$__  $$| $$  | $$| $$  | $$    | $$  | $$
//        |  $$$$$$/| $$  | $$|  $$$$$$$| $$| $$      |  $$$$$$$|  $$$$$$$  |  $$$$/|  $$$$$$$|  $$$$$$$|  $$$$$$/| $$     |  $$$$$$$| $$$$$$$/| $$  | $$ /$$| $$  | $$
//        \______/ |__/  |__/ \_______/|__/|__/       \_______/ \_______/   \___/   \_______/ \_______/ \______/ |__/      \_______/| $$____/ |__/  |__/|__/|__/  |__/
//                                                                                                                                    | $$
//                                                                                                                                    | $$
//                                                                                                                                    |__/

#ifndef UNDIRECTEDGRAPH_H
#define UNDIRECTEDGRAPH_H

#include <string>
#include <queue>
#include <unordered_set>
#include <algorithm>
#include "Graph.h"
#include "./Algorithms/data_structures/bst.h"

/* Declaraciones de clases y funciones */

template <typename TV, typename TE>
class UnDirectedGraph;

// Funciones auxiliares
template <typename VertexType, typename EdgeType>
UnDirectedGraph<VertexType, EdgeType> DFS(UnDirectedGraph<VertexType, EdgeType> *graph, std::string start_node);

template <typename VertexType, typename EdgeType>
UnDirectedGraph<VertexType, EdgeType> greedyBFS(UnDirectedGraph<VertexType, EdgeType> *graph, std::string start_node, std::string end_node);

template <typename TV, typename TE>
UnDirectedGraph<TV, TE> dijkstra(UnDirectedGraph<TV, TE> &, string);

template <typename TV, typename TE>
deque<distance_pair<TE>> astar(UnDirectedGraph<TV, TE> &gr, unordered_map<string, TE> &h, string start_node, string end_node);

template <typename TE>
struct matrix_square_pair;

template <typename TV, typename TE>
matrix_square_pair<TE> floyd_warshall(UnDirectedGraph<TV, TE> &g);

template <typename TV, typename TE>
UnDirectedGraph<TV, TE> bellman_ford(UnDirectedGraph<TV, TE> grafo, const string &nodoInicio);
template <typename TV, typename TE>
UnDirectedGraph<TV, TE> kruskal(UnDirectedGraph<TV, TE> grafo);
class DisjointSetGrafoDirigido;
class DisjointSetGrafoNoDirigido;
template <typename TV, typename TE>
UnDirectedGraph<TV, TE> prim(UnDirectedGraph<TV, TE> grafo, string inicio);

template <typename TV, typename TE>
class UnDirectedGraph : public Graph<TV, TE>
{
public:
  UnDirectedGraph() = default;

  bool insertVertex(std::string id, TV vertex) override;

  bool createEdge(std::string id1, std::string id2, TE w) override;

  bool deleteVertex(std::string id) override;

  bool deleteEdge(std::string start, std::string end) override;

  TE &operator()(std::string start, std::string end) override;

  float density() override;

  bool isDense(float threshold) override;

  bool isConnected() override;

  bool isStronglyConnected() noexcept override;

  bool empty() override;

  void clear() override;

  void displayVertex(std::string id) override;

  bool findById(std::string id) override;

  void display() override;

private:
  /* Declaración de funciones amigas */
  template <typename T, typename E>
  friend UnDirectedGraph<T, E> dijkstra(UnDirectedGraph<T, E> &, string);

  template <typename T, typename E>
  friend deque<distance_pair<E>> astar(UnDirectedGraph<T, E> &gr, unordered_map<string, E> &h, string start_node, string end_node);

  template <typename T, typename E>
  friend matrix_square_pair<E> floyd_warshall(UnDirectedGraph<T, E> &g);

  template <typename TVf, typename TEf>
  friend UnDirectedGraph<TVf, TEf> bellman_ford(UnDirectedGraph<TVf, TEf> grafo, const string &nodoInicio);
  template <typename TVf, typename TEf>
  friend UnDirectedGraph<TVf, TEf> kruskal(UnDirectedGraph<TVf, TEf> grafo);
  friend class DisjointSetGrafoDirigido;
  friend class DisjointSetGrafoNoDirigido;
  template <typename TVf, typename TEf>
  friend UnDirectedGraph<TVf, TEf> prim(UnDirectedGraph<TVf, TEf> grafo, string inicio);

  template <typename VertexType, typename EdgeType>
  friend UnDirectedGraph<VertexType, EdgeType> greedyBFS(UnDirectedGraph<VertexType, EdgeType> *graph, std::string start_node, std::string end_node);

  template <typename VertexType, typename EdgeType>
  friend UnDirectedGraph<VertexType, EdgeType> DFS(UnDirectedGraph<VertexType, EdgeType> *graph, std::string start_node);
};

template <typename TV, typename TE>
bool UnDirectedGraph<TV, TE>::insertVertex(std::string id, TV vertex)
{
  // Verify if vertex exists
  if (this->vertexes.find(id) != this->vertexes.end())
    return false;
  this->vertexes[id] = new Vertex<TV, TE>{id, vertex, std::list<Edge<TV, TE> *>{}};
  this->V++;

  return true;
}

template <typename TV, typename TE>
bool UnDirectedGraph<TV, TE>::createEdge(std::string id1, std::string id2, TE w)
{
  // Verify if edge exists
  if (this->vertexes.find(id1) == this->vertexes.end() || this->vertexes.find(id2) == this->vertexes.end())
    return false;

  auto v1 = this->vertexes[id1];
  auto v2 = this->vertexes[id2];

  for (auto it = v1->edges.begin(); it != v1->edges.end(); ++it)
  {
    if ((*it)->vertexes[1] == v2)
      return false;
  }

  auto edge1 = new Edge<TV, TE>{{v1, v2}, w};
  auto edge2 = new Edge<TV, TE>{{v2, v1}, w};
  v1->edges.push_front(edge1);
  v2->edges.push_front(edge2);

  this->E++;

  return true;
}

template <typename TV, typename TE>
bool UnDirectedGraph<TV, TE>::deleteVertex(std::string id)
{
  if (this->vertexes.find(id) == this->vertexes.end())
    return false;

  auto v = this->vertexes[id];
  while (v->edges.size() != 0)
  {
    deleteEdge((*(v->edges.begin()))->vertexes[0]->id, (*(v->edges.begin()))->vertexes[1]->id);
  }

  delete this->vertexes[id];
  this->vertexes.erase(id);
  --this->V;

  return true;
}

template <typename TV, typename TE>
bool UnDirectedGraph<TV, TE>::deleteEdge(std::string start, std::string end)
{
  if (this->vertexes.find(start) == this->vertexes.end() ||
      this->vertexes.find(end) == this->vertexes.end())
    return false;

  auto inicio = this->vertexes[start];
  auto llegada = this->vertexes[end];

  for (auto it = inicio->edges.begin(); it != inicio->edges.end(); ++it)
  {
    if ((*it)->vertexes[1] == llegada)
    {
      inicio->edges.erase(it);
      delete *it;
      break;
    }
  }

  for (auto it = llegada->edges.begin(); it != llegada->edges.end(); ++it)
  {
    if ((*it)->vertexes[1] == inicio)
    {
      llegada->edges.erase(it);
      --this->E;
      delete *it;
      return true;
    }
  }
  return false;
}

template <typename TV, typename TE>
TE &UnDirectedGraph<TV, TE>::operator()(std::string start, std::string end)
{
  if (this->vertexes.find(start) == this->vertexes.end() ||
      this->vertexes.find(end) == this->vertexes.end())
    throw std::runtime_error("No se encuentra uno o ambos vertices");

  auto inicio = this->vertexes[start];
  auto llegada = this->vertexes[end];

  for (auto it = inicio->edges.begin(); it != inicio->edges.end(); ++it)
  {
    if ((*it)->vertexes[1] == llegada)
      return (*it)->weight;
  }

  throw std::runtime_error("No se encuentra la arista");
}

template <typename TV, typename TE>
float UnDirectedGraph<TV, TE>::density()
{
  return (2 * this->E) / (this->V * (this->V - 1));
}

template <typename TV, typename TE>
bool UnDirectedGraph<TV, TE>::isDense(float threshold)
{
  return density() >= threshold;
}

template <typename TV, typename TE>
bool UnDirectedGraph<TV, TE>::isConnected()
{

  std::unordered_set<std::string> visitados;
  std::queue<std::string> ayuda;

  ayuda.push(this->vertexes.begin()->first);
  visitados.insert(this->vertexes.begin()->first);

  while (!ayuda.empty())
  {
    auto actual = ayuda.front();
    ayuda.pop();
    for (auto it = this->vertexes[actual]->edges.begin(); it != this->vertexes[actual]->edges.end(); ++it)
    {
      auto v = (*it)->vertexes[1]->id;
      if (visitados.find(v) == visitados.end())
      {
        ayuda.push(v);
        visitados.insert(v);
      }
    }
  }

  return visitados.size() == this->V;
}

template <typename TV, typename TE>
bool UnDirectedGraph<TV, TE>::isStronglyConnected() noexcept
{
  return false;
}

template <typename TV, typename TE>
bool UnDirectedGraph<TV, TE>::empty()
{
  return this->V == 0;
}

template <typename TV, typename TE>
void UnDirectedGraph<TV, TE>::clear()
{
  while (this->vertexes.size() != 0)
  {
    deleteVertex(this->vertexes.begin()->first);
  }
}

template <typename TV, typename TE>
void UnDirectedGraph<TV, TE>::displayVertex(std::string id)
{
  if (this->vertexes.find(id) == this->vertexes.end())
    throw std::runtime_error("No se encuentra ese vertice");

  auto v = this->vertexes[id];
  std::cout << "Las aristas de " << v->id << " son: ";

  for (auto it = v->edges.begin(); it != v->edges.end(); ++it)
  {
    std::cout << "({" << (*it)->vertexes[0]->id << "," << (*it)->vertexes[1]->id << "}, w: " << (*it)->weight
              << ") ";
  }
  std::cout << "\n";
}

template <typename TV, typename TE>
bool UnDirectedGraph<TV, TE>::findById(std::string id)
{
  return this->vertexes.find(id) != this->vertexes.end();
}

template <typename TV, typename TE>
void UnDirectedGraph<TV, TE>::display()
{
  vector<string> keys;
  for (auto it = this->vertexes.begin(); it != this->vertexes.end(); ++it)
  {
    keys.push_back(it->first);
  }

  sort(keys.begin(), keys.end());

  for (auto &i : keys)
  {
    auto v = this->vertexes[i];
    cout << "Las aristas de " << v->id << " son: ";
    for (auto it = v->edges.begin(); it != v->edges.end(); ++it)
    {
      cout << "({" << (*it)->vertexes[0]->id << "," << (*it)->vertexes[1]->id << "}, w: " << (*it)->weight << ") ";
    }
    cout << endl;
  }
}

#endif // UNDIRECTEDGRAPH_H
