/**
 * @file Utils3.hh
 * @author Yuezuo Liu (522204435@qq.com)
 * @brief containing some utility functions.
 * @version 0.1
 * @date 2022-08-04
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef CPP_PROGRAM_ASSIGNMENT3_INCLUDE_UTILS3_HH_
#define CPP_PROGRAM_ASSIGNMENT3_INCLUDE_UTILS3_HH_

#include <cmath>
#include <set>
#include <vector>

using AdjListType = std::vector<std::vector<std::pair<int, double>>>;

const std::vector<std::pair<int, int>> kLineNeighbors = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
const std::vector<std::pair<int, int>> kDiagNeighbors = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
const std::vector<std::pair<int, int>> kAllNeighbors
    = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
const double kDiagDist = 1.414;

/**
 * @brief check if a coordinate is valid in given map.
 *
 * @param row row coordinate.
 * @param col column coordinate.
 * @param map_height map's height.
 * @param map_width map's width.
 * @return true if coordinate is valid.
 * @return false if coordinate is invalid.
 */
bool checkLocValid(int row, int col, int map_height, int map_width);

/**
 * @brief transforms map coordinate to array index.
 *
 * @param row row coordinate.
 * @param col column coordinate.
 * @param map_width map's width.
 * @return int array index in adjacency list.
 */
int mapLocToArrayIdx(int row, int col, int map_width);

/**
 * @brief transforms array index to map coordinate.
 *
 * @param arrayIdx array index in adjacency list
 * @param map_width map's coordinate
 * @return std::pair<int, int> a std::pair containing (row coordinate, column
 * coordinate).
 */
std::pair<int, int> arrayIdxToMapLoc(int arrayIdx, int map_width);

/**
 * @brief compute diagnal distance of two locations on map.
 *
 * @param start_row row coordinate of start.
 * @param start_col column coordinate of start.
 * @param end_row row coordinate of end.
 * @param end_col column coordinate of end.
 * @return double diagnal distance.
 */
static double diagDistance(int start_row, int start_col, int end_row, int end_col);

/**
 * @brief Get the Edge Length From adjacency list.
 *
 * @param adjacency_list adjacency list.
 * @param start start index.
 * @param end end index.
 * @return double edge length from start to end.
 */
static double getEdgeLenFromAdj(const AdjListType& adjacency_list, int start, int end);

/**
 * @brief update distance array.
 *
 * @param adjacency_list adjacency list
 * @param unfinded_nodes nodes whose distance don't have.
 * @param pre_node contraing the precursor in shortest path at present.
 * @param dist distance from start vertex to all nodes.
 * @param node_idx newly got node index.
 */
static void updateDist(const AdjListType& adjacency_list, const std::set<int>& unfinded_nodes,
                       std::vector<int>& pre_node, std::vector<double>& dist, int node_idx);

/**
 * @brief finds next node.
 *
 * @param dist distance array.
 * @param unfinded_nodes nodes whose distance don't have.
 * @return int found node index.
 */
static int findNextNode(const std::vector<double>& dist, const std::set<int>& unfinded_nodes,
                        const std::vector<double>& heuristic_dist, int proportion);

/**
 * @brief A* alogrithm based on dijkstra algorithm and graph theory (adjacency list)
 *
 * @param adjacency_list adjacency list.
 * @param path path containg shortest path.
 * @param start start vertex.
 * @param dest destination vertex.
 * @return double shortest path length.
 */
double dijkstra(const AdjListType& adjacency_list, std::vector<int>& path, int start, int dest,
                int map_width);

double aStarPath1(const std::vector<std::vector<int>> map, std::vector<std::pair<int, int>>& path,
                  std::pair<int, int> start, std::pair<int, int> dest);

#endif