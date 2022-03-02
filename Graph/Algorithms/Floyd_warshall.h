#ifndef FLOYD_WARSHALL_H
#define FLOYD_WARSHALL_H
#include "../DirectedGraph.h"
#include "../UndirectedGraph.h"
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <set>
#include <functional>

template <typename TE>
struct matrix_square_pair
{

  set<string> indexes;
  unordered_map<string, unordered_map<string, pair<string, TE>>> matrix;
  void display_a()
  {
    for (auto it = indexes.begin(); it != indexes.end(); ++it)
    {
      cout << *it << ":";
      for (auto it2 = indexes.begin(); it2 != indexes.end(); ++it2)
      {
        cout << "{" << *it2 << "," << matrix[*it][*it2].first << "}"
             << " ";
      }
      cout << endl;
    }
  }
  void display_b()
  {
    for (auto it = indexes.begin(); it != indexes.end(); ++it)
    {
      cout << *it << ":";
      for (auto it2 = indexes.begin(); it2 != indexes.end(); ++it2)
      {
        if (matrix[*it][*it2].second == numeric_limits<TE>::max())
          cout << "{" << *it2 << ",inf}";
        else
          cout << "{" << *it2 << "," << matrix[*it][*it2].second << "}";
        cout << " ";
      }
      cout << endl;
    }
  }
  unordered_map<string, pair<string, TE>> &operator[](string in)
  {
    return matrix[in];
  }
  void insert_index(string in)
  {
    indexes.insert(in);
  }
  set<string> &indexes_()
  {
    return indexes;
  }
};

template <typename TV, typename TE>
matrix_square_pair<TE> floyd_warshall(DirectedGraph<TV, TE> &g)
{
  matrix_square_pair<TE> dyp;

  for (auto it = g.vertexes.begin(); it != g.vertexes.end(); ++it)
  {
    dyp.insert_index(it->first);
    for (auto it2 = g.vertexes.begin(); it2 != g.vertexes.end(); ++it2)
    {
      if (it->first == it2->first)
      {
        dyp[it->first][it2->first].second = 0;
        dyp[it->first][it2->first].first = it->first;
      }
      else
      {
        dyp[it->first][it2->first].second = numeric_limits<TE>::max();
        dyp[it->first][it2->first].first = "";
      }
    }
  }

  for (auto it = g.vertexes.begin(); it != g.vertexes.end(); ++it)
  {
    for (auto it2 = it->second->edges.begin(); it2 != it->second->edges.end(); ++it2)
    {
      dyp[it->first][(*it2)->vertexes[1]->id].second = (*it2)->weight;
      dyp[it->first][(*it2)->vertexes[1]->id].first = (*it2)->vertexes[1]->id;
    }
  }

  for (auto it = dyp.indexes_().begin(); it != dyp.indexes_().end(); ++it)
  {
    for (auto it2 = dyp.indexes_().begin(); it2 != dyp.indexes_().end(); ++it2)
    {
      for (auto it3 = dyp.indexes_().begin(); it3 != dyp.indexes_().end(); ++it3)
      {

        if (dyp[*it2][*it].second != numeric_limits<TE>::max() &&
            dyp[*it][*it3].second != numeric_limits<TE>::max())
        {

          if (dyp[*it2][*it3].second == numeric_limits<TE>::max() ||
              (dyp[*it2][*it3].second > dyp[*it2][*it].second + dyp[*it][*it3].second))
          {
            dyp[*it2][*it3].second = dyp[*it2][*it].second + dyp[*it][*it3].second;
            dyp[*it2][*it3].first = *it;
          }
        }
      }
    }
  }

  return dyp;
}

template <typename TV, typename TE>
matrix_square_pair<TE> floyd_warshall(UnDirectedGraph<TV, TE> &g)
{
  matrix_square_pair<TE> dyp;

  for (auto it = g.vertexes.begin(); it != g.vertexes.end(); ++it)
  {
    dyp.insert_index(it->first);
    for (auto it2 = g.vertexes.begin(); it2 != g.vertexes.end(); ++it2)
    {
      if (it->first == it2->first)
      {
        dyp[it->first][it2->first].second = 0;
        dyp[it->first][it2->first].first = it->first;
      }
      else
      {
        dyp[it->first][it2->first].second = numeric_limits<TE>::max();
        dyp[it->first][it2->first].first = "";
      }
    }
  }

  for (auto it = dyp.indexes_().begin(); it != dyp.indexes_().end(); ++it)
  {
    for (auto it2 = g.vertexes[*it]->edges.begin(); it2 != g.vertexes[*it]->edges.end(); ++it2)
    {
      if (dyp[*it][(*it2)->vertexes[1]->id].second == numeric_limits<TE>::max())
      {
        dyp[(*it2)->vertexes[1]->id][*it].second = (*it2)->weight;
        dyp[*it][(*it2)->vertexes[1]->id].second = (*it2)->weight;
        dyp[*it][(*it2)->vertexes[1]->id].first = (*it2)->vertexes[1]->id;
        dyp[(*it2)->vertexes[1]->id][*it].first = *it;
      }
    }
  }

  for (auto it = dyp.indexes_().begin(); it != dyp.indexes_().end(); ++it)
  {
    /* cout<<*it<<endl; */
    for (auto it2 = dyp.indexes_().begin(); it2 != dyp.indexes_().end(); ++it2)
    {
      for (auto it3 = dyp.indexes_().begin(); it3 != dyp.indexes_().end(); ++it3)
      {

        if (dyp[*it2][*it].second != numeric_limits<TE>::max() &&
            dyp[*it][*it3].second != numeric_limits<TE>::max())
        {

          if (dyp[*it2][*it3].second == numeric_limits<TE>::max() ||
              (dyp[*it2][*it3].second > dyp[*it2][*it].second + dyp[*it][*it3].second))
          {
            dyp[*it2][*it3].second = dyp[*it2][*it].second + dyp[*it][*it3].second;
            dyp[*it2][*it3].first = *it;
            dyp[*it3][*it2].second = dyp[*it2][*it].second + dyp[*it][*it3].second;
            dyp[*it3][*it2].first = *it;
          }
        }
      }
    }
  }

  return dyp;
}

#endif
