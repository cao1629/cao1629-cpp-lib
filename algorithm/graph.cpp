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

void doDfs(int vertex, std::unordered_set<int> &visited, std::vector<int> &result, const std::vector<std::vector<int>> &graph) {
  result.push_back(vertex);
  visited.insert(vertex);

  for (const auto &neighbor : graph[vertex]) {
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


void HasCycleUndirected::dfs(int vertex, int parent) {
  if (found) {
    return;
  }
  visited.insert(vertex);

  for (auto neighbor : graph[vertex]) {
    if (visited.find(neighbor) == visited.cend()) {
      dfs(neighbor, vertex);
    } else if (neighbor != parent) {
      found = true;
      return;
    }
  }
}

bool HasCycleUndirected::DetectCycle() {
  dfs(0, -1);
  return found;
}


void HasCycleDirected::dfs(int vertex) {
  if (found) {
    return;
  }

  visited.insert(vertex);

  gray_set.insert(vertex);
  for (auto neighbor : graph[vertex]) {
    if (visited.find(neighbor) != visited.cend()) {
      if (gray_set.find(neighbor) != gray_set.cend()) {
        found = true;
        return;
      }
    } else {
      dfs(neighbor);
    }
  }
  gray_set.erase(vertex);
}

bool HasCycleDirected::DetectCycle() {
  dfs(0);
  return found;
}

}

