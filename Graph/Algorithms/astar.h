#ifndef ASTAR_H
#define ASTAR_H
#include "../DirectedGraph.h"
#include "../UndirectedGraph.h"
#include <unordered_map>
#include <unordered_set>
#include <deque>
#include <functional>
#include "../Algorithms/data_estructures/bst.h"

template<typename TV,typename TE>
deque<distance_pair<TE>> astar(DirectedGraph<TV,TE> & gr,unordered_map<string,TE> & h ,string start_node,string end_node){
  unordered_map<string,TE> f;
  unordered_map<string,distance_pair<TE>> padres;
  unordered_set<string> closed_set;
  BSTree<TE> open_set;
  deque<distance_pair<TE>> retorno;

  for(auto it = gr.vertexes.begin();it != gr.vertexes.end();++it){
    if(it->second->id == start_node){ 
      f.insert({it->second->id,TE{0} +  h[it->second->id]});
      open_set.insert(distance_pair<TE>{it->second->id,TE{0} +  h[it->second->id]});
    }
    else{ 
      f.insert({it->second->id,numeric_limits<TE>::max()});
    }
  }

  
  while(true){
    auto m = open_set.minValue();
    closed_set.insert(m.nodo);
    

    if(m.nodo == end_node){
      retorno.push_back(distance_pair<TE>{m.nodo,f[m.nodo] - h[m.nodo] });
      break;

    }
    for(auto it = gr.vertexes[m.nodo]->edges.begin(); it != gr.vertexes[m.nodo]->edges.end(); ++it){
      auto v2 = (*it)->vertexes[0]->id == m.nodo ? (*it)->vertexes[1] : (*it)->vertexes[0];

      if(closed_set.find(v2->id) == closed_set.end() &&( f[v2->id] == numeric_limits<TE>::max()|| 
	    f[v2->id] - h[v2->id] > (f[m.nodo] - h[m.nodo] +(*it)->weight))){

	auto eliminar = distance_pair<TE>{v2->id,f[v2->id]};
	if(open_set.find(eliminar))
	  open_set.remove(eliminar);
	f[v2->id] = f[m.nodo]  - h[m.nodo] + (*it)->weight + h[v2->id];
	padres[v2->id] = m;
	open_set.insert(distance_pair<TE>{v2->id,f[v2->id]});
      }
    }



    open_set.remove(m);
    if(open_set.size() == 0){
      return deque<distance_pair<TE>>{};

    }
  }



  auto temp = end_node;
  while(true){
    auto m = padres[temp];

    if(m.nodo == start_node){
      retorno.push_front(distance_pair<TE>{m.nodo,0});
      break;
    }


    retorno.push_front(distance_pair<TE>{m.nodo,f[m.nodo] - h[m.nodo] });
    temp = m.nodo;
  }


  return retorno;
}

template<typename TV,typename TE>
deque<distance_pair<TE>> astar(UnDirectedGraph<TV,TE> & gr,unordered_map<string,TE> & h ,string start_node,string end_node){
  unordered_map<string,TE> f;
  unordered_map<string,distance_pair<TE>> padres;
  unordered_set<string> closed_set;
  BSTree<TE> open_set;
  deque<distance_pair<TE>> retorno;

  for(auto it = gr.vertexes.begin();it != gr.vertexes.end();++it){
    if(it->second->id == start_node){ 
      f.insert({it->second->id,TE{0} +  h[it->second->id]});
      open_set.insert(distance_pair<TE>{it->second->id,TE{0} +  h[it->second->id]});
    }
    else{ 
      f.insert({it->second->id,numeric_limits<TE>::max()});
    }
  }

  
  while(true){
    auto m = open_set.minValue();
    closed_set.insert(m.nodo);
    

    if(m.nodo == end_node){
      retorno.push_back(distance_pair<TE>{m.nodo,f[m.nodo] - h[m.nodo] });
      break;

    }
    for(auto it = gr.vertexes[m.nodo]->edges.begin(); it != gr.vertexes[m.nodo]->edges.end(); ++it){
      auto v2 = (*it)->vertexes[1];

      if(closed_set.find(v2->id) == closed_set.end() &&( f[v2->id] == numeric_limits<TE>::max()|| 
	    f[v2->id] - h[v2->id] > (f[m.nodo] - h[m.nodo] +(*it)->weight))){

	auto eliminar = distance_pair<TE>{v2->id,f[v2->id]};
	if(open_set.find(eliminar))
	  open_set.remove(eliminar);
	f[v2->id] = f[m.nodo]  - h[m.nodo] + (*it)->weight + h[v2->id];
	padres[v2->id] = m;
	open_set.insert(distance_pair<TE>{v2->id,f[v2->id]});
      }
    }



    open_set.remove(m);
    if(open_set.size() == 0){
      return deque<distance_pair<TE>>{};

    }
  }



  auto temp = end_node;
  while(true){
    auto m = padres[temp];

    if(m.nodo == start_node){
      retorno.push_front(distance_pair<TE>{m.nodo,0});
      break;
    }


    retorno.push_front(distance_pair<TE>{m.nodo,f[m.nodo] - h[m.nodo] });
    temp = m.nodo;
  }


  return retorno;
}



#endif
