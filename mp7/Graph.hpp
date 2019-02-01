#include "Graph.h"
#include "Edge.h"
#include "Vertex.h"

#include <string>
#include <iostream>

using std::list;

/**
* @return The number of vertices in the Graph
*/
template <class V, class E>
unsigned int Graph<V,E>::size() const {
    // TODO: Part 2
    return adjList.size();
}


/**
* @return Returns the degree of a given vertex.
* @param v Given vertex to return degree.
*/
template <class V, class E>
unsigned int Graph<V,E>::degree(const V & v) const {
    // TODO: Part 2
    return adjList[v.key()].size();
}


/**
* Inserts a Vertex into the Graph by adding it to the Vertex map and adjacency list
* @param key The key of the Vertex to insert
* @return The inserted Vertex
*/
template <class V, class E>
V & Graph<V,E>::insertVertex(std::string key) {
    // TODO: Part 2
    V & v = *(new V(key));
    vertexMap.emplace(key, v);
    std::list<edgeListIter> newEdgeList;
    adjList.emplace(key, newEdgeList);
    return v;
}


/**
* Removes a given Vertex
* @param v The Vertex to remove
*/
template <class V, class E>
void Graph<V,E>::removeVertex(const std::string & key) {
    // TODO: Part 2
    std::list<edgeListIter> elist = adjList.at(key);
    while (!elist.empty()) {
        elist = adjList.at(key);
        for (edgeListIter eit : elist) {
            removeEdge(eit);
            break;
        }
    }

    adjList.erase(key);
    vertexMap.erase(key);
}


/**
* Inserts an Edge into the adjacency list
* @param v1 The source Vertex
* @param v2 The destination Vertex
* @return The inserted Edge
*/
template <class V, class E>
E & Graph<V,E>::insertEdge(const V & v1, const V & v2) {
    // TODO: Part 2
    E & e = *(new E(v1, v2));
    edgeList.push_front(e);
    string s1 = v1.key();
    string s2 = v2.key();
    std::list<edgeListIter> & v1el = adjList[s1];
    std::list<edgeListIter> & v2el = adjList[s2];
    edgeListIter edgeit = edgeList.begin();
    v1el.push_front(edgeit);
    v2el.push_front(edgeit);
    return e;
}


/**
* Removes an Edge from the Graph
* @param key1 The key of the ource Vertex
* @param key2 The key of the destination Vertex
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const std::string key1, const std::string key2) {
  // TODO: Part 2

    /*std::cout<<"size "<<edgeList.size()<<std::endl;
    for (auto e : adjList) {
        std::cout<<e.first<<" "<<e.second.size()<<std::endl;
    }*/

    V & start = vertexMap.at(key1);
    V & ending = vertexMap.at(key2);
    E edge(start,ending);
    for(edgeListIter currit : adjList.at(key1)) {
          Edge curre = *currit;
          if(curre == edge) {
              removeEdge(currit);
              break;
          }
    }

    /*std::cout<<"size "<<edgeList.size()<<std::endl;
    for (auto e : adjList) {
        std::cout<<e.first<<" "<<e.second.size()<<std::endl;
    }*/

}


/**
* Removes an Edge from the adjacency list at the location of the given iterator
* @param it An iterator at the location of the Edge that
* you would like to remove
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const edgeListIter & it) {
  // TODO: Part 2

    E edge = *it;
    const V & start = edge.source();
    const V & ending = edge.dest();
    string key1 = start.key();
    string key2 = ending.key();

    for(edgeListIter currit: adjList.at(key1)) {
        Edge curre = *currit;
        if(curre == edge) {
            adjList.at(key1).remove(currit);
            break;
        }
    }
    for(edgeListIter currit: adjList.at(key2)) {
        Edge curre = *currit;
        if(curre == edge) {
            adjList.at(key2).remove(currit);
            break;
        }
    }

    edgeList.erase(it);
}
// O(deg(v))
/**
* @param key The key of an arbitrary Vertex "v"
* @return The list edges (by reference) that are adjacent to "v"
*/
template <class V, class E>
const std::list<std::reference_wrapper<E>> Graph<V,E>::incidentEdges(const std::string key) const {
    // TODO: Part 2
    std::list<std::reference_wrapper<E>> edges;
    std::list<edgeListIter> listedgeit = adjList.at(key);

    for (edgeListIter edgeit : listedgeit) {
        edges.push_back(*edgeit);
    }
    return edges;
}


// O(deg(v))
/**
* Return whether the two vertices are adjacent to one another
* @param key1 The key of the source Vertex
* @param key2 The key of the destination Vertex
* @return True if v1 is adjacent to v2, False otherwise
*/
template <class V, class E>
bool Graph<V,E>::isAdjacent(const std::string key1, const std::string key2) const {
    // TODO: Part 2
    std::list<edgeListIter> listedgeit = adjList.at(key1);
    for (edgeListIter edgeit : listedgeit) {
        if ((*edgeit).get().source() == vertexMap.at(key1) && (*edgeit).get().dest() == vertexMap.at(key2)) {
            return true;
        }
    }
    return false;
}
