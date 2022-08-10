# C++实训一 Assignment_3
思路：
------

1.读入map信息，存于二维数组中，0表示无障碍物，1表示有障碍物。

2.所有无障碍物点构成Graph数据结构的顶点，创建邻接表。

3.使用A*算法求两点间的最短路径。

A*算法实现思路:
-------
基于dijkstra最短路径算法，在选择加入close set的下一个点时，将仅考虑到起点的距离修改为到起点的距离+到终点的启发式距离。启发式距离选择的是对角线距离。

使用的数据结构:
-------
1.Graph3类：使用邻接表存储邻接信息。
-------
public:

    Graph3();

    ~Graph3() = default;

    bool loadMap(char file_name[]);  //loads map from file.

    bool constructAdjacencyList();  //construct adjacency list given after loading a map.

    void shortestPath(int start_row, int start_col, int end_row, int end_col);  //print shortest path from start to destination.

    void showMap();  //print loaded map.

    void showAdjacencyList();  //print adjacency list.

private:

    std::vector<std::vector<int>> _map;  //二维数组保存地图信息.
    std::vector<std::vector<std::pair<int, double>>> _adjacency_list;  //邻接表，edge用std::pair<int, double>表示.

    int _vertex_num;
    int _edge_num;
    int _map_width;
    int _map_height;


Utils头文件：定义用到的一些辅助函数.
----

    bool checkLocValid(int row, int col, int map_height, int map_width);  //check if a coordinate is valid in given map.

    int mapLocToArrayIdx(int row, int col, int map_width);  //transforms map coordinate to array index.

    std::pair<int, int> arrayIdxToMapLoc(int arrayIdx, int map_width);  //transforms array index to map coordinate.

    double diagDistance(int start_row, int start_col, int end_row, int end_col);  //compute diagnal distance of two locations on map.

    double getEdgeLenFromAdj(std::vector<std::vector<std::pair<int, double>>>& adjacency_list, int start, int end);  //Get the Edge Length From adjacency list.

    void updateDist(std::vector<std::vector<std::pair<int, double>>>& adjacency_list, std::set<int>& unfinded_nodes, std::vector<int>& pre_node, std::vector<double>& dist, int node_idx)  //update distance array.

    int findNextNode(std::vector<double>& dist, std::set<int>& unfinded_nodes)  //finds next node.

    double dijkstraPath(std::vector<std::vector<std::pair<int, double>>>& adjacency_list, std::vector<int>& path, int start, int dest);  //dijkstra shortest path alogrithm.