/**
 * @file Graph3.cc
 * @author Yuezuo Liu (you@domain.com)
 * @brief define class functions in class Graph3.
 * @version 0.1
 * @date 2022-08-04
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "Graph3.hh"

#include "Utils3.hh"

bool Graph3::loadMap(char file_name[])
{
  FILE* fp;
  fp = fopen(file_name, "r");
  if (fp == NULL) {
    printf("%s 文件打开失败！\n", file_name);
    return false;
  }

  fscanf(fp, "%d %d", &_map_height, &_map_width);
  _map = std::vector<std::vector<int>>(_map_height, std::vector<int>(_map_width));
  for (int row = 0; row < _map_height; ++row) {
    for (int col = 0; col < _map_width; ++col) {
      fscanf(fp, "%d", &_map[row][col]);
    }
  }

  fclose(fp);
  printf("%d * %d map loaded\n", _map_height, _map_width);
  return true;
}

bool Graph3::constructAdjacencyList()
{
  int vertex_num = 0, edge_num = 0;

  if (_map.size() == 0) {
    printf("error, load map first!\n");
    return false;
  }

  extern const std::vector<std::pair<int, int>> kLineNeighbors;
  extern const std::vector<std::pair<int, int>> kdiagNeighbors;

  _adjacency_list.reserve(_map_height * _map_width);
  int neighbor_row, neighbor_col;

  for (int row = 0; row < _map_height; ++row) {
    for (int col = 0; col < _map_width; ++col) {
      _adjacency_list.push_back(std::vector<std::pair<int, double>>());

      if (_map[row][col] == 0) {  // 对于非障碍物点，统计其可达邻接点(非障碍物邻接点)
        ++vertex_num;

        for (std::pair<int, int> neighbor_offset : kLineNeighbors) {  // four-adjacency neighbors
          neighbor_row = row + neighbor_offset.first;
          neighbor_col = col + neighbor_offset.second;
          if (checkLocValid(neighbor_row, neighbor_col, _map_height, _map_width)
              && _map[neighbor_row][neighbor_col] == 0) {
            _adjacency_list[_adjacency_list.size() - 1].push_back(std::pair<int, double>(
                mapLocToArrayIdx(neighbor_row, neighbor_col, _map_width), 1.0));
            ++edge_num;
          }
        }

        for (std::pair<int, int> neighbor_offset : kDiagNeighbors) {  // diag-adjacency neighbors
          neighbor_row = row + neighbor_offset.first;
          neighbor_col = col + neighbor_offset.second;
          if (checkLocValid(neighbor_row, neighbor_col, _map_height, _map_width)
              && _map[neighbor_row][neighbor_col] == 0) {
            _adjacency_list[_adjacency_list.size() - 1].push_back(std::pair<int, double>(
                mapLocToArrayIdx(neighbor_row, neighbor_col, _map_width), kDiagDist));
            ++edge_num;
          }
        }
      }
    }
  }
  if (edge_num % 2 != 0)
    printf("_edgeNum error!\n");
  edge_num /= 2;
  printf("graph constructed, vertex number: %d, edge number: %d\n", vertex_num, edge_num);
  return true;
}

void Graph3::shortestPath(std::pair<int, int> start, std::pair<int, int> end,
                          std::string method) const
{
  std::vector<std::pair<int, int>> path1;
  double astar_dist = aStarPath1(_map, path1, start, end);

  std::vector<int> path2;
  int start2 = mapLocToArrayIdx(start.first, start.second, _map_width);
  int end2 = mapLocToArrayIdx(end.first, end.second, _map_width);
  double dijkstra_dist = dijkstra(_adjacency_list, path2, start2, end2, _map_width);
  printf("shortest path from (%d,%d) to (%d,%d):\n", start.first, start.second, end.first,
         end.second);

  // show dijkstra path.
  for (int i = path2.size() - 1; i > 0; --i)
    printf("%d --> ", path2[i]);
  printf("%d\n", path2[0]);

  // show astar path.
  for (int i = path1.size() - 1; i > 0; --i)
    printf("(%d,%d) --> ", path1[i].first, path1[i].second);
  printf("(%d,%d)\n", path1[0].first, path1[0].second);

  printf("dist = %4.2lf\n", astar_dist);
}