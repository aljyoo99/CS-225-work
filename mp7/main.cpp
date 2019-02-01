#include "Graph.h"
#include "Vertex.h"
#include "Edge.h"
#include "DirectedEdge.h"

#include "CYOA.h"

#include <string>
#include <iostream>

int main() {
  CYOA cyoa;
  Graph<Vertex, DirectedEdge> g = cyoa.load("data/");
  //std::cout << g << std::endl;

  // Modify the g.shortestPath call to find the shortest path to your story:

  /*std::list<std::string> path = g.shortestPath("alberty3-gates-intro", "alberty3-gates-ai");
  for (std::string key : path) {
    std::cout << key << " -> ";
  }
  std::cout << "[THE END]" << std::endl;*/

  Graph<Vertex, Edge> h;
  h.insertVertex("a");
  h.insertVertex("b");
  h.insertVertex("c");
  h.insertEdge("a", "b");
  h.insertEdge("a", "c");
  //h.insertEdge("b", "c");
  unsigned initedges = h.edges();
  std::cout << h << std::endl;

  h.removeEdge("b", "a");
  //h.removeEdge("a", "c");
  //h.removeEdge("b", "c");
  h.removeVertex("a");
  /*if (h.edges() == initedges - 2) {
    std::cout<<"removed "<<h.edges()<<std::endl;
  }*/
  std::cout << h << std::endl;
  return 0;
}
