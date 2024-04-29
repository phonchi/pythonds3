#!/usr/bin/env python3
"""
Bradley N. Miller, David L. Ranum
Problem Solving with Algorithms and Data Structures using Python
Copyright 2005
Updated by Roman Yasinovskyy, 2017
"""

import heapq
import sys
from typing import Any, Iterator, Union


class Vertex:
    """
    Represents a vertex in a graph with various attributes like neighbors, color, distance,
    previous vertex, and discovery and closing times used in graph traversal algorithms.
    
    Attributes:
        key (Any): Unique identifier of the vertex.
        neighbors (dict): A dictionary mapping adjacent vertices to edge weights.
        color (str): Marker used during traversal (white, gray, black).
        distance (int): Distance from the start vertex in path finding algorithms.
        previous (Vertex): Previous vertex in the path of minimum cost.
        discovery_time (int): Discovery time in DFS.
        closing_time (int): Closing time in DFS.
    """

    def __init__(self, key: Any) -> None:
        """
        Initializes a new vertex with the specified key.
        
        Args:
            key (Any): The unique identifier for the vertex.
        """
        self._key = key
        self._neighbors: dict["Vertex", Union[int, None]] = {}
        self._color = "white"
        self._distance = sys.maxsize
        self._previous = None
        self._discovery_time = 0
        self._closing_time = 0

    def __lt__(self, other: "Vertex") -> bool:
        """
        Defines behavior for the less-than operator, which is used in priority queues.
        
        Args:
            other (Vertex): Another vertex to compare with.
        
        Returns:
            bool: True if this vertex's key is less than the other vertex's key.
        """
        return self.key < other.key

    def get_key(self) -> Any:
        """
        Returns the key of the vertex.
        
        Returns:
            Any: The key of the vertex.
        """
        return self._key

    key = property(get_key)

    def get_neighbor(self, other: "Vertex") -> Union[int, None]:
        """
        Returns the weight of the edge to a specified neighboring vertex.
        
        Args:
            other (Vertex): The neighbor vertex.
        
        Returns:
            Union[int, None]: The weight of the edge to the neighbor, or None if not connected.
        """
        return self._neighbors.get(other, None)

    def set_neighbor(self, other: "Vertex", weight: int = 0) -> None:
        """
        Connects this vertex to another vertex with an edge of specified weight.
        
        Args:
            other (Vertex): The neighbor vertex to connect to.
            weight (int, optional): The weight of the edge. Defaults to 0 if not specified.
        """
        self._neighbors[other] = weight

    def get_neighbors(self):
        """
        Returns all adjacent vertices (neighbors) of this vertex.
        
        Returns:
            Iterator[Vertex]: An iterator over the neighboring vertices.
        """
        return self._neighbors.keys()

    def get_color(self) -> str:
        """
        Returns the color of the vertex, used in traversal algorithms.
        
        Returns:
            str: The color of the vertex.
        """
        return self._color

    def set_color(self, color: str) -> None:
        """
        Sets the color of the vertex, used in traversal algorithms.
        
        Args:
            color (str): The new color to set for the vertex.
        """
        self._color = color

    color = property(get_color, set_color)

    def get_distance(self) -> int:
        """
        Returns the current distance from the start vertex in path-finding algorithms.
        
        Returns:
            int: The distance of the vertex.
        """
        return self._distance

    def set_distance(self, distance: int) -> None:
        """
        Sets the distance of this vertex from the start vertex in path-finding algorithms.
        
        Args:
            distance (int): The new distance to set for the vertex.
        """
        self._distance = distance

    distance = property(get_distance, set_distance)

    def get_previous(self) -> Union["Vertex", None]:
        """
        Returns the previous vertex in the path of minimum cost.
        
        Returns:
            Union[Vertex, None]: The previous vertex in the path, or None if no previous vertex.
        """
        return self._previous

    def set_previous(self, previous: "Vertex") -> None:
        """
        Sets the previous vertex in the path of minimum cost.
        
        Args:
            previous (Vertex): The vertex to set as previous.
        """
        self._previous = previous

    previous = property(get_previous, set_previous)

    def get_discovery_time(self) -> int:
        """
        Returns the discovery time in DFS.
        
        Returns:
            int: The discovery time of the vertex.
        """
        return self._discovery_time

    def set_discovery_time(self, discovery_time: int) -> None:
        """
        Sets the discovery time of the vertex during DFS.
        
        Args:
            discovery_time (int): The discovery time to set for the vertex.
        """
        self._discovery_time = discovery_time

    discovery_time = property(get_discovery_time, set_discovery_time)

    def get_closing_time(self) -> int:
        """
        Returns the closing time of the vertex in DFS.
        
        Returns:
            int: The closing time of the vertex.
        """
        return self._closing_time

    def set_closing_time(self, closing_time: int) -> None:
        """
        Sets the closing time of the vertex during DFS.
        
        Args:
            closing_time (int): The closing time to set for the vertex.
        """
        self._closing_time = closing_time

    closing_time = property(get_closing_time, set_closing_time)

    def __str__(self) -> str:
        """
        Provides a string representation of the vertex, including its key, color, distance,
        discovery time, closing time, and previous vertex key.
        
        Returns:
            str: A formatted string representation of the vertex.
        """
        key = str(self._key)
        color = str(self._color)
        distance = str(self._distance) if self._distance != sys.maxsize else 'inf'
        discovery_time = str(self._discovery_time)
        closing_time = str(self._closing_time)
        previous_key = str(getattr(self._previous, '_key', 'None'))
        
        return f"{key:^8}|{color:^8}|{distance:^8}|{discovery_time:^8}|{closing_time:^8}|{previous_key}"


class Graph:
    """
    Represents a graph using an adjacency list approach, supporting various algorithms such as BFS,
    DFS, Dijkstra's, Bellman-Ford, and Prim's algorithm to compute paths and spanning trees.
    
    Attributes:
        vertices (dict): A dictionary mapping vertex keys to Vertex instances.
        edges (dict): A dictionary mapping pairs of vertices to edge weights.
        time (int): Global time counter used in DFS.
    """

    def __init__(self) -> None:
        """
        Initializes a new empty graph.
        """
        self._vertices: dict["Vertex", list] = {}
        self._edges: dict[tuple["Vertex", "Vertex"], int] = {}
        self._time = 0

    def __iter__(self) -> Iterator:
        """
        Returns an iterator over the vertices in the graph.
        
        Returns:
            Iterator[Vertex]: An iterator over the vertices in the graph.
        """
        return iter(self._vertices.values())

    def size(self) -> int:
        """
        Returns the number of vertices in the graph.
        
        Returns:
            int: The number of vertices in the graph.
        """
        return len(self._vertices)

    def __len__(self) -> int:
        """
        Returns the number of vertices in the graph. This is equivalent to the size method.
        
        Returns:
            int: The number of vertices in the graph.
        """
        return len(self._vertices)

    def __contains__(self, key: Any) -> bool:
        """
        Checks if a vertex with the given key exists in the graph.
        
        Args:
            key (Any): The key to check for in the graph.
        
        Returns:
            bool: True if a vertex with the key exists, False otherwise.
        """
        return key in self._vertices

    def get_vertex(self, key: Any) -> Union["Vertex", None]:
        """
        Finds and returns the vertex in the graph with the specified key.
        
        Args:
            key (Any): The key of the vertex to find.
        
        Returns:
            Union[Vertex, None]: The vertex if found, None otherwise.
        """
        return self._vertices.get(key, None)

    def set_vertex(self, key) -> None:
        """
        Adds a new vertex to the graph if it does not already exist, using the specified key.
        
        Args:
            key (Any): The key of the new vertex to add.
        """
        self._vertices[key] = Vertex(key)

    def add_edge(self, from_vertex, to_vertex, weight: int = 0) -> None:
        """
        Adds a directed edge from one vertex to another with an optional weight.
        
        Args:
            from_key (Any): The key of the vertex from which the edge originates.
            to_key (Any): The key of the vertex to which the edge points.
            weight (int, optional): The weight of the edge. Defaults to 0 if not specified.
        """
        if from_vertex not in self._vertices:
            self.set_vertex(from_vertex)
        if to_vertex not in self._vertices:
            self.set_vertex(to_vertex)
        self._vertices[from_vertex].set_neighbor(self._vertices[to_vertex], weight)
        self._edges[(from_vertex, to_vertex)] = weight

    def get_vertices(self):
        """
        Returns a list of keys for all vertices in the graph.
        
        Returns:
            list[Any]: A list of vertex keys.
        """
        return self._vertices.keys()

    def get_edges(self):
        """
        Returns a list of tuples representing the edges in the graph, each tuple containing the keys
        of the from and to vertices and the weight of the edge.
        
        Returns:
            list[tuple]: A list of edges as tuples.
        """
        return self._edges.keys()

    def reset_distances(self, default_distance: int = sys.maxsize) -> None:
        """
        Resets the distances of all vertices in the graph, typically used before running path-finding algorithms.
        
        Args:
            default_distance (int, optional): The distance value to reset each vertex's distance to.
                                             Defaults to sys.maxsize.
        """
        for vertex in self:
            vertex.distance = default_distance

    def bfs(self, start: "Vertex") -> None:
        """
        Performs a breadth-first search starting from the specified vertex, marking distances from the start.
        
        Args:
            start (Vertex): The vertex from which BFS starts.
        """
        start.distance = 0
        start.previous = None
        vert_queue = [start]
        while vert_queue:
            current_vert = vert_queue.pop(0)
            for neigh in current_vert.get_neighbors():
                if neigh.color == "white":
                    neigh.color = "gray"
                    neigh.distance = current_vert.distance + 1
                    neigh.previous = current_vert
                    vert_queue.append(neigh)
            current_vert.color = "black"

    def dfs(self) -> None:
        """
        Performs a depth-first search on the graph, marking discovery and closing times.
        """
        for vertex in self:
            if vertex.color == "white":
                self.dfs_visit(vertex)

    def dfs_visit(self, start: "Vertex") -> None:
        """
        A helper function for DFS that visits vertices recursively.
        
        Args:
            start (Vertex): The vertex to start the DFS visit from.
        """
        start.color = "gray"
        self._time = self._time + 1
        start.discovery_time = self._time
        for next_vertex in start.get_neighbors():
            if next_vertex.color == "white":
                next_vertex.set_previous(start)
                self.dfs_visit(next_vertex)
        start.color = "black"
        self._time = self._time + 1
        start.closing_time = self._time

    def traverse(self, src: "Vertex", dst: "Vertex") -> None:
        """
        Traces and prints the path from the source vertex to the destination vertex, assuming that path finding
        has already been executed and paths have been recorded in the previous attributes of vertices.
        
        Args:
            src_key (Any): The key of the source vertex.
            dst_key (Any): The key of the destination vertex.
        """
        path = []
        current = self.get_vertex(dst)
        while current:
            path.append(current)
            current = current.previous
        print(
            f"Path from {self.get_vertex(src).key} "
            + f"to {self.get_vertex(dst).key} "
            + f"({self.get_vertex(dst).distance}): "
            + f"{' '.join(vertex.key for vertex in reversed(path))}"
        )

    def dijkstra(self, start: "Vertex") -> None:
        """
        Implements Dijkstra's algorithm to find the shortest path from the start vertex to all other vertices in the graph.
        
        Args:
            start (Vertex): The vertex from which Dijkstra's algorithm starts.
        """
        start.distance = 0
        not_yet_visited: list[list[Union[int, "Vertex"]]] = [[start.distance, start]]
        heapq.heapify(not_yet_visited)
        while not_yet_visited:
            current_vertex = heapq.heappop(not_yet_visited)[1]
            for next_vertex in current_vertex.get_neighbors():
                new_distance = current_vertex.distance + current_vertex.get_neighbor(
                    next_vertex
                )
                if new_distance < next_vertex.distance:
                    next_vertex.distance = new_distance
                    next_vertex.previous = current_vertex
                    found = False
                    for vertex in not_yet_visited:
                        if vertex[1].key == next_vertex.key:
                            vertex[0] = next_vertex.distance
                            heapq.heapify(not_yet_visited)
                            found = True
                    if not found:
                        heapq.heappush(
                            not_yet_visited, [next_vertex.distance, next_vertex]
                        )

    def bellman_ford(self, start: "Vertex") -> None:
        """
        Implements the Bellman-Ford algorithm to compute the shortest paths from the start vertex to all other vertices.
        It can detect negative weight cycles in the graph.
        
        Args:
            start (Vertex): The vertex from which Bellman-Ford starts.
        
        Raises:
            ValueError: If a negative-weight cycle is detected in the graph.
        """
        start.distance = 0
        for _ in range(len(self._vertices)):
            for edge in self._edges:
                if (
                    self.get_vertex(edge[0]).distance + self._edges[edge]
                    < self.get_vertex(edge[1]).distance
                ):
                    self.get_vertex(edge[1]).distance = (
                        self.get_vertex(edge[0]).distance + self._edges[edge]
                    )
                    self.get_vertex(edge[1]).previous = self.get_vertex(edge[0])
        for edge in self._edges:
            if (
                self.get_vertex(edge[0]).distance + self._edges[edge]
                < self.get_vertex(edge[1]).distance
            ):
                raise ValueError("Graph contains a negative-weight cycle")

    def prim(self, start: "Vertex") -> None:
        """
        Implements Prim's algorithm to find a minimum spanning tree starting from the given vertex.
        
        Args:
            start (Vertex): The vertex from which Prim's algorithm starts.
        """
        start.distance = 0
        not_in_a_tree = [[vertex.distance, vertex] for vertex in self]
        heapq.heapify(not_in_a_tree)
        while not_in_a_tree:
            current_vertex = heapq.heappop(not_in_a_tree)[1]
            for next_vertex in current_vertex.get_neighbors():
                new_distance = current_vertex.get_neighbor(next_vertex)
                if (
                    any(item[1] == next_vertex for item in not_in_a_tree)
                    and new_distance < next_vertex.distance
                ):
                    next_vertex.previous = current_vertex
                    next_vertex.distance = new_distance
                    for item in not_in_a_tree:
                        if item[1] == next_vertex:
                            item[0] = new_distance
                            heapq.heapify(not_in_a_tree)
                            break
