/**
 * @file main.cc
 * @author Yuezuo Liu (522204435@qq.com)
 * @brief defines main function containing test code.
 * @version 0.1
 * @date 2022-08-04
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <cstdio>

#include "Graph3.hh"

int main()
{
  Graph3 g;
  g.loadMap("../data/map1.txt");
  g.showMap();

  g.constructAdjacencyList();
  g.showAdjacencyList();

  std::pair<int, int> start{0, 0};
  std::pair<int, int> end{3, 7};
  g.shortestPath(start, end, "aStar");

  return 0;
}