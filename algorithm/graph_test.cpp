#include "graph.h"
#include <iostream>
#include <gtest/gtest.h>
#include <stack>

namespace cao1629 {
static const std::vector<std::pair<int, int>> graph1{
  {0, 1}, {0, 2}, {0, 5}, {0, 6}, {3, 4}, {3, 5}, {4, 5}
};


void doDfs(int vertex, std::unordered_set<int>& visited, std::vector<int>& result,
           const std::vector<std::vector<int>>& graph) {
  result.push_back(vertex);
  visited.insert(vertex);

  for (const auto& neighbor : graph[vertex]) {
    if (visited.find(neighbor) == visited.cend()) {
      doDfs(neighbor, visited, result, graph);
    }
  }
}

std::vector<int> Dfs(std::vector<std::vector<int>> graph) {
  std::vector<int> result;
  std::unordered_set<int> visited;

  doDfs(0, visited, result, graph);
  return result;
}

std::vector<int> Bfs(std::vector<std::vector<int>> graph) {
  std::queue<int> q;
  q.push(0);
  std::unordered_set<int> visited;
  visited.insert(0);
  std::vector<int> result;

  while (!q.empty()) {
    result.push_back(q.front());
    int vertex = q.front();
    q.pop();

    for (auto neighbor : graph[vertex]) {
      if (visited.find(neighbor) == visited.cend()) {
        visited.insert(neighbor);
        q.push(neighbor);
      }
    }
  }

  return result;
}

TEST(GraphTest, TestDfs) {
  auto graph = CreateUndirectedGraph(graph1);
  auto result = Dfs(graph);
  for (auto vertex : result) {
    std::cout << vertex << std::endl;
  }
}

TEST(GraphTest, TestBfs) {
  auto graph = CreateUndirectedGraph(graph1);
  auto result = Bfs(graph);
  for (auto vertex : result) {
    std::cout << vertex << std::endl;
  }
}

class HasCycleUndirected {
public:
  HasCycleUndirected(const std::vector<std::pair<int, int>> edges) {
    // copy assignment
    graph = CreateUndirectedGraph(edges);
    found = false;
  }

  bool DetectCycle() {
    dfs(0, -1);
    return found;
  }

  void dfs(int vertex, int parent) {
    if (found) {
      return;
    }
    visited.insert(vertex);

    for (auto neighbor : graph[vertex]) {
      if (visited.find(neighbor) == visited.cend()) {
        dfs(neighbor, vertex);
      }
      else if (neighbor != parent) {
        found = true;
        return;
      }
    }
  }

  std::vector<std::vector<int>> graph;
  std::unordered_set<int> visited;
  bool found;
};


TEST(GraphTest, TestHasCycleUndirected) {
  std::vector<std::pair<int, int>> edges_with_cycle{
    {0, 1}, {1, 2}, {2, 0}
  };
  HasCycleUndirected cycle_detector(edges_with_cycle);
  EXPECT_TRUE(cycle_detector.DetectCycle());
}

class HasCycleDirected {
public:
  HasCycleDirected(const std::vector<std::pair<int, int>> edges) {
    // copy assignment
    graph = CreateDirectedGraph(edges);
    found = false;
  }

  void dfs(int vertex) {
    if (found) {
      return;
    }

    visited.insert(vertex);

    gray_set.insert(vertex);
    for (auto neighbor : graph[vertex]) {
      if (gray_set.find(neighbor) != gray_set.cend()) {
        found = true;
        return;
      }

      if (visited.find(neighbor) == visited.cend()) {
        dfs(neighbor);
      }
    }
    gray_set.erase(vertex);
  }

  bool DetectCycle() {
    dfs(0);
    return found;
  }

  std::vector<std::vector<int>> graph;
  std::unordered_set<int> visited;
  std::unordered_set<int> gray_set;
  bool found;
};


TEST(GraphTest, TestHasCycleDirected) {
  std::vector<std::pair<int, int>> edges_with_cycle{
    {0, 1}, {1, 2}, {2, 0}
  };
  HasCycleDirected cycle_detector(edges_with_cycle);
  EXPECT_TRUE(cycle_detector.DetectCycle());
}


class PathFinderUndirectedGraph {
public:
  PathFinderUndirectedGraph(std::vector<std::pair<int, int>> edges) {
    graph = CreateUndirectedGraph(edges);
    found = false;
    // predecessors = std::vector<int>(edges.size(), 0);
  }

  // DFS
  // Find one path. There might be more than one path, but we don't care.
  std::vector<int> FindPath(int s, int d) {
    visited.clear();
    grey.clear();
    result.clear();
    dfs(s, d);
    return result;
  }

  void dfs(int v, int d) {
    if (found) {
      return;
    }

    visited.insert(v);
    grey.push_back(v);

    if (v == d) {
      found = true;
      result = grey;
      return;
    }

    for (auto w : graph[v]) {
      if (visited.find(w) == visited.cend()) {
        dfs(w, d);
      }
    }
    grey.pop_back();
  }


  // BFS
  std::vector<int> FindShortestPath(int s, int d) {
  }

  std::vector<std::vector<int>> graph;
  std::unordered_set<int> visited;
  bool found;
  std::vector<int> grey;
  std::vector<int> result;
};


TEST(GraphTest, TestFindPathUndirectedGraph) {
  PathFinderUndirectedGraph solver(graph1);
  std::vector<int> result = solver.FindPath(0, 4);
  std::vector<int> path1{0, 5, 3, 4};
  std::vector<int> path2{0, 5, 4};
  bool match = (result == path1 || result == path2);
  EXPECT_TRUE(match);
}
}
