/* 
    ___    ____   ____  __  _   _____ ______  ____    ____ 
    |   \  |    | |    ||  |/ ] / ___/|      ||    \  /    |
    |    \  |  |  |__  ||  ' / (   \_ |      ||  D  )|  o  |
    |  D  | |  |  __|  ||    \  \__  ||_|  |_||    / |     |
    |     | |  | /  |  ||     \ /  \ |  |  |  |    \ |  _  |
    |     | |  | \  `  ||  .  | \    |  |  |  |  .  \|  |  |
    |_____||____| \____||__|\_|  \___|  |__|  |__|\_||__|__|
                                                        
 */
#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include "../DirectedGraph.h"
#include "../UndirectedGraph.h"
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <functional>

#include "./data_structures/bst.h"

template <typename TV, typename TE>
DirectedGraph<TV, TE> dijkstra(DirectedGraph<TV, TE> &g, string start_node)
{
  unordered_map<string, TE> distancias;
  unordered_map<string, string> padres;
  unordered_set<string> visitados;
  BSTree<TE> heap;
  DirectedGraph<TV, TE> retorno;
  auto vts = g.vertexes;

  for (auto it = g.vertexes.begin(); it != g.vertexes.end(); ++it)
  {
    if (it->second->id == start_node)
    {
      distancias.insert({it->second->id, TE{0}});
      heap.insert(distance_pair<TE>{it->second->id, TE{0}});
    }
    else
    {
      distancias.insert({it->second->id, numeric_limits<TE>::max()});
      /* heap.insert(distance_pair<TE>{it->second->id,numeric_limits<TE>::max()}); */
    }
    retorno.insertVertex(it->second->id, it->second->data);
  }
  // visitados.size() != g.V
  while (true)
  {
    auto m = heap.minValue();
    visitados.insert(m.nodo);
    if (m.nodo != start_node)
    {
      retorno.createEdge(padres[m.nodo], m.nodo, distancias[m.nodo] - distancias[padres[m.nodo]]);
    }

    for (auto it = g.vertexes[m.nodo]->edges.begin(); it != g.vertexes[m.nodo]->edges.end(); ++it)
    {
      auto v2 = (*it)->vertexes[1];
      if (visitados.find(v2->id) == visitados.end() && distancias[v2->id] > (m.peso + (*it)->weight))
      {

        /* cout<<(*it)->vertexes[1]->id<<" "; */
        if (heap.find(distance_pair<TE>{v2->id, distancias[v2->id]}))
          heap.remove(distance_pair<TE>{v2->id, distancias[v2->id]});
        distancias[v2->id] = m.peso + (*it)->weight;
        padres[v2->id] = m.nodo;
        heap.insert(distance_pair<TE>{v2->id, distancias[v2->id]});
      }
    }
    /* cout<<endl; */
    /* cout<<m.nodo; */
    heap.remove(m);
    if (heap.size() == 0)
      break;
  }

  /* for(auto it = distancias.begin(); it != distancias.end();++it){ */
  /*   cout<<"{"<<it->first<<","<<it->second<<"}"<<" "; */
  /* } */

  return retorno;
}

template <typename TV, typename TE>
UnDirectedGraph<TV, TE> dijkstra(UnDirectedGraph<TV, TE> &g, string start_node)
{
  unordered_map<string, TE> distancias;
  unordered_map<string, string> padres;
  unordered_set<string> visitados;
  BSTree<TE> heap;
  UnDirectedGraph<TV, TE> retorno;
  auto vts = g.vertexes;

  for (auto it = g.vertexes.begin(); it != g.vertexes.end(); ++it)
  {
    if (it->second->id == start_node)
    {
      distancias.insert({it->second->id, TE{0}});
      heap.insert(distance_pair<TE>{it->second->id, TE{0}});
    }
    else
    {
      distancias.insert({it->second->id, numeric_limits<TE>::max()});
      /* heap.insert(distance_pair<TE>{it->second->id,numeric_limits<TE>::max()}); */
    }

    retorno.insertVertex(it->second->id, it->second->data);
  }

  // visitados.size() != g.V
  while (true)
  {
    auto m = heap.minValue();
    visitados.insert(m.nodo);
    if (m.nodo != start_node)
    {
      retorno.createEdge(padres[m.nodo], m.nodo, distancias[m.nodo] - distancias[padres[m.nodo]]);
    }

    for (auto it = g.vertexes[m.nodo]->edges.begin(); it != g.vertexes[m.nodo]->edges.end(); ++it)
    {
      auto v2 = (*it)->vertexes[1];
      if (visitados.find(v2->id) == visitados.end() && distancias[v2->id] > (m.peso + (*it)->weight))
      {

        if (heap.find(distance_pair<TE>{v2->id, distancias[v2->id]}))
          heap.remove(distance_pair<TE>{v2->id, distancias[v2->id]});
        distancias[v2->id] = m.peso + (*it)->weight;
        padres[v2->id] = m.nodo;
        heap.insert(distance_pair<TE>{v2->id, distancias[v2->id]});
      }
    }
    heap.remove(m);
    if (heap.size() == 0)
      break;
  }

  /*   for(auto it = distancias.begin(); it != distancias.end();++it){ */
  /*     cout<<"{"<<it->first<<","<<it->second<<"}"<<" "; */
  /*   } */
  /*   cout<<endl; */

  return retorno;
}

#endif
