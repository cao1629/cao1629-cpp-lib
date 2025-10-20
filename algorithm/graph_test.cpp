#include "graph.h"
#include <iostream>
#include <gtest/gtest.h>

namespace cao1629 {

static const std::vector< std::pair<int, int>> graph1{
  {0, 1}, {0, 2}, {0, 5}, {0, 6}, {3, 4}, {3, 5}, {4, 5}
};

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

TEST(GraphTest, TestHasCycleUndirected) {
  std::vector<std::pair<int, int>> edges_with_cycle{
  {0, 1}, {1, 2}, {2, 0}
  };
  HasCycleUndirected cycle_detector(edges_with_cycle);
  EXPECT_TRUE(cycle_detector.DetectCycle());
}

TEST(GraphTest, TestHasCycleDirected) {
  std::vector<std::pair<int, int>> edges_with_cycle{
  {0, 1}, {1, 2}, {2, 0}
  };
  HasCycleDirected cycle_detector(edges_with_cycle);
  EXPECT_TRUE(cycle_detector.DetectCycle());
}



}