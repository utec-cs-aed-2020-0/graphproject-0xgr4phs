<h1 align="center">
  <br>
  <a href="#"><img src="./assets/logo.png" alt="" width="200"></a>
  <br>
  UTEC Graphs
  <br>
</h1>
<p align="center">
  <img src="https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white">
  <img src="https://img.shields.io/badge/CLion-black?style=for-the-badge&logo=clion&logoColor=white">
  <img src="https://img.shields.io/badge/NeoVim-%2357A143.svg?&style=for-the-badge&logo=neovim&logoColor=white">
  <img src="https://img.shields.io/badge/CMake-%23008FBA.svg?style=for-the-badge&logo=cmake&logoColor=white">
  <img src="https://img.shields.io/badge/Notion-%23000000.svg?style=for-the-badge&logo=notion&logoColor=white">
</p>

<h1 align="center">
  <a href="#"><img src="./assets/capture.gif" alt="" width="70%"></a>
</h1>


## Integrantes
|   Apellidos y Nombres    |           Email               |
|--------------------------|-------------------------------|
| Morales Panitz, Alexander| alexander.morales@utec.edu.pe |
| Ugarte Quispe, Grover    | grover.ugarte@utec.edu.pe     |
| Bracamento Otiniano, Eric| eric.bracamonte@utec.edu.pe   |

----
El proyecto del curso consiste en implementar una estructura de datos de grafo y un file parser. La estructura debe soportar los métodos y algoritmos descritos a continuacion:  


## Graph data structure

* El grafo debe ser dinámico (inserciones. eliminaciones, búsquedas, ...)
* Se debe implementar los dos tipos de grafos: dirigidos y no-dirigidos.
* No considerar loops ni multi-arista. 


### Methods:
```cpp
bool insertVertex(string id, V data); // Creates a new vertex in the graph with some data and an ID

bool createEdge(string start, string end, E data); // Creates a new edge in the graph with some data

bool deleteVertex(string id); // Deletes a vertex in the graph

bool deleteEdge(string start, string end); // Deletes an edge in the graph, it is not possible to search by the edge value, since it can be repeated

E &operator()(string start, string end); // Gets the value of the edge from the start and end vertexes

float density() const; // Calculates the density of the graph

bool isDense(float threshold = 0.5) const; // Calculates the density of the graph, and determine if it is dense dependening on a threshold value

bool isConnected(); // Detect if the graph is connected

bool isStronglyConnected() throw(); // Detect if the graph is strongly connected (only for directed graphs)

bool empty(); // If the graph is empty

void clear(); // Clears the graph
```

### Algorithms:

#### Algoritmo Belman-Ford 
Consta de un algoritmo con el objetivo de encontrar la ruta más corta entre un nodo y los restantes. Al igual que el algoritmo Dijkstra, se basa en la comparación de distancias y asignación de padres. La única diferencia es que la evaluación de aquello se realiza mediante la iteración de todas las aristas en el grafo por una cantidad $|V|-1$. Ya que no depende de la partida de vertices, es posible trabajar con grafos con pesos negativos. 

![](img/bf.gif)

Este algoritmo es principalmente utilizado con grafos dirigidos, ya que si se tratase de aplicar en un grafo no dirigido y este contase con una arista de peso negativa, existiría un bucle que tras cada iteración ocasionaría la disminución en la distancia. 

Presenta un complejidad de $O(|E|*|V|)$.

```cpp
template <typename TV, typename TE>
DirectedGraph<TV, TE> bellman_ford(DirectedGraph<TV, TE> grafo, const string &nodoInicio);
```

En nuestra implementación, se retorna un grafo dirigido el cual presenta las aristas que permiten el menor peso para llegar a todos los vértices.

#### Algoritmo Kruskal
Consta de un algoritmo para hallar un árbol mínimo de expansión en un grafo. Se basa en recorrer las aristas de forma ascendente dependiendo de sus pesos sin crear ciclos en el proceso. Esto se realiza mediante un disjoint set.

![](img/kk.gif)

Presenta un complejidad de $O(E\log V)$

```cpp
template <typename TV, typename TE>
UnDirectedGraph<TV, TE> kruskal(UnDirectedGraph<TV, TE> grafo)
```

En nuestra implementación, considerando de que Kruskal puede identificar ciclos en grafos dirigidos cuando las direcciones determinan lo contrario, entonces solo se retornará un grafo no dirigido.

#### Algoritmo Prim

Es un algoritmo de obtención de un árbol de expansión mínima el cual se enfoca en aglomerar a un grafo las aristas con menor tamaño tras recorrer vértices por media de las aristas. Sabiendo que no se deben formar ciclos, requerimos la ayuda de un disjoint set.

![](img/pr.gif)

Su complejidad es $O(V^2)$.

```cpp
template <typename TV, typename TE>
UnDirectedGraph<TV, TE> prim(UnDirectedGraph<TV, TE> grafo, string inicio);
```

Sabiendo que solo se pueden recorrer vértices si existe una conexión dirigida entre ellos, existen casos donde no será posible llegar a todos los vértices. Por ende, no podrá obtenerse un arbol de expansión mínima. Por ese motivo, solo se utiliza para el caso de grafos no dirigidos.

```cpp
//Given the graph
UndirectedGraph<char, int> graph;

//1- Generates a MST graph using the Kruskal approach (only for undirected graphs)
Kruskal<char, int> kruskal(&graph);
UndirectedGraph<char, int> result = kruskal.apply();//return a tree

//2- Generates a MST graph using the Prim approach (only for undirected graphs)
Prim<char, int> prim(&graph, "A");
UndirectedGraph<char, int> result = prim.apply();//return a tree

//3- A *
AStar<char, int> astar(&graph, "A", "Z", vector<int> heuristics);
UndirectedGraph<char, int> result = astar.apply();

```


## JSON file parser
* Construye un grafo a partir de una archivo JSON de aereopuertos del mundo. 


### Methods:
```cpp
void clear(); // Clears parser saved atributes

void readJSON(); // Parses JSON file and saves data into class
// NOTE: each derived class has its own readJSON method

void uGraphMake(UndirectedGraph<string, double> &tempGraph); // Adds the parsed data into the specified undirected graph

void dGraphMake(DirectedGraph<string, double> &tempGraph); // Adds the parsed data into the specified directed graph
```
# How to use this repo
```
$ g++ main.cpp && ./a.out
```
