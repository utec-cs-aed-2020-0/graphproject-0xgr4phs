#include "../Algorithms/dijkstra.h"


int main(){
  UnDirectedGraph<int,int> grafito;


  grafito.insertVertex("A", 0);
  grafito.insertVertex("B", 1);
  grafito.insertVertex("C", 2);
  grafito.insertVertex("D", 3);
  grafito.insertVertex("E", 4);
  grafito.insertVertex("F", 5);
  grafito.insertVertex("G", 6);
  grafito.insertVertex("H", 7);

  grafito.createEdge("A","C",4);
  grafito.createEdge("A","F",7);
  grafito.createEdge("C","D",3);
  grafito.createEdge("C","F",2);
  grafito.createEdge("C","G",9);
  grafito.createEdge("F","G",8);
  grafito.createEdge("D","G",7);
  grafito.createEdge("D","E",3);
  grafito.createEdge("G","E",2);
  grafito.createEdge("E","H",7);
  grafito.createEdge("E","B",9);
  grafito.createEdge("H","B",3);
  grafito.createEdge("G","H",3);


  try{
   dijkstra<int,int>(grafito , "A").display();
  }catch(const string x){
    cout<<endl<<x;
  }



  return 0;



}

