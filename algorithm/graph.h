#pragma once
#include <vector>
#include <unordered_set>

namespace cao1629 {

std::vector<std::vector<int>> CreateUndirectedGraph(std::vector<std::pair<int, int>> edges);

std::vector<std::vector<int>> CreateDirectedGraph(std::vector<std::pair<int, int>> edges);

// Assume there is only one connected component
std::vector<int> Dfs(std::vector<std::vector<int>> graph);

void doDfs(int vertex, std::unordered_set<int> &visited, std::vector<int> &result, const std::vector<std::vector<int>> &graph);

// Assume there is only one connected component
std::vector<int> Bfs(std::vector<std::vector<int>> graph);

class HasCycleUndirected {
public:
  HasCycleUndirected(const std::vector<std::pair<int, int>> edges) {
    // copy assignment
    graph = CreateUndirectedGraph(edges);
    found = false;
  }

  bool DetectCycle();

  void dfs(int vertex, int parent);

  std::vector<std::vector<int>> graph;
  std::unordered_set<int> visited;
  bool found;
};

class HasCycleDirected {
public:
  HasCycleDirected(const std::vector<std::pair<int, int>> edges) {
    // copy assignment
    graph = CreateDirectedGraph(edges);
    found = false;
  }

  void dfs(int vertex);

  bool DetectCycle();

  std::vector<std::vector<int>> graph;
  std::unordered_set<int> visited;
  std::unordered_set<int> gray_set;
  bool found;
};

}