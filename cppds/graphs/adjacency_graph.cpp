#include <fstream>
#include <iostream>
#include <utility>      //std::pair
#include <algorithm>    //std::find
#include <map>
#include <string>
#include <vector>
using namespace std;

class Vertex {
public:
      string id;
      map<string, float> connectedTo;

      Vertex() {
      }

      Vertex(string key) {
              id = key;
      }

      void addNeighbor(string nbr, float weight = 1) {
              connectedTo[nbr] = weight;
      }

      vector<string> getConnections() {
              vector<string> keys;
              // Use of iterator to find all keys
              for (map<string, float>::iterator it = connectedTo.begin();
                       it != connectedTo.end();
                       ++it) {
                      keys.push_back(it->first);
              }
              return keys;
      }

      string getId() {
              return id;
      }

      float getWeight(string nbr) {
              return connectedTo[nbr];
      }

      friend ostream &operator<<(ostream &, Vertex &);
};

ostream &operator<<(ostream &stream, Vertex &vert) {
      vector<string> connects = vert.getConnections();
    stream << vert.id << " -> ";
      for (unsigned int i = 0; i < connects.size(); i++) {
              stream << connects[i] << endl << "\t";
      }

      return stream;
}

class Graph {
public:
      map<string, Vertex> vertList;
      int numVertices;
      bool directional;

      Graph(bool directed = true) {
              directional = directed;
              numVertices = 0;
      }

      Vertex addVertex(string key) {
              numVertices++;
              Vertex newVertex = Vertex(key);
              this->vertList[key] = newVertex;
              return newVertex;
      }

      Vertex *getVertex(string n) {
              for (map<string, Vertex>::iterator it = vertList.begin();
                       it != vertList.end();
                       ++it) {
                      if (it->first == n) {
                              // Forced to use pntr due to possibility of returning NULL
                              Vertex *vpntr = &vertList[n];
                              return vpntr;
                      } else {
                              return NULL;
                      }
              }
      }

      bool contains(string n) {
              for (map<string, Vertex>::iterator it = vertList.begin();
                       it != vertList.end();
                       ++it) {
                      if (it->first == n) {
                              return true;
                      }
              }
              return false;
      }

      void addEdge(string f, string t, float cost = 1) {
              if (!this->contains(f)) {
                      this->addVertex(f);
              }
              if (!this->contains(t)) {
                      this->addVertex(t);
              }
              vertList[f].addNeighbor(t, cost);

              if (!directional) {
                      vertList[t].addNeighbor(f, cost);
              }
      }

      vector<string> getVertices() {
              vector<string> verts;

              for (map<string, Vertex>::iterator it = vertList.begin();
                       it != vertList.end();
                       ++it) {
                      verts.push_back(it->first);
              }
              return verts;
      }

      friend ostream &operator<<(ostream &, Graph &);
};

ostream &operator<<(ostream &stream, Graph &grph) {
      for (map<string, Vertex>::iterator it = grph.vertList.begin();
               it != grph.vertList.end();
               ++it) {
              stream << grph.vertList[it->first];
        cout<<endl;
      }

      return stream;
}

string getBlank(string str, int index) {
      string blank = str;
      blank[index] = '_';
      return blank;
}

Graph buildGraph(vector<string> words) {
      Graph g(false);

      map<string, vector<string> > d;

      // Go through the words
      for (unsigned int i = 0; i < words.size(); i++) {
              // Go through each letter, making it blank
              for (unsigned int j = 0; j < words[i].length(); j++) {
                      string bucket = getBlank(words[i], j);
                      // Add the word to the map at the location of the blank
                      d[bucket].push_back(words[i]);
              }
      }

      for (map<string, vector<string> >::iterator iter = d.begin(); iter != d.end(); ++iter) {
              for(unsigned int i=0; i<iter->second.size();i++) {
            for (unsigned int j=0; j<iter->second.size();j++) {
                if (iter->second[i]!=iter->second[j]) {
                    g.addEdge(iter->second[i],iter->second[j]);
                }
            }
        }
      }

    return g;
}

class DFSGraph{
    typedef std::pair<int, std::list<int>> vertex_t;
    typedef std::map<int, vertex_t> graph_t;
public:
    const bool directional;
    DFSGraph(bool directional) : directional(directional){}

    bool containsVertex(int id){
        return vertices.count(id);
    }

    std::list<int>& getVertexConnections(int id){
        return vertices[id].second;
    }

    void addVertex(int id){
        if(containsVertex(id)){
            vertices[id].second.clear();
        }else{
            vertices[id] = std::make_pair(id, std::list<int>());
        }
    }

    vertex_t& getVertex(int id){
        return vertices[id];
    }

    void addEdge(int fromID, int toID){
        if(!containsVertex(fromID))
            addVertex(fromID);

        if(!containsVertex(toID))
            addVertex(toID);

        getVertexConnections(fromID).push_back(toID);
        if(!directional)
            getVertexConnections(toID).push_back(fromID);
    }

    void dfs(){
        std::list<int> visitedList;

        for(auto& cur : vertices){
            if(std::find(visitedList.begin(), visitedList.end(), cur.first) == visitedList.end()){
                dfsvisit(visitedList, cur.second);
            }
        }
    }

    void dfsvisit(std::list<int>& visitedList, vertex_t& vertex){
        visitedList.push_back(vertex.first);

        std::cout << "Visited Vertex With ID#: " << vertex.first << std::endl;

        for(int neighborID : vertex.second){
            if(std::find(visitedList.begin(), visitedList.end(), neighborID) != visitedList.end()){
                dfsvisit(visitedList, getVertex(neighborID));
            }
        }
    }
private:
    graph_t vertices;
};