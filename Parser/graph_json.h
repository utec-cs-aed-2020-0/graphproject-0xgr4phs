#ifndef GRAPH_JSON_H
#define GRAPH_JSON_H
#include "../Graph/UndirectedGraph.h"
#include "../Graph/DirectedGraph.h"
#include "json.hpp"

using nlohmann::json;


template<typename TV, typename TE>
class graph_json{
  protected:
  json gj = json::array();
  public:

  void clear(){
    gj = json::array();
  }

  void readJSON(string js){
    gj = json::parse(js);
  }


  void uGraphMake(UnDirectedGraph<TV, TE> &tempGraph){
    tempGraph.clear();

    for(auto& kv: gj.items()){
      tempGraph.insertVertex(kv.key(), gj[kv.key()]["data"] );

    }

    for(auto& kv: gj.items()){
      /* cout<<kv.key()<<endl; */
      for(int i = 0; i < gj[kv.key()]["connections"].size();++i){
	/* cout<<gj[kv.key()]["conexions"][i][0]<<" "; */
	tempGraph.createEdge(kv.key(), gj[kv.key()]["connections"][i][0] , gj[kv.key()]["connections"][i][1] );
      }

    }




  }

  void dGraphMake(DirectedGraph<TV, TE> &tempGraph){
    tempGraph.clear();

    for(auto& kv: gj.items()){
      tempGraph.insertVertex(kv.key(), gj[kv.key()]["data"] );

    }
    /* tempGraph.display(); */
    /* cout<<endl; */

    for(auto& kv: gj.items()){
      for(int i = 0; i < gj[kv.key()]["connections"].size();++i){
	tempGraph.createEdge(kv.key(), gj[kv.key()]["connections"][i][0] , gj[kv.key()]["connections"][i][1] );
      }
      /* cout<<endl; */

    }


  }

};




#endif
