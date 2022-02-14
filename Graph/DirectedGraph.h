#ifndef DIRECTEDGRAPH_H
#define DIRECTEDGRAPH_H

#include "graph.h"
#include <iostream>
#include <algorithm>
#include <queue>
#include <unordered_set>
#include <deque>
#include "./Algorithms/data_estructures/bst.h"
using namespace std;


template<typename TV, typename TE>
class DirectedGraph;

template<typename TV,typename TE>
deque<distance_pair<TE>> astar(DirectedGraph<TV,TE> & gr,unordered_map<string,TE> & h ,string start_node,string end_node);

template<typename TV,typename TE>
DirectedGraph<TV,TE> dijkstra(DirectedGraph<TV,TE> & , string);

template<typename TV, typename TE>
class DirectedGraph : public Graph<TV, TE> {
  template<typename T,typename E> 
    friend DirectedGraph<T, E> dijkstra(DirectedGraph<T,E>&,string);
  template<typename T,typename E> 
    friend  deque<distance_pair<E>> astar(DirectedGraph<T,E> & ,unordered_map<string,E> & , string ,string );

  private:
  int E{};
  int V{};
  public:
  DirectedGraph() = default;
  DirectedGraph(const unordered_map<string, Vertex < TV, TE> *> & vertexes){
    this->vertexes = vertexes;
  }
  ~DirectedGraph() {clear();}

  bool insertVertex(string id, TV vertex) override{
    if(this->vertexes.find(id) != this->vertexes.end()) return false;

    this->vertexes[id] = new Vertex<TV,TE>{id,vertex,std::list<Edge<TV,TE>*>{}};

    ++V;
    return true;
  }

  bool createEdge(string id1, string id2, TE w) override{
    if(this->vertexes.find(id1) == this->vertexes.end()  || 
	this->vertexes.find(id2) == this->vertexes.end()) return false; 
    auto v1 = this->vertexes[id1];
    auto v2 = this->vertexes[id2];

    for(auto it = v1->edges.begin(); it != v1->edges.end();++it){
      if((*it)->vertexes[1] == v2) return false;
    }

    v1->edges.push_front(new Edge<TV,TE>{{v1,v2},w});

    ++E;
    return true;

  }

  bool deleteVertex(string id) override{
    if(this->vertexes.find(id) == this->vertexes.end()) return false;
    auto v = this->vertexes[id];
    for(auto it = v->edges.begin(); it != v->edges.end();++it){

      delete *it;
      --E;}
    v->edges.clear();

    for(auto it = this->vertexes.begin();it != this->vertexes.end();++it)
      if(it->first != id)
	deleteEdge(it->first,id);



    delete this->vertexes[id];
    this->vertexes.erase(id);

    --V;

    return true;
  }

  bool deleteEdge(string id1,string id2) override{
    if(this->vertexes.find(id1) == this->vertexes.end()  || 
	this->vertexes.find(id2) == this->vertexes.end()) return false; 

    auto inicio = this->vertexes[id1];
    auto llegada = this->vertexes[id2];


    for(auto it = inicio->edges.begin();it!= inicio->edges.end();++it){
      if((*it)->vertexes[1] == llegada){
	delete *it;
	inicio->edges.erase(it);
	--E;
	return true;
      }

    }


    return false;
  }

  TE &operator()(string start, string end) override{

    if(this->vertexes.find(start) == this->vertexes.end()  || 
	this->vertexes.find(end) == this->vertexes.end()) throw "No se encuentra uno o ambos vertices"; 
    auto inicio = this->vertexes[start];
    auto llegada = this->vertexes[end];


    for(auto it = inicio->edges.begin();it!= inicio->edges.end();++it){
      if((*it)->vertexes[1] == llegada) return (*it)->weight;

    }

    throw "No se encuentra la arista";

  }

  float density() override{
    return E / (V*(V-1));

  }

  bool isDense(float threshold) override{
    return density() >= threshold;
  }

  bool isConnected() throw() override{

    throw "No puedes llamar a esta funcion";
    return false;
  }

  bool isStronglyConnected() throw() override{

    unordered_set<string> visitados;
    queue<string> ayuda;



    for(auto it= this->vertexes.begin(); it != this->vertexes.end();++it){
      auto v = it->second;

      ayuda.push(v->id);
      visitados.insert(v->id);
      while(!ayuda.empty()){
	auto temp = ayuda.front();
	ayuda.pop();

	for(auto it = this->vertexes[temp]->edges.begin();it != this->vertexes[temp]->edges.end();++it){
	  auto a_insertar = (*it)->vertexes[1]->id;
	  if(visitados.find(a_insertar) == visitados.end()){

	    ayuda.push(a_insertar);
	    visitados.insert(a_insertar);
	  }

	}

      }

      if(visitados.size() != V) return false;

      visitados.clear();

    }

    return true;
  }

  bool empty() override{
    return V == 0;
  }

  void clear() override{

    while(this->vertexes.size() != 0){

      deleteVertex(this->vertexes.begin()->first);

    }

    /* for(auto it_p = this->vertexes.begin();it_p != this->vertexes.end();++it_p){ */
    /* auto v = it_p->second; */
    /* for(auto it = v->edges.begin(); it != v->edges.end();++it) */
    /* delete *it; */
    /* v->edges.clear(); */


    /* delete it_p->second; */

    /* } */


    /* this->vertexes.clear(); */

  }

  void displayVertex(string id) override{

    if(this->vertexes.find(id) == this->vertexes.end()) throw "No se encuentra ese vertice";
    auto v = this->vertexes[id];
    cout<<"Las aristas de "<<v->id<<" son: ";
    for(auto it = v->edges.begin(); it != v->edges.end();++it){
      cout<<"({"<<(*it)->vertexes[0]->id<<","<<(*it)->vertexes[1]->id<<"}, w: "<<(*it)->weight<<") ";
    }
    cout<<endl;

  }

  bool findById(string id) override{
    return this->vertexes.find(id) != this->vertexes.end();
  }

  void display() override{
    vector<string> keys;


    for(auto it = this->vertexes.begin();it != this->vertexes.end();++it){
      keys.push_back(it->first);

    }

    sort(keys.begin(),keys.end());
    for(auto&i: keys){
      auto v = this->vertexes[i];
      cout<<"Las aristas de "<<v->id<<" son: ";
      for(auto it = v->edges.begin(); it != v->edges.end();++it){
	cout<<"({"<<(*it)->vertexes[0]->id<<","<<(*it)->vertexes[1]->id<<"}, w: "<<(*it)->weight<<") ";
      }
      cout<<endl;
    }




  }
};







#endif
