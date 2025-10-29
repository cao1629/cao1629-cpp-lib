#include "algorithm/graph.h"
#include <queue>

namespace cao1629 {
// vertex number starts from 0
std::vector<std::vector<int>> CreateUndirectedGraph(std::vector<std::pair<int, int>> edges) {
  int max_vertex = -1;
  for (const auto &edge : edges) {
    max_vertex = std::max(max_vertex, std::max(edge.first, edge.second));
  }

  std::vector<std::vector<int>> graph(max_vertex + 1);
  for (const auto &edge : edges) {
    graph[edge.first].push_back(edge.second);
    graph[edge.second].push_back(edge.first);
  }
  return graph;
}


std::vector<std::vector<int>> CreateDirectedGraph(std::vector<std::pair<int, int>> edges) {
  int max_vertex = -1;
  for (const auto &edge : edges) {
    max_vertex = std::max(max_vertex, std::max(edge.first, edge.second));
  }

  std::vector<std::vector<int>> graph(max_vertex + 1);
  for (const auto &edge : edges) {
    graph[edge.first].push_back(edge.second);
  }
  return graph;
}


}

