#include <fstream>
#include <iostream>
#include <utility>      // std::pair
#include <algorithm>    // std::find
#include <list>         // std::list
#include <map>          // std::map
#include <string>
#include <vector>
#include <limits>
using namespace std;

/**
 * Represents a single vertex in a graph, containing methods and attributes for maintaining
 * graph properties and interactions with other vertices.
 * 
 * Attributes:
 *     id (string): Unique identifier of the vertex.
 *     connectedTo (map<string, float>): Adjacency list mapping neighbor ID to edge weight.
 *     color (string): Vertex color for traversal, e.g., "white", "gray", "black".
 *     previous (Vertex*): Pointer to previous vertex in the shortest path or traversal.
 *     discovery_time (int): Discovery time in depth-first search.
 *     closing_time (int): Closing time in depth-first search.
 *     distance (int): Distance from the source vertex, initialized to infinity.
 */
class Vertex {
public:
    string id;
    map<string, float> connectedTo;
    string color;
    Vertex* previous;
    int discovery_time;
    int closing_time;
    int distance;

    /**
     * Default constructor that initializes vertex with empty or default attributes.
     */
    Vertex() : id(""), color("white"), previous(nullptr), discovery_time(0), closing_time(0), distance(numeric_limits<int>::max()) {}

    /**
     * Constructor that initializes a vertex with a specific identifier.
     * 
     * Args:
     *     key (string): The unique identifier for the vertex.
     */
    Vertex(string key) : id(key), color("white"), previous(nullptr), discovery_time(0), closing_time(0), distance(numeric_limits<int>::max()) {}

    /**
     * Adds a neighbor to this vertex with an optional weight.
     * 
     * Args:
     *     nbr (string): The identifier of the neighbor vertex.
     *     weight (float): The weight of the edge connecting to the neighbor, defaulting to 1.0.
     */
    void addNeighbor(string nbr, float weight = 1) {
        connectedTo[nbr] = weight;
    }

    /**
     * Returns a vector of identifiers for all direct neighbors of this vertex.
     * 
     * Returns:
     *     vector<string>: A vector of neighbor identifiers.
     */
    vector<string> getConnections() const {
        vector<string> keys;
        for (auto it = connectedTo.begin(); it != connectedTo.end(); ++it) {
            keys.push_back(it->first);
        }
        return keys;
    }

    /**
     * Accessor method for the vertex's identifier.
     * 
     * Returns:
     *     string: The identifier of this vertex.
     */
    string getId() const {
        return id;
    }

    /**
     * Returns the weight of the edge connecting this vertex to a given neighbor.
     * 
     * Args:
     *     nbr (string): The identifier of the neighbor.
     * 
     * Returns:
     *     float: The weight of the edge to the specified neighbor.
     * 
     * Throws:
     *     runtime_error: If the neighbor is not found in the adjacency list.
     */
    float getWeight(const string& nbr) const {
        if (connectedTo.find(nbr) != connectedTo.end()) {
            return connectedTo.at(nbr);
        }
        throw std::runtime_error("Neighbor not found");
    }

    /**
     * Provides a string representation of the vertex for easy debugging and display.
     * 
     * Returns:
     *     string: A string representing the vertex details.
     */
    string to_string() const {
        string prev_id = (previous ? previous->id : "None");
        string distance_str = (distance == numeric_limits<int>::max()) ? "inf" : std::to_string(distance);
        return id + " | " + color + " | " + distance_str + " | " +
               std::to_string(discovery_time) + " | " + std::to_string(closing_time) + " | " + prev_id;
    }
};

// Overloads the << operator to provide a standard way of outputting vertex details.
ostream &operator<<(ostream &stream, Vertex &vert) {
    vector<string> connects = vert.getConnections();
    stream << vert.id << " -> ";
    for (unsigned int i = 0; i < connects.size(); i++) {
        stream << connects[i] << " (Weight: " << vert.getWeight(connects[i]) << ")" << endl;
        if (i < connects.size() - 1) stream << "\t";
    }
    return stream;
}

/**
 * Represents a graph structure with a list of vertices and methods to manipulate the graph,
 * such as adding vertices and edges, and checking if a vertex exists.
 * 
 * Attributes:
 *     vertList (map<string, Vertex>): Maps vertex identifiers to Vertex objects.
 *     numVertices (int): Number of vertices in the graph.
 *     directional (bool): Flag to check if the graph is directed.
 */
class Graph {
public:
    map<string, Vertex> vertList;
    int numVertices;
    bool directional;

    /**
     * Constructor initializes an empty graph, optionally directed.
     * 
     * Args:
     *     directed (bool): Specifies whether the graph is directed, default is true.
     */
    Graph(bool directed = true) : directional(directed), numVertices(0) {}

    /**
     * Adds a vertex to the graph by key, initializing it if it doesn't exist.
     * 
     * Args:
     *     key (string): The unique identifier for the new vertex.
     * 
     * Returns:
     *     Vertex: The vertex added to the graph.
     */
    Vertex addVertex(string key) {
        if (!contains(key)) {
            numVertices++;
            Vertex newVertex(key);
            vertList[key] = newVertex;
        }
        return vertList[key];
    }

    /**
     * Returns a pointer to the vertex if it exists, otherwise nullptr.
     * 
     * Args:
     *     n (string): The identifier of the vertex to retrieve.
     * 
     * Returns:
     *     Vertex*: A pointer to the vertex, or nullptr if it does not exist.
     */
    Vertex* getVertex(const string& n) {
        auto it = vertList.find(n);
        if (it != vertList.end()) {
            return &it->second;
        }
        return nullptr;
    }

    /**
     * Checks if a vertex with a specified identifier exists in the graph.
     * 
     * Args:
     *     n (string): The identifier of the vertex to check.
     * 
     * Returns:
     *     bool: True if the vertex exists, false otherwise.
     */
    bool contains(string n) {
        return vertList.find(n) != vertList.end();
    }


    /**
     * Adds an edge between two vertices with an optional cost. If the vertices do not exist,
     * they are added to the graph.
     * 
     * Args:
     *     f (string): The identifier of the from vertex.
     *     t (string): The identifier of the to vertex.
     *     cost (float): The cost of the edge, defaulting to 1.0.
     */
    void addEdge(string f, string t, float cost = 1) {
        if (!contains(f)) {
            addVertex(f);
        }
        if (!contains(t)) {
            addVertex(t);
        }
        vertList[f].addNeighbor(t, cost);
        if (!directional) {
            vertList[t].addNeighbor(f, cost); // Add the edge in the opposite direction for undirected graphs.
        }
    }

    /**
     * Retrieves a list of all vertex identifiers in the graph.
     * 
     * Returns:
     *     vector<string>: A vector containing all vertex identifiers in the graph.
     */
    vector<string> getVertices() {
        vector<string> verts;
        for (auto& pair : vertList) {
            verts.push_back(pair.first);
        }
        return verts;
    }

    /**
     * Overloads the output stream operator to print all vertices and their connections in the graph.
     * Each vertex is printed followed by its connections and weights.
     * 
     * Args:
     *     stream (ostream&): The output stream.
     *     grph (Graph&): The graph to be printed.
     * 
     * Returns:
     *     ostream&: The output stream for chaining.
     */
    friend ostream &operator<<(ostream &stream, Graph &grph) {
        for (auto& pair : grph.vertList) {
            stream << grph.vertList[pair.first];
            cout << endl;
        }
        return stream;
    }
};

/**
 * Constructs a graph from a list of words by connecting words that differ by one letter.
 * Each word is modified by replacing each letter sequentially with a blank, grouping words
 * by these blanked forms, and then connecting words in the same group.
 * 
 * Args:
 *     words (vector<string>): The list of words to be processed.
 * 
 * Returns:
 *     Graph: A graph where each word is a vertex and edges connect words differing by one letter.
 */
Graph buildGraph(vector<string> words) {
    Graph g(false); // Build an undirected graph

    map<string, vector<string>> d; // Dictionary to group words by their blanked forms

    // Iterate through each word
    for (size_t i = 0; i < words.size(); i++) {
        // Modify each letter in the word to create a blanked form and group by these forms
        for (size_t j = 0; j < words[i].length(); j++) {
            string bucket = getBlank(words[i], j);
            d[bucket].push_back(words[i]);
        }
    }

    // Connect all words in the same group with an edge
    for (auto& pair : d) {
        vector<string>& group = pair.second;
        for (size_t i = 0; i < group.size(); i++) {
            for (size_t j = i + 1; j < group.size(); j++) {
                g.addEdge(group[i], group[j]);
            }
        }
    }

    return g;
}

/**
 * Helper function to replace a specific character in a string with an underscore,
 * used to generate blanked forms of words.
 * 
 * Args:
 *     str (string): The original string.
 *     index (int): The position of the character to be replaced.
 * 
 * Returns:
 *     string: The modified string with the specified character replaced by an underscore.
 */
string getBlank(string str, int index) {
    string blank = str;
    blank[index] = '_';
    return blank;
}


/**
 * Class representing a depth-first search (DFS) specific graph structure. It maintains a map
 * of vertex identifiers to vertices, where each vertex has a list of connected vertices.
 * This class is tailored for performing depth-first searches, especially in directed or
 * undirected graphs.
 * 
 * Attributes:
 *     vertices (graph_t): A map from vertex identifiers to vertex structures containing
 *                          vertex data and adjacency lists.
 *     directional (bool): Indicates whether the graph is directed or not.
 */
class DFSGraph{
    typedef std::pair<int, std::list<int>> vertex_t;  // Pair containing vertex identifier and list of neighbors.
    typedef std::map<int, vertex_t> graph_t;  // Type alias for the graph data structure.

public:
    const bool directional;  // Flag to indicate if the graph is directed.

    /**
     * Constructor for DFSGraph that initializes it as either directed or undirected.
     * 
     * Args:
     *     directional (bool): Specifies whether the graph is directed.
     */
    DFSGraph(bool directional) : directional(directional) {}

    /**
     * Checks if a vertex with the given identifier exists in the graph.
     * 
     * Args:
     *     id (int): The identifier of the vertex to check.
     * 
     * Returns:
     *     bool: True if the vertex exists, false otherwise.
     */
    bool containsVertex(int id) {
        return vertices.count(id) > 0;
    }

    /**
     * Retrieves the adjacency list of a vertex identified by id.
     * 
     * Args:
     *     id (int): The identifier of the vertex.
     * 
     * Returns:
     *     std::list<int>&: A reference to the list containing the identifiers of connected vertices.
     */
    std::list<int>& getVertexConnections(int id) {
        return vertices[id].second;
    }

    /**
     * Adds a new vertex to the graph or clears the connections of an existing vertex.
     * 
     * Args:
     *     id (int): The identifier of the vertex to be added or reset.
     */
    void addVertex(int id) {
        if (containsVertex(id)) {
            vertices[id].second.clear();
        } else {
            vertices[id] = std::make_pair(id, std::list<int>());
        }
    }

    /**
     * Retrieves the vertex structure containing both the identifier and its connections.
     * 
     * Args:
     *     id (int): The identifier of the vertex.
     * 
     * Returns:
     *     vertex_t&: A reference to the vertex structure.
     */
    vertex_t& getVertex(int id) {
        return vertices[id];
    }

    /**
     * Adds an edge between two vertices. If the vertices do not exist, they are created.
     * 
     * Args:
     *     fromID (int): The identifier of the 'from' vertex.
     *     toID (int): The identifier of the 'to' vertex.
     */
    void addEdge(int fromID, int toID) {
        if (!containsVertex(fromID))
            addVertex(fromID);

        if (!containsVertex(toID))
            addVertex(toID);

        getVertexConnections(fromID).push_back(toID);
        if (!directional)
            getVertexConnections(toID).push_back(fromID);
    }

    /**
     * Performs a depth-first search across the graph, starting from any unvisited vertices.
     */
    void dfs() {
        std::list<int> visitedList;

        for (auto& cur : vertices) {
            if (std::find(visitedList.begin(), visitedList.end(), cur.first) == visitedList.end()) {
                dfsvisit(visitedList, cur.second);
            }
        }
    }

    /**
     * A helper function for the DFS that visits vertices recursively.
     * 
     * Args:
     *     visitedList (std::list<int>&): A list tracking visited vertex identifiers.
     *     vertex (vertex_t&): The current vertex structure to visit.
     */
    void dfsvisit(std::list<int>& visitedList, vertex_t& vertex) {
        visitedList.push_back(vertex.first);
        std::cout << "Visited Vertex With ID#: " << vertex.first << std::endl;

        for (int neighborID : vertex.second.second) {
            if (std::find(visitedList.begin(), visitedList.end(), neighborID) == visitedList.end()) {
                dfsvisit(visitedList, vertices[neighborID]);
            }
        }
    }

private:
    graph_t vertices;  // Map of vertices where key is the vertex ID and value is a pair of ID and list of connected vertices.
};
