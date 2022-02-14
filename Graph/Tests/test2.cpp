
#include "../Algorithms/dijkstra.h"


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

  grafito.createEdge("0","2",9);
  grafito.createEdge("1","3",7);
  grafito.createEdge("1","6",9);
  grafito.createEdge("2","1",5);
  grafito.createEdge("2","4",9);
  grafito.createEdge("2","5",3);
  grafito.createEdge("3","1",7);
  grafito.createEdge("3","7",9);
  grafito.createEdge("4","6",1);
  grafito.createEdge("5","7",8);
  grafito.createEdge("6","2",3);
  grafito.createEdge("6","4",2);
  grafito.createEdge("7","6",1);


  try{
 dijkstra<int,int>(grafito , "0").display();
  }catch(const string x){
    cout<<endl<<x;
  }



  return 0;



}

