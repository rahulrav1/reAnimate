#pragma once
#include <vector>
#include <queue>
#include <iostream>
#include <float.h>
class Graph {
    public:
        struct Node {
            int val;
            std::vector<std::pair<int, double>> adjNodes; // Pair<AdjNode (idx in graph vector), Weight>
        };
        Graph(int numVertices, int numEdges, int edgeList[numEdges][2], double edgeWeight[numEdges]);
        double Dijkstra(int src, int dest);
        void DFS(int src, bool track);
        void DFSHelper(int src, bool track);
        void pathDFS(int src, int dest, std::vector<Node> treeAdj, std::vector<int> & curNodes, std::vector<int> & path);
        std::vector<std::vector<double>> constructMST(int src);
        std::vector<std::vector<std::pair<int, double>>> flattenGraph();
        std::vector<int> trackTraversal(int src); // For Testing
        std::vector<int> getDijkPath(int src, int dest);
        std::vector<int> traverseMST(std::vector<std::vector<double>> MST, int src, int dest);
        double supremumDijkstra(int src, int dest);
        std::vector<Node> graph;
        std::vector<double> dist;
        std::vector<int> pred;
        std::vector<bool> vis;
        std::vector<int> trav;  // For Testing
        int vertices;
};
