/**
 * @file Graph3.hh
 * @author Yuezuo Liu (522204435@11.com)
 * @brief header file of class Graph3.
 * @version 0.1
 * @date 2022-08-04
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef CPP_PROGRAM_ASSIGNMENT3_INCLUDE_GRAPH3_HH_
#define CPP_PROGRAM_ASSIGNMENT3_INCLUDE_GRAPH3_HH_

#include <cstdio>
#include <fstream>
#include <vector>

#define MAX_NAME_LEN 20

/**
 * @brief class Graph3 using adjcency list.
 *
 * class Graph3 using adjacency list.
 * loads a map from file, and computes shortest path from given start to
 * destination.
 */
class Graph3
{
 public:
  Graph3() = default;

  ~Graph3() = default;

  /**
   * @brief loads map from file.
   *
   * @param file_name file name to load.
   * @return true if load successes.
   * @return false if load fails.
   */
  bool loadMap(char file_name[]);

  /**
   * @brief construct adjacency list given after loading a map.
   *
   * @return true if construction successes.
   * @return false if construction fails.
   */
  bool constructAdjacencyList();

  /**
   * @brief print shortest path from start to destination.
   *
   * @param start_row row coordinate of start.
   * @param start_col column coordinate of start.
   * @param end_row row coordinate of destination.
   * @param end_col column coordinate of destination.
   */
  void shortestPath(std::pair<int, int> start, std::pair<int, int> end, std::string method) const;

  /**
   * @brief print loaded map.
   *
   */
  void showMap() const
  {
    for (int i = 0; i < _map.size(); ++i) {
      for (int map_unit : _map[i])
        printf("%d ", map_unit);
      printf("\n");
    }
  }

  /**
   * @brief print adjacency list.
   *
   */
  void showAdjacencyList() const
  {
    for (int out_idx = 0; out_idx < _adjacency_list.size(); ++out_idx) {
      if (_adjacency_list[out_idx].size() > 0) {
        printf("[%2d]", out_idx);
        for (std::pair<int, double> edge : _adjacency_list[out_idx])
          printf(" --%2.1lf--> (%2d)", edge.second, edge.first);
        printf("\n");
      }
    }
  }

 private:
  // obstacle-node holds a place in adj_list, pair = [in_index, weight]
  std::vector<std::vector<std::pair<int, double>>> _adjacency_list;
  std::vector<std::vector<int>> _map;

  int _map_width;
  int _map_height;
};

#endif