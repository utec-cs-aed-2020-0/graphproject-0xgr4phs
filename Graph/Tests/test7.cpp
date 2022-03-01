#include "../Algorithms/floyd_warshall.h"


int main(){

  UnDirectedGraph<int,int> grafito;

  grafito.insertVertex("0",0);
  grafito.insertVertex("1",1);
  grafito.insertVertex("2",2);
  grafito.insertVertex("3",3);
  grafito.insertVertex("4",4);
  grafito.insertVertex("5",5);
  grafito.insertVertex("6",6);
  grafito.insertVertex("7",7);


  grafito.createEdge("0","1",5);
  grafito.createEdge("0","2",3);
  grafito.createEdge("0","3",7);
  grafito.createEdge("0","4",9);

  grafito.createEdge("1","2",8);
  grafito.createEdge("1","3",3);
  grafito.createEdge("1","6",5);

  grafito.createEdge("2","4",9);
  grafito.createEdge("2","5",5);


  grafito.createEdge("7","5",3);

  
  /* grafito.display(); */

  auto a = floyd_warshall(grafito);

  
  a.display_a();
  cout<<endl;
  a.display_b();

  




  return 0;



}

