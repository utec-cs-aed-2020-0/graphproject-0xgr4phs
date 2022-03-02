#ifndef NODE_H
#define NODE_H
#include <iostream>

using namespace std;

template <typename TE>
struct distance_pair
{
  string nodo;
  TE peso;

  bool operator==(distance_pair<TE> otro)
  {
    return nodo == otro.nodo && peso == otro.peso;
  }

  bool operator!=(distance_pair<TE> otro)
  {
    return nodo != otro.nodo || peso != otro.peso;
  }
  bool operator<(distance_pair<TE> otro)
  {

    return peso == otro.peso ? nodo < otro.nodo : peso < otro.peso;
  }
  bool operator>(distance_pair<TE> otro)
  {

    return peso == otro.peso ? nodo > otro.nodo : peso > otro.peso;
  }
};

template <typename TE>
struct NodeBT
{
  distance_pair<TE> par;
  NodeBT *left;
  NodeBT *right;

  NodeBT() : par{}, left{nullptr}, right{nullptr} {}
  NodeBT(distance_pair<TE> par) : par{par}, left{nullptr}, right{nullptr} {}
  void KillSelf()
  {
    delete this;
  }
};

#endif
