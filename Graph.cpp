#include "Graph.hpp"
#include <iostream>

// Store vertex info
struct VertexPair {
  int index;
  std::string to;
  bool edgeExists;
};

// Constructor and Destructor
Graph::Graph() {
  MAX_VALUE = 0xFFFFFFFF; // Needs Max_Value to be big enough to hold the sum of all edge weights
}
Graph::~Graph() {
}

// Finds a vertex by label
int Graph::findVertex(const std::string &label) {
  for (size_t i = 0; i < vertices.size(); ++i) {
    if (vertices[i].label == label) {
      return i;
    }
  }
  return -1; // Does not exist
}

// Creates a vertex with the label
void Graph::addVertex(std::string label) {
  // Checks if vertex exists
  if (findVertex(label) != -1) {
    return;
  }

  // Create new vertex
  Vertex newVertex;
  newVertex.label = label;

  // Add to vertex to the vertices vector
  vertices.push_back(newVertex);
}

// Remove a vertex with its edges
void Graph::removeVertex(std::string label) {
  // Checks if vertex exists
  int index = findVertex(label);
  if (index == -1) {
    return;
  }

  // Remove the vertex from vertices vector
  vertices.erase(vertices.begin() + index);

  // Remove edges pointing to this vertex
  for (Vertex &vertex : vertices) {
    for (size_t i = 0; i < vertex.edges.size(); ++i) {
      if (vertex.edges[i].to == label) {
        vertex.edges.erase(vertex.edges.begin() + i);
        --i;
      }
    }
  }
}

// Creates an edge between two vertices
void Graph::addEdge(std::string label1, std::string label2, unsigned long weight) {
  // Find vertices by label
  int index1 = findVertex(label1);
  int index2 = findVertex(label2);

  // Check if the vertices exist and are different
  if (index1 == -1 || index2 == -1 || label1 == label2) {
    return;
  }

  // Set up vertex pairs for processing
  VertexPair pairs[2] = {
    {index1, label2, false},
    {index2, label1, false}
  };

  for (int i = 0; i < 2; i++) {
    // Check if edge exists, create it if not
    auto& edges = vertices[pairs[i].index].edges;
    for (const Edge &edge : edges) {
      if (edge.to == pairs[i].to) {
        pairs[i].edgeExists = true;
        break;
      }
    }
    if (!pairs[i].edgeExists) {
      edges.push_back({pairs[i].to, weight});
    }
  }
}

// Remove an edge between two vertices
void Graph::removeEdge(std::string label1, std::string label2) {
  // Find vertices
  int index1 = findVertex(label1);
  int index2 = findVertex(label2);

  // Check if vertices exist
  if (index1 == -1 || index2 == -1) {
    return;
  }

  // Set up vertex pairs for removal
  VertexPair pairs[2] = {
    {index1, label2, false},
    {index2, label1, false}
  };

  // Remove both edges
  for (int i = 0; i < 2; i++) {
    std::vector<Edge> &edges = vertices[pairs[i].index].edges;
    for (size_t j = 0; j < edges.size(); ++j) {
      if (edges[j].to == pairs[i].to) {
        edges.erase(edges.begin() + j);
        break;
      }
    }
  }
}

// Find shortest path using Dijkstra's algorithm
unsigned long Graph::shortestPath(std::string startLabel, std::string endLabel,
                                  std::vector<std::string> &path) {
  // Clear the output path vector
  path.clear();

  // Find both vertices
  int startIndex = findVertex(startLabel);
  int endIndex = findVertex(endLabel);

  // Check if both vertices exist
  if (startIndex == -1 || endIndex == -1) {
    return MAX_VALUE; // Wrong way
  }

  // Edge case: start and end are the same
  if (startIndex == endIndex) {
    path.push_back(startLabel);
    return 0;
  }

  // Reserve memory for vectors
  size_t vertexCount = vertices.size();
  // Tracks all used vertices
  std::vector<bool> processed(vertexCount, false);
  // Stores all distances from start
  std::vector<unsigned long> distances(vertexCount, MAX_VALUE);
  // Store previous vertex in path
  std::vector<int> previous(vertexCount, -1);

  // Distance starts at 0
  distances[startIndex] = 0;

  for (size_t i = 0; i < vertexCount; ++i) {
    // Find unused vertex with smallest distance
    int current = -1;
    unsigned long minimumDistance = MAX_VALUE;

    for (size_t j = 0; j < vertexCount; ++j) {
      if (!processed[j] && distances[j] < minimumDistance) {
        minimumDistance = distances[j];
        current = j;
      }
    }

    // No path to vertex
    if (current == -1 || current == endIndex) {
      break;
    }

    processed[current] = true;

    // Finds adjacent vertex
    for (const Edge &edge : vertices[current].edges) {
      // Neighbor index
      int neighborIndex = -1;
      for (size_t j = 0; j < vertexCount; ++j) {
        if (vertices[j].label == edge.to) {
          neighborIndex = j;
          break;
        }
      }

      // Skip if neighbor already processed
      if (neighborIndex == -1 || processed[neighborIndex]) {
        continue;
      }

      // Calculate new distance
      unsigned long newDistance = distances[current] + edge.weight;

      // Update if better path was found
      if (newDistance < distances[neighborIndex]) {
        distances[neighborIndex] = newDistance;
        previous[neighborIndex] = current;
      }
    }
  }

  // Check if path exists
  if (distances[endIndex] == MAX_VALUE) {
    return MAX_VALUE;
  }

  // Reconstruct path
  std::vector<std::string> reversePath;
  reversePath.reserve(vertexCount);

  int current = endIndex;
  while (current != -1) {
    reversePath.push_back(vertices[current].label);
    current = previous[current];
  }

  // Reverse to get path from start to end
  path.reserve(reversePath.size());
  for (int i = reversePath.size() - 1; i >= 0; --i) {
    path.push_back(reversePath[i]);
  }

  // Returns total distance
  return distances[endIndex];
}