#include "../Algorithms/astar.h"


int main(){

  DirectedGraph<int,int> grafito;
  unordered_map<string,int> h;

  grafito.insertVertex("1",1);
  grafito.insertVertex("2",2);
  grafito.insertVertex("3",3);
  grafito.insertVertex("4",4);
  grafito.insertVertex("5",5);
  grafito.insertVertex("6",6);
  grafito.insertVertex("7",7);

  grafito.createEdge("1","2",2);
  grafito.createEdge("1","3",11);
  grafito.createEdge("1","4",1);
  grafito.createEdge("2","5",3);
  grafito.createEdge("3","2",2);
  grafito.createEdge("3","7",1);
  grafito.createEdge("3","6",1);
  grafito.createEdge("4","6",15);
  grafito.createEdge("4","3",12);
  grafito.createEdge("5","3",5);
  grafito.createEdge("6","7",1);

  h.insert({"1",8});
  h.insert({"2",7});
  h.insert({"3",0});
  h.insert({"4",11});
  h.insert({"5",5});
  h.insert({"6",1});
  h.insert({"7",0});




  deque<distance_pair<int>> a = astar(grafito,h,"1","7");

  for(auto &i: a){
    cout<<"{"<<i.nodo<<", "<<i.peso<<"}"<<" ";
  }




  return 0;



}

