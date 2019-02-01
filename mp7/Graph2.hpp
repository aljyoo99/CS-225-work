#include <queue>
#include <algorithm>
#include <string>
#include <list>


/**
 * Returns an std::list of vertex keys that creates some shortest path between `start` and `end`.
 *
 * This list MUST include the key of the `start` vertex as the first vertex in the list, the key of
 * the `end` vertex as the last element in the list, and an ordered list of all vertices that must
 * be traveled along the shortest path.
 *
 * For example, the path a -> c -> e returns a list with three elements: "a", "c", "e".
 *
 * @param start The key for the starting vertex.
 * @param end   The key for the ending vertex.
 */
template <class V, class E>
std::list<std::string> Graph<V,E>::shortestPath(const std::string start, const std::string end) {
    std::list<std::string> path;
    std::unordered_map<V, bool> visited;
    std::unordered_map<V , V> mst;
    std::queue<V> q;

    for (auto vpair : vertexMap) {
        visited[vpair.second] = false;
    }

    q.push(vertexMap.at(start));
    visited[vertexMap.at(start)] = true;
    while (!q.empty()) {
        V vertex = q.front();
        q.pop();
        //std::cout<<"key: "<<vertex.key()<<std::endl;
        //std::cout<<"adj: ";
        for (auto adjE : incidentEdges(vertex.key())) {
            V adjV = adjE.get().dest();
            if (adjV.key() != vertex.key()) {
                //std::cout<<adjV.key()<<" ";
                if (!visited[adjV]) {
                    visited[adjV] = true;
                    mst.insert(std::make_pair(adjV, vertex));
                    q.push(adjV);
                }
            } else {
                adjV = adjE.get().source();
                //std::cout<<adjV.key()<<" ";
                if (!visited[adjV]) {
                    visited[adjV] = true;
                    mst.insert(std::make_pair(adjV, vertex));
                    q.push(adjV);
                }
            }
        }
        //std::cout<<std::endl;
    }


    V currvertex = vertexMap.at(end);
    //for (auto it : mst) {
        //std::cout<<it.first.key()<<" "<<it.second.key()<<std::endl;
    //}

    while (mst.at(currvertex).key() != start) {
        path.push_back(currvertex.key());
        currvertex = mst.at(currvertex);
    }
    //std::cout<<"end"<<std::endl;
    path.push_back(currvertex.key());
    path.push_back(start);
    std::reverse(path.begin(), path.end());
    return path;
}
