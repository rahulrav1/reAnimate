#include "Graph.h"

Graph::Graph(int numVertices, int numEdges, int edgeList[numEdges][2], double edgeWeight[numEdges]) {
    graph.resize(numVertices); // Graph Class assumes vertices are labeled [0, numVertices-1]
    dist.resize(numVertices);
    pred.resize(numVertices);
    vertices = numVertices;
    for(int i = 0; i < numEdges; i++) {
        graph[edgeList[i][0]].adjNodes.push_back({edgeList[i][1], edgeWeight[i]});
    }
    vis.resize(numVertices);
}
void Graph::DFSHelper(int src, bool track) {
    if(track && !vis[src]) {
        trav.push_back(src);
    }
    vis[src] = true;
    for(std::pair<int, double> v : graph[src].adjNodes) {
        if(!vis[v.first]) {
            DFSHelper(v.first, track);
        }
    }
} 
void Graph::DFS(int src, bool track) {
    std::fill(vis.begin(), vis.end(), false);
    DFSHelper(src, track);
}
double Graph::Dijkstra(int src, int dest) {
    std::fill(dist.begin(), dist.end(), DBL_MAX);
    std::fill(pred.begin(), pred.end(), -1);
    dist[src] = 0;
    std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>, std::greater<std::pair<double, int>>> pq;
    pq.push({0, src});
    while(!pq.empty()) {
        std::pair<double, int> u = pq.top();
        pq.pop();
        for(std::pair<int, double> p : graph[u.second].adjNodes) {
            double weight = p.second;
            if(dist[u.second] + weight < dist[p.first]) {
                dist[p.first] = dist[u.second] + weight;
                pred[p.first] = u.second;
                pq.push({dist[p.first], p.first});
            }
        }
    } 
    return dist[dest];
}
double Graph::supremumDijkstra(int src, int dest) {
    std::fill(dist.begin(), dist.end(), DBL_MAX);
    std::fill(pred.begin(), pred.end(), -1);
    dist[src] = 0;
    std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>, std::greater<std::pair<double, int>>> pq;
    pq.push({0, src});
    while(!pq.empty()) {
        std::pair<double, int> u = pq.top();
        pq.pop();
        for(std::pair<int, double> p : graph[u.second].adjNodes) {
            double weight = p.second;
            if(std::max(dist[u.second],weight) < dist[p.first]) {
                dist[p.first] = std::max(dist[u.second],weight);
                pred[p.first] = u.second;
                pq.push({dist[p.first], p.first});
            }
        }
    } 
    return dist[dest];
}
std::vector<std::vector<double>> Graph::constructMST(int src) {
    std::vector<int> parent(vertices, -1);
    std::vector<double> key(vertices, DBL_MAX);
    std::vector<bool> inMST(vertices, false);
    std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>, std::greater<std::pair<double, int>>> pq;
    key[src] = 0;
    parent[src] = -1;
    pq.push({0, src});
    while(!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        inMST[u] = true;
        for(std::pair<int, double> p : graph[u].adjNodes) {
            int v = p.first;
            double weight = p.second;
            if(!inMST[v] && key[v] > weight) {
                key[v] = weight;
                pq.push({key[v], v});
                parent[v] = u;
            }
        }
    }
    std::vector<std::vector<double>> MST(vertices - 1);
    int idx = 0;
    for(int i = 0; i < vertices; i++) {
        if(parent[i] == -1) {
            continue;
        }
        double weight = 0;
        for(std::pair<int, double> p : graph[parent[i]].adjNodes) {
            if(p.first == i) {
                weight = p.second;
                break;
            }
        }
        MST[idx].push_back(parent[i]);
        MST[idx].push_back(i);
        MST[idx].push_back(weight);
        idx++;
    }
    return MST;
}
void Graph::pathDFS(int src, int dest, std::vector<Node> treeAdj, std::vector<int> & curNodes, std::vector<int> & path) {
    curNodes.push_back(src);
    if(src == dest) {
        for(int i = 0; i < (int)curNodes.size(); i++) {
            path.push_back(curNodes[i]);
        }
        return;
    }
    vis[src] = true;
    for(std::pair<int, double> v : treeAdj[src].adjNodes) {
        if(!vis[v.first]) {
            pathDFS(v.first, dest, treeAdj, curNodes, path);
        }
    }
    curNodes.pop_back();
}
std::vector<int> Graph::traverseMST(std::vector<std::vector<double>> MST, int src, int dest) {
    std::vector<Node> mstTree(vertices);
    for(int i = 0; i < (int)MST.size(); i++) {
        if (MST[i].empty())
        continue;
        mstTree[(int)MST[i][0]].adjNodes.push_back({(int)MST[i][1], -1});
        mstTree[(int)MST[i][1]].adjNodes.push_back({(int)MST[i][0], -1});
    }
    std::fill(vis.begin(), vis.end(), false);
    std::vector<int> p;
    std::vector<int> cNodes;
    pathDFS(src, dest, mstTree, cNodes, p);
    return p;
}
std::vector<std::vector<std::pair<int, double>>> Graph::flattenGraph() {
    std::vector<std::vector<std::pair<int, double>>> v(graph.size());
    for(int i = 0; i < (int)graph.size(); i++) {
        for(std::pair<int, double> p : graph[i].adjNodes) {
            v[i].push_back(p);
        }
    }
    return v;
}
std::vector<int> Graph::trackTraversal(int src) {
    trav.clear();
    DFS(src, true);
    return trav;
}
std::vector<int> Graph::getDijkPath(int src, int dest) {
        std::vector<int> path;
        int cur = dest;
        while(pred[cur] != src) {
            path.push_back(cur);
            cur = pred[cur];
        }
        path.push_back(src);
        std::reverse(path.begin(), path.end());
        return path;
}
