#ifndef GRAPH_H
#define GRAPH_H
#include "GraphBase.hpp"
#include <vector>
#include <string>

class Graph : public GraphBase {
private:
    // Edge struct
    struct Edge {
        std::string to;
        unsigned long weight;
    };

    // Vertex struct
    struct Vertex {
        std::string label;
        std::vector<Edge> edges;
    };

    // Stores vertices
    std::vector<Vertex> vertices;

    // Finds vertex by label
    int findVertex(const std::string& label);
    unsigned long MAX_VALUE;

public:
    // Constructor and destructor
    Graph();
    ~Graph();

    // From GraphBase
    void addVertex(std::string label);
    void removeVertex(std::string label);
    void addEdge(std::string label1, std::string label2, unsigned long weight);
    void removeEdge(std::string label1, std::string label2);
    unsigned long shortestPath(std::string startLabel, std::string endLabel, 
                               std::vector<std::string> &path);
};
#endif