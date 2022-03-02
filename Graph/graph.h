//
//                /$$$$$$                               /$$           /$$
//                /$$__  $$                             | $$          | $$
//                | $$  \__/  /$$$$$$  /$$$$$$   /$$$$$$ | $$$$$$$     | $$$$$$$
//                | $$ /$$$$ /$$__  $$|____  $$ /$$__  $$| $$__  $$    | $$__  $$
//                | $$|_  $$| $$  \__/ /$$$$$$$| $$  \ $$| $$  \ $$    | $$  \ $$
//                | $$  \ $$| $$      /$$__  $$| $$  | $$| $$  | $$    | $$  | $$
//                |  $$$$$$/| $$     |  $$$$$$$| $$$$$$$/| $$  | $$ /$$| $$  | $$
//                \______/ |__/      \_______/| $$____/ |__/  |__/|__/|__/  |__/
//                                            | $$
//                                            | $$
//                                            |__/

#ifndef GRAPH_H
#define GRAPH_H
#include <list>
#include <vector>
#include <unordered_map>
#include <iostream>

/* Declaración de funciones */
template<typename TV, typename TE>
struct Edge;

template<typename TV, typename TE>
struct Vertex;

template<typename TV, typename TE>
class Graph;

/* Funciones Auxiliares */

template<typename VertexType, typename EdgeType>
std::string greedyBFS(Graph<VertexType, EdgeType> *graph, std::string start_node, std::string end_node);

template <typename VertexType, typename EdgeType>
std::string DFS(Graph<VertexType,EdgeType>* graph, std::string start_node);

/* Implementaciones */
template<typename TV, typename TE>
struct Edge {
    Vertex<TV, TE>* vertexes[2]{};
    TE weight{};
};

template<typename TV, typename TE>
struct Vertex {
    std::string id;
    TV data{};
    std::list<Edge<TV, TE>*> edges{};
};

template<typename TV, typename TE>
class Graph{
protected:
    /* Attributes */
    std::unordered_map<std::string, Vertex<TV, TE>*>  vertexes;
    // Number of vertexes
    int V{};
    // Number of edges
    int E{};
public:
    /* Methods */
    virtual bool insertVertex(std::string id, TV vertex) = 0;
    virtual bool createEdge(std::string id1, std::string id2, TE w) = 0;
    virtual bool deleteVertex(std::string id) = 0;
    virtual bool deleteEdge(std::string start, std::string end) = 0;
    virtual TE &operator()(std::string start, std::string end) = 0;
    virtual float density() = 0;
    virtual bool isDense(float threshold = 0.5) = 0;
    virtual bool isConnected() = 0;
    virtual bool isStronglyConnected() noexcept = 0;
    virtual bool empty() = 0;
    virtual void clear()= 0;
    virtual void displayVertex(std::string id)= 0;
    virtual bool findById(std::string id) = 0;
    virtual void display() = 0;

private:
    /* Declaración de funciones amigas */
    template <typename VertexType, typename EdgeType>
    friend std::string greedyBFS(Graph<VertexType,EdgeType>* graph, std::string start_node, std::string end_node);

    template <typename VertexType, typename EdgeType>
    friend std::string DFS(Graph<VertexType,EdgeType>* graph, std::string start_node);
};

template<typename TV,typename TE>
using vertex_t = Vertex<TV,TE>;

#endif // GRAPH_H