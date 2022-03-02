#ifndef BSTREE_H
#define BSTREE_H

#include "node.h"
#include <stack>
#include <math.h>
#include <queue>

using namespace std;

template <typename TE>
class BSTree {
    private:
        NodeBT<TE>* root;    

    public:
        BSTree(): root(nullptr){}

	void insert(distance_pair<TE> value){
	  NodeBT<TE>* n = new NodeBT<TE>(value);
	  if(root == nullptr){
	    root = n;
	  }
	  auto temp = root;


	  while(true){
	    if(temp->par == value) return;
	    else if(value < temp->par){
	      if(temp->left == nullptr){
		temp->left = n;
		return;
	      }
	      temp = temp->left;
	    }
	    else if(value > temp->par){
	      if(temp->right == nullptr){
		temp->right = n;
		return;
	      }
	      temp = temp->right;
	    } 


	  }



	}

	bool find(distance_pair<TE> value){
	  /* cout<<value.nodo<<" "<<value.peso<<":"; */
	  auto temp = root;
	  while(temp != nullptr){
	    /* cout<<temp->par.nodo<<" "<<temp->par.peso<<endl; */
	    if(temp->par == value) return true;
	    else if(value < temp->par) temp = temp->left;
	    else if(value > temp->par) temp = temp->right;
	  } 


	  return false;


	}



	string displayInOrder(){
	  string respuesta("");
	  stack<NodeBT<TE>*> ayuda;
	  auto temp = root;


	  while(temp != nullptr || !ayuda.empty()){

	    while(temp != nullptr){
	      ayuda.push(temp);
	      temp = temp->left;
	    }

	    temp = ayuda.top();
	    ayuda.pop();
	    respuesta += "{" + temp->par.nodo + ", " + to_string(temp->par.peso) + "} ";

	    temp = temp->right;


	  }

	  return respuesta;


	}

    public:


	distance_pair<TE> minValue(){
	  auto temp = root;


	  while(temp->left != nullptr)
	    temp = temp->left;

	  return temp->par;
	}
	distance_pair<TE> maxValue(){
	  auto temp = root;


	  while(temp->right != nullptr)
	    temp = temp->right;


	  return temp->par;


	}
    private:
	NodeBT<TE>* findP(NodeBT<TE>* c,NodeBT<TE>* v){
	  if(c == v) throw "No puedes encontrar al padre partiendo de uno mismo";
	  if(c->right == v || c->left == v) return c;

	  auto siguiente = c->par > v->par ? c->left : c->right;
	  


	  return findP(siguiente,v);
	}


    public:
	bool rootIsNull(){return root == nullptr;}
	void remove(distance_pair<TE> value){
	  //cout<<" "<<value.nodo<<" "<<value.peso;
	  if(!find(value)) throw value.nodo  ;
	  auto v = findV(value);

	  if(v->left == nullptr && v->right == nullptr){
	    if(v == root){
	      root->KillSelf();
	      root = nullptr;
	      return;
	    }
	    auto p = findP(root,v);
	    if(p->right == v){
	      p->right->KillSelf();
	      p->right = nullptr;
	      return;

	    }
	    p->left->KillSelf();
	    p->left = nullptr;

	  }else if(v->left == nullptr || v->right == nullptr){
	    decltype(root) temp;

	    if(v->left != nullptr){
	      temp = v->left;

	    }else{
	      temp = v->right;
	    }

	    if(v == root){
	      root->KillSelf();
	      root = temp;
	      return;
	    }
	    auto p = findP(root,v);

	    if(p->right == v ){
	      p->right->KillSelf();
	      p->right = temp;
	      return;
	    }
	    p->left->KillSelf();
	    p->left = temp;


	  }else{
	    auto pred = findV(predecessor(value));
	    auto value2 = pred->par;
	    remove(value2);
	    v->par = value2;



	  }

	}

	int size(){
	  int s = 0;
	  stack<NodeBT<TE>*> ayuda;
	  auto temp = root;


	  while(temp != nullptr || !ayuda.empty()){

	    while(temp != nullptr){
	      ayuda.push(temp);
	      temp = temp->left;
	    }

	    temp = ayuda.top();
	    ayuda.pop();
	    s++;

	    temp = temp->right;


	  }

	  return s;

	}

    private:
	NodeBT<TE>* findV(distance_pair<TE> value){
	  auto temp = root;
	  while(temp != nullptr){
	    if(temp->par == value) return temp;
	    else if(value < temp->par) temp = temp->left;
	    else if(value > temp->par) temp = temp->right;
	  } 

	  throw "No se encuentra el nodo";


	}
	NodeBT<TE>* minValue(NodeBT<TE>* start){
	  auto temp = start;


	  while(temp->left != nullptr)
	    temp = temp->left;

	  return temp;
	}
	NodeBT<TE>* maxValue(NodeBT<TE>* start){
	  auto temp = start;


	  while(temp->right != nullptr)
	    temp = temp->right;


	  return temp;


	}


    public:
	distance_pair<TE> successor(distance_pair<TE> value){
	  if(!find(value)) throw "No se encuentra el valor";
	  auto v = findV(value);

	  if(v->par == maxValue()) return value;
	  else if(v->right != nullptr) return minValue(v->right)->par;
	  else{
	    stack<NodeBT<TE>*> ayuda;
	    auto temp = root;
	    ayuda.push(temp);


	    while(temp->par != value){
	      temp = temp->par > value ? temp->left : temp->right;
	      ayuda.push(temp);

	    }


	    ayuda.pop();

	    while(true){
	      if(ayuda.top()->left == temp) return ayuda.top()->par;
	      temp = ayuda.top();
	      ayuda.pop();

	    }



	  }

	}


	// Retornar el valor siguiente de "value" en el arbol
	distance_pair<TE> predecessor(distance_pair<TE> value){
	  if(!find(value)) throw "No se encuentra el valor";
	  auto v = findV(value);

	  if(v->par == minValue()) return value;
	  else if(v->left != nullptr) return maxValue(v->left)->par;
	  else{
	    stack<NodeBT<TE>*> ayuda;
	    auto temp = root;
	    ayuda.push(temp);


	    while(temp->par != value){
	      temp = temp->par > value ? temp->left : temp->right;
	      ayuda.push(temp);

	    }


	    ayuda.pop();

	    while(true){
	      if(ayuda.top()->right == temp) return ayuda.top()->par;
	      temp = ayuda.top();
	      ayuda.pop();

	    }



	  }


	} // Retornar el valor anterior de "value" en el arbol
	void clear(){
	  stack<NodeBT<TE>*> ayuda;
	  stack<NodeBT<TE>*> eliminacion;
	  auto temp = root;


	  while(temp != nullptr || !ayuda.empty()){

	    while(temp != nullptr){
	      ayuda.push(temp);
	      temp = temp->left;
	    }

	    temp = ayuda.top();
	    ayuda.pop();

	    eliminacion.push(temp);

	    temp = temp->right;


	  }


	  while(!eliminacion.empty()){
	    eliminacion.top()->KillSelf();
	    eliminacion.pop();

	  }


	  root = nullptr;

	}// Liberar todos los nodos (usar root->KillSelf)


}; 


#endif



