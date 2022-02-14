#include "../Algorithms/astar.h"


int main(){

  UnDirectedGraph<int,int> grafito;
  unordered_map<string,int> h;

  grafito.insertVertex("A",1);
  grafito.insertVertex("B",2);
  grafito.insertVertex("C",3);
  grafito.insertVertex("D",4);
  grafito.insertVertex("E",5);
  grafito.insertVertex("F",6);
  grafito.insertVertex("G",7);
  grafito.insertVertex("H",8);
  grafito.insertVertex("I",9);

  grafito.createEdge("A","B",22);
  grafito.createEdge("A","C",9);
  grafito.createEdge("A","D",12);
  grafito.createEdge("B","H",34);
  grafito.createEdge("B","F",36);
  grafito.createEdge("B","C",35);
  grafito.createEdge("C","F",42);
  grafito.createEdge("C","E",65);
  grafito.createEdge("C","D",4);
  grafito.createEdge("D","E",33);
  grafito.createEdge("D","I",30);
  grafito.createEdge("H","F",24);
  grafito.createEdge("H","G",25);
  grafito.createEdge("H","I",19);
  grafito.createEdge("F","E",18);
  grafito.createEdge("F","G",39);
  grafito.createEdge("E","G",23);
  grafito.createEdge("I","G",21);

  h.insert({"A",36});
  h.insert({"B",39});
  h.insert({"C",31});
  h.insert({"D",30});
  h.insert({"E",34});
  h.insert({"F",32});
  h.insert({"G",21});
  h.insert({"H",19});
  h.insert({"I",0});




  deque<distance_pair<int>> a = astar(grafito,h,"A","I");

  for(auto &i: a){
    cout<<"{"<<i.nodo<<", "<<i.peso<<"}"<<" ";
  }




  return 0;



}

