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


}