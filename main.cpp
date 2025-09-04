#include "Graph.hpp"
#include <iostream>
#include <string>
#include <vector>

// ANSI color codes for terminal output
#define RESET "\033[0m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"
#define CYAN "\033[1;36m"
#define BOLD "\033[1m"

// Function to print section header
void printHeader(const std::string &title) {
  std::cout << "\n" << YELLOW << "=========================\n";
  std::cout << "  " << title << "\n";
  std::cout << "=========================" << RESET << "\n";
}

// Function to print path results
void printPath(const std::string &start, const std::string &end,
               unsigned long distance, const std::vector<std::string> &path) {
  std::cout << GREEN << "Shortest path from '" << start << "' to '" << end
            << "': " << distance << RESET << "\n";
  std::cout << CYAN << "Path: " << RESET;
  for (size_t i = 0; i < path.size(); ++i) {
    std::cout << BLUE << BOLD << path[i] << RESET;
    if (i < path.size() - 1) {
      std::cout << " -> ";
    }
  }
  std::cout << "\n" << std::endl;
}

// Structure to define an edge
struct EdgeData {
  std::string from;
  std::string to;
  unsigned long weight;
};

int main() {
  // Graph 1
  printHeader("GRAPH 1");
  Graph g1;

  // Add vertices
  std::vector<std::string> vertices1 = {"1", "2", "3", "4", "5", "6"};
  for (const std::string &v : vertices1) {
    g1.addVertex(v);
  }

  // Add edges
  std::vector<EdgeData> edges1 = {
      {"1", "2", 7},  {"1", "3", 9},  {"1", "6", 14},
      {"2", "3", 10}, {"2", "4", 15}, {"3", "4", 11},
      {"3", "6", 2},  {"4", "5", 6},  {"5", "6", 9}};

  for (size_t i = 0; i < edges1.size(); ++i) {
    g1.addEdge(edges1[i].from, edges1[i].to, edges1[i].weight);
  }

  // Test shortest path
  std::vector<std::string> path1;
  unsigned long distance1 = g1.shortestPath("1", "5", path1);
  printPath("1", "5", distance1, path1);

  // Graph 2
  printHeader("GRAPH 2");
  Graph g2;

  // Add vertices
  std::vector<std::string> vertices2 = {"BSN", "LIB", "ENB", "MSC",
                                        "CAS", "SUB", "SUN"};
  for (const std::string &v : vertices2) {
    g2.addVertex(v);
  }

  // Add edges
  std::vector<EdgeData> edges2 = {
      {"BSN", "LIB", 871},  {"BSN", "CAS", 1672}, {"BSN", "MSC", 2355},
      {"SUN", "SUB", 1265}, {"LIB", "MSC", 1615}, {"LIB", "SUN", 1847},
      {"ENB", "SUN", 2885}, {"ENB", "CAS", 454},  {"ENB", "LIB", 1078}};

  for (size_t i = 0; i < edges2.size(); ++i) {
    g2.addEdge(edges2[i].from, edges2[i].to, edges2[i].weight);
  }

  // Test paths
  std::vector<std::string> path2a;
  unsigned long distance2a = g2.shortestPath("ENB", "SUN", path2a);
  printPath("ENB", "SUN", distance2a, path2a);

  std::vector<std::string> path2b;
  unsigned long distance2b = g2.shortestPath("LIB", "CAS", path2b);
  printPath("LIB", "CAS", distance2b, path2b);

  // Example 1
  printHeader("General Locations");
  Graph g3;

  // General locations
  std::vector<std::string> locations = {"Home", "School",  "Store",
                                        "Park", "Library", "CoffeeShop",
                                        "Gym",  "BusStop"};
  for (const std::string &loc : locations) {
    g3.addVertex(loc);
  }

  // Distances
  std::vector<EdgeData> routes = {
      {"Home", "School", 15},       {"Home", "Store", 10},
      {"Home", "BusStop", 5},       {"School", "Library", 8},
      {"School", "Park", 12},       {"School", "CoffeeShop", 7},
      {"Store", "Park", 9},         {"Store", "BusStop", 6},
      {"Store", "Gym", 15},         {"Park", "Library", 10},
      {"Library", "CoffeeShop", 4}, {"CoffeeShop", "Gym", 12},
      {"BusStop", "School", 12},    {"BusStop", "Gym", 20}};

  for (size_t i = 0; i < routes.size(); ++i) {
    g3.addEdge(routes[i].from, routes[i].to, routes[i].weight);
  }

  std::vector<std::string> path3a;
  unsigned long distance3a = g3.shortestPath("BusStop", "Home", path3a);
  printPath("BusStop", "Home", distance3a, path3a);

  std::vector<std::string> path3b;
  unsigned long distance3b = g3.shortestPath("Home", "Gym", path3b);
  printPath("Home", "Gym", distance3b, path3b);

  std::vector<std::string> path3c;
  unsigned long distance3c = g3.shortestPath("Store", "Library", path3c);
  printPath("Store", "Library", distance3c, path3c);

  // Example 2
  printHeader("FLORIDA CITIES");
  Graph g4;

  // Florida cities 
  std::vector<std::string> cities = {
      "Tampa",           "Clearwater",  "Miami",          "Orlando",
      "Jacksonville",    "Tallahassee", "St. Petersburg", "Fort Lauderdale",
      "West Palm Beach", "Gainesville"};

  // Add every vertex
  for (const auto &loc : cities) {
    g4.addVertex(loc);
  }

  // Distances
  std::vector<EdgeData> FLCities = {
    {"Tampa", "Clearwater", 24},          
    {"Tampa", "Orlando", 85},            
    {"Tampa", "St. Petersburg", 25},      
    {"Tampa", "Fort Lauderdale", 260},    
    {"Clearwater", "Miami", 280},        
    {"Clearwater", "Orlando", 107},      
    {"Miami", "Gainesville", 335},       
    {"Orlando", "Jacksonville", 140},    
    {"Orlando", "Fort Lauderdale", 215},  
    {"Jacksonville", "Tallahassee", 164},
    {"Jacksonville", "West Palm Beach", 300}, 
    {"Tallahassee", "St. Petersburg", 244},  
    {"St. Petersburg", "West Palm Beach", 220}, 
    {"Fort Lauderdale", "West Palm Beach", 50}, 
    {"Fort Lauderdale", "Gainesville", 300},    
    {"West Palm Beach", "Gainesville", 285}    
  };

  for (const auto &e : FLCities) {
    g4.addEdge(e.from, e.to, e.weight);
  }

  std::vector<std::string> path;
  unsigned long dist;

  dist = g4.shortestPath("Tampa", "Miami", path);
  printPath("Tampa", "Miami", dist, path);

  dist = g4.shortestPath("Miami", "Tallahassee", path);
  printPath("Miami", "Tallahassee", dist, path);

  dist = g4.shortestPath("West Palm Beach", "Tampa", path);
  printPath("West Palm Beach", "Tampa", dist, path);

  return 0;
}