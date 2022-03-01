#ifndef UNDIRECTEDGRAPH_H
#define UNDIRECTEDGRAPH_H

#include <string>
#include "graph.h"
#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_set>
#include "./Algorithms/data_estructures/bst.h"


using namespace std;



template<typename TV, typename TE>
class UnDirectedGraph;

template<typename TV,typename TE>
UnDirectedGraph<TV,TE> dijkstra(UnDirectedGraph<TV,TE> & , string);

template<typename TV,typename TE>
deque<distance_pair<TE>> astar(UnDirectedGraph<TV,TE> & gr,unordered_map<string,TE> & h ,string start_node,string end_node);

template<typename TE>
struct matrix_square_pair;

template<typename TV,typename TE>
matrix_square_pair<TE> floyd_warshall(UnDirectedGraph<TV,TE> & g);

template<typename TV, typename TE>
DirectedGraph<TV, TE> bellman_ford(const DirectedGraph<TV, TE> &grafo, const string &nodoInicio);
template<typename TV,typename TE>
DirectedGraph<TV, TE> kruskal(const DirectedGraph<TV, TE> &grafo);
class DisjointSetGrafo;



template<typename TV, typename TE>
class UnDirectedGraph : public Graph<TV, TE>{
  template<typename T,typename E>
    friend UnDirectedGraph<T, E> dijkstra(UnDirectedGraph<T,E>&,string);


  template<typename T,typename E>
    friend deque<distance_pair<E>> astar(UnDirectedGraph<T,E> & gr,unordered_map<string,E> & h ,string start_node,string end_node);

  template<typename T,typename E>
    friend matrix_square_pair<E> floyd_warshall(UnDirectedGraph<T,E> & g);

    friend UnDirectedGraph<TV, TE> bellman_ford(const UnDirectedGraph<TV, TE> &grafo, const string &nodoInicio);
    friend UnDirectedGraph<TV, TE> kruskal(const UnDirectedGraph<TV, TE> &grafo);
    friend class DisjointSetGrafo;

  private:
  int E{};
  int V{};
  public:

  UnDirectedGraph() = default;
  UnDirectedGraph(const unordered_map<string, Vertex < TV, TE> *> & vertexes){
    this->vertexes = vertexes;
  }
  ~UnDirectedGraph() {clear();}



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

    auto e = new Edge<TV,TE>{{v1,v2},w};
    auto e2 = new Edge<TV,TE>{{v2,v1},w};
    v1->edges.push_front(e);
    v2->edges.push_front(e2);

    ++E;
    return true;


  }

  bool deleteVertex(string id) override{
    if(this->vertexes.find(id) == this->vertexes.end()) return false;
    auto v = this->vertexes[id];

    while(v->edges.size() != 0){

      deleteEdge((*(v->edges.begin()))->vertexes[0]->id,(*(v->edges.begin()))->vertexes[1]->id);
    }

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
	inicio->edges.erase(it);
	delete *it;
	break;
      }

    }
    for(auto it = llegada->edges.begin();it!= llegada->edges.end();++it){
      //cout<<(*it)->vertexes[0]->id<<" "<<(*it)->vertexes[1]->id<<endl;
      if((*it)->vertexes[1] == inicio){
	llegada->edges.erase(it);
	--E;
	delete *it;
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
      if((*it)->vertexes[1] == llegada) 
	return (*it)->weight;

    }

    throw "No se encuentra la arista";

  }

  float density() override{
    return (2*E)/(V*(V-1));
  }

  bool isDense(float threshold) override{
    return density() >= threshold;
  }

  bool isConnected() throw() override{
    unordered_set<string> visitados;

    queue<string> ayuda;
    ayuda.push(this->vertexes.begin()->first);
    visitados.insert(this->vertexes.begin()->first);

    while(!ayuda.empty()){
      auto actual = ayuda.front();
      ayuda.pop();

      for(auto it = this->vertexes[actual]->edges.begin();it!= this->vertexes[actual]->edges.end();++it){
	auto v = (*it)->vertexes[1]->id;
	if(visitados.find(v) == visitados.end()){
	  ayuda.push(v);
	  visitados.insert(v);
	}

      }


    }

    return visitados.size() == V;

  }

  bool isStronglyConnected() throw() override{
    throw "No puedes llamar a esta funcion";

    return false;

  }
  bool empty() override{
    return V == 0;
  }

  void clear() override{

    while(this->vertexes.size() != 0){

      deleteVertex(this->vertexes.begin()->first);

    }

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
