/**
 * @file Utils3.cc
 * @author Yuezuo Liu (522204435@qq.com)
 * @brief containing some utility functions.
 * @version 0.1
 * @date 2022-08-08
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "Utils3.hh"

#include <algorithm>
#include <queue>
#include <set>
#include <unordered_map>

class MapLoc
{
 public:
  MapLoc(double dist, double heuristic, std::pair<int, int> loc)
      : _loc(loc), _dist(dist), _heuristic_dist(heuristic)
  {
  }

  bool operator<(const MapLoc& other) const
  {
    return (other._dist + other._heuristic_dist < _dist + _heuristic_dist);
  }

  friend double aStarPath1(const std::vector<std::vector<int>> map,
                           std::vector<std::pair<int, int>>& path, std::pair<int, int> start,
                           std::pair<int, int> dest);

 private:
  double _dist;
  double _heuristic_dist;
  std::pair<int, int> _loc;
  // std::pair<int, int> _pre;
};

bool checkLocValid(int row, int col, int map_height, int map_width)
{
  if (row >= 0 && row < map_height && col >= 0 && col < map_width)
    return true;
  else
    return false;
}

int mapLocToArrayIdx(int row, int col, int map_width)
{
  return row * map_width + col;
}

std::pair<int, int> arrayIdxToMapLoc(int arrayIdx, int map_width)
{
  return std::pair<int, int>(arrayIdx / map_width, arrayIdx % map_width);
}

double diagDistance(int start_row, int start_col, int end_row, int end_col)
{
  double dy = std::abs(start_row - end_row);
  double dx = std::abs(start_col - end_col);
  return dx + dy + (kDiagDist - 2) * std::min(dx, dy);
}

double diagDistance(std::pair<int, int> start, std::pair<int, int> end)
{
  double dy = std::abs(start.first - end.first);
  double dx = std::abs(start.second - end.second);
  return dx + dy + (kDiagDist - 2) * std::min(dx, dy);
}

static double getEdgeLenFromAdj(const AdjListType& adjacency_list, int start, int end)
{
  if (start == end)
    return 0;
  for (std::pair<int, double> edge : adjacency_list[start]) {
    if (edge.first == end)
      return edge.second;
  }
  return 10000.0;  // unreachable
}

static void updateDist(const AdjListType& adjacency_list, const std::set<int>& unfinded_nodes,
                       std::vector<int>& pre_node, std::vector<double>& dist, int node_idx)
{
  for (int unfinded_node_idx : unfinded_nodes) {
    double edge_len = getEdgeLenFromAdj(adjacency_list, node_idx, unfinded_node_idx);
    if (dist[node_idx] + edge_len
        < dist[unfinded_node_idx]) {  // start节点经过node_idx中转到达unfinded_node_idx更短
      dist[unfinded_node_idx] = dist[node_idx] + edge_len;
      pre_node[unfinded_node_idx] = node_idx;  // update predecessor
    }
  }
}

static int findNextNode(const std::vector<double>& dist, const std::set<int>& unfinded_nodes,
                        const std::vector<double>& heuristic_dist)
{
  int nearest_node_idx;
  double min_dist = 10000.0;
  for (int unfinded_node_idx : unfinded_nodes) {
    if (dist[unfinded_node_idx] < min_dist) {
      min_dist = dist[unfinded_node_idx];
      nearest_node_idx = unfinded_node_idx;
    }
  }
  return nearest_node_idx;
}

double dijkstra(const AdjListType& adjacency_list, std::vector<int>& path, int start, int dest,
                int map_width)
{
  printf("A* finding shortest path from %d to %d......\n", start, dest);
  if (start == dest) {
    path.push_back(start);
    return 0;
  }

  std::set<int> finded_nodes;
  std::set<int> unfinded_nodes;
  finded_nodes.insert(start);
  for (int vertex_idx = 0; vertex_idx < adjacency_list.size(); ++vertex_idx) {  // init two sets
    if (vertex_idx != start && adjacency_list[vertex_idx].size() > 0)
      unfinded_nodes.insert(vertex_idx);
  }

  // compute heuristic distance
  std::vector<double> heuristic_dist = std::vector<double>(adjacency_list.size());
  for (int vertex_idx : unfinded_nodes) {
    std::pair<int, int> start_map_loc = arrayIdxToMapLoc(start, map_width);
    std::pair<int, int> dest_map_loc = arrayIdxToMapLoc(dest, map_width);
    heuristic_dist[vertex_idx] = diagDistance(start_map_loc.first, start_map_loc.second,
                                              dest_map_loc.first, dest_map_loc.second);
  }

  std::vector<int> pre_node(adjacency_list.size());  // record pre_node index in shortest path
  std::vector<double> dist(adjacency_list.size(), 10000.0);
  for (std::pair<int, double> edge : adjacency_list[start]) {
    dist[edge.first] = edge.second;  // init distance from start_vertex to others
    pre_node[edge.first] = start;    // init pre_nodes array;
  }

  int newly_finded_node;

  while (true) {
    newly_finded_node = findNextNode(dist, unfinded_nodes, heuristic_dist);
    printf("find node %2d, dist = %4.2lf\n", newly_finded_node, dist[newly_finded_node]);
    if (newly_finded_node == dest)
      break;

    finded_nodes.insert(newly_finded_node);
    unfinded_nodes.erase(newly_finded_node);
    updateDist(adjacency_list, unfinded_nodes, pre_node, dist, newly_finded_node);
  }

  path.push_back(dest);
  int node_idx = dest;
  while (true) {
    node_idx = pre_node[node_idx];
    path.push_back(node_idx);
    if (node_idx == start)
      break;
  }
  return dist[dest];
}

static double neighborDist(const std::pair<int, int>& loc1, const std::pair<int, int>& loc2)
{
  if (loc1.first != loc2.first && loc1.second != loc2.second)
    return kDiagDist;
  else
    return 1.0;
}

double aStarPath1(const std::vector<std::vector<int>> map, std::vector<std::pair<int, int>>& path,
                  std::pair<int, int> start, std::pair<int, int> dest)
{
  // 0:unfound, 1:open-set, 2:close-set
  std::vector<std::vector<int>> visit_flag(map.size(), std::vector<int>(map[0].size(), 0));
  std::vector<std::vector<std::pair<int, int>>> pre_node(
      map.size(), std::vector<std::pair<int, int>>(map[0].size()));
  std::priority_queue<MapLoc> open_set;
  // std::set<std::pair<int, int>> close_set;

  open_set.push(MapLoc(0, diagDistance(start.first, start.second, dest.first, dest.second),
                       std::pair<int, int>{start.first, start.second}));

  while (!open_set.empty()) {
    MapLoc location = open_set.top();
    printf("%d, %d\n", location._loc.first, location._loc.second);

    if (location._loc.first == dest.first
        && location._loc.second == dest.second) {  // find destination
      path.push_back(dest);
      std::pair<int, int> current = dest;
      while (current != start) {
        // total_dist += neighborDist(current, pre_node[current.first][current.second]);
        current = pre_node[current.first][current.second];
        path.push_back(current);
      }
      return location._dist;
    }

    open_set.pop();
    // close_set.insert(location._loc);
    visit_flag[location._loc.first][location._loc.second] = 2;  // node is in close set now
    std::pair<int, int> current_loc;
    int current_row, current_col;
    double current_dist;
    for (std::pair<int, int> neighbor_offset : kAllNeighbors) {
      current_loc = std::pair<int, int>{location._loc.first + neighbor_offset.first,
                                        location._loc.second + neighbor_offset.second};
      if (!checkLocValid(current_loc.first, current_loc.second, map.size(), map[0].size())
          || map[current_loc.first][current_loc.second] == 1)
        continue;

      printf("current: %d, %d\n", current_loc.first, current_loc.second);
      printf("size: %d %d\n", visit_flag.size(), visit_flag[0].size());
      if (visit_flag[current_loc.first][current_loc.second] == 0) {  // not in openset and close set
        pre_node[current_loc.first][current_loc.second] = location._loc;
        current_dist = location._dist + neighborDist(location._loc, current_loc);
        open_set.push(MapLoc(current_dist, diagDistance(current_loc, dest), current_loc));
        visit_flag[current_loc.first][current_loc.second] = 1;  // node is in open-set now
      }
    }
  }
}