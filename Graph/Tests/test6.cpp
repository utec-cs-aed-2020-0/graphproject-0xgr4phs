#include "../Algorithms/floyd_warshall.h"


int main(){

  DirectedGraph<int,int> grafito;

  grafito.insertVertex("0",0);
  grafito.insertVertex("1",1);
  grafito.insertVertex("2",2);
  grafito.insertVertex("3",3);
  grafito.insertVertex("4",4);
  grafito.insertVertex("5",5);
  grafito.insertVertex("6",6);
  grafito.insertVertex("7",7);


  grafito.createEdge("0","1",1);
  grafito.createEdge("0","3",8);
  grafito.createEdge("0","4",6);
  grafito.createEdge("1","5",9);
  grafito.createEdge("1","6",8);
  grafito.createEdge("2","0",9);
  grafito.createEdge("2","1",9);
  grafito.createEdge("3","5",9);
  grafito.createEdge("3","7",9);
  grafito.createEdge("4","2",2);
  grafito.createEdge("4","6",1);
  grafito.createEdge("5","3",6);
  grafito.createEdge("6","5",4);

  
  /* grafito.display(); */

  auto a = floyd_warshall(grafito);

  
  a.display_a();
  cout<<endl;
  a.display_b();

  




  return 0;



}

