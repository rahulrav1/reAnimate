#include "../cs225/catch/catch.hpp"

#include "../Graph/Graph.h"

#include <vector>
#include <algorithm>
#include <set>
#include <float.h>

using namespace std;


void match1DVect(vector<int> & output, vector<int> & ans){

  REQUIRE(output.size() == ans.size());

  for(size_t i = 0; i < ans.size(); ++i) {
    if(output[i] != ans[i]) {
        INFO("At index value: " + std::to_string(i) + " your vector was incorrect.");
        REQUIRE(output[i] == ans[i]);
    }
  }
}
void matchVectSet(vector<vector<double>> & output, set<vector<double>> & ans){

  REQUIRE(output.size() == ans.size());

  for(size_t i = 0; i < ans.size(); ++i) {
    if(ans.find(output[i]) == ans.end()) {
        INFO("At index value: " + std::to_string(i) + " your vector was incorrect.");
        REQUIRE(ans.find(output[i]) != ans.end());
    }
  }
}

void match2DVectPairs(vector<vector<pair<int, double>>> & output, vector<vector<pair<int, double>>> & ans){

  REQUIRE(output.size() == ans.size());

  for(size_t i = 0; i < ans.size(); ++i) {
    for(size_t j = 0; j < ans[i].size(); j++) {
        if(output[i][j] != ans[i][j]) {
            INFO("At index value: " + std::to_string(i) + " your vector was incorrect.");
            REQUIRE(output[i][j] == ans[i][j]);
        }
    }
  }
}


TEST_CASE("Graph::Constructor small graph", "[weight=6]")
{
    int edges[4][2];
    vector<vector<int>> v = {{0, 1, 2}, {1, 2, 3}, {3, 2, 4}, {3, 0, 7}};
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 2; j++) {
            edges[i][j] = v[i][j];
        }
    }
    double edgeWeights[4];
    for(int i = 0; i < 4; i++) {
        edgeWeights[i] = v[i][2];
    }
    Graph g(4, 4, edges, edgeWeights);
    vector<vector<pair<int, double>>> ans = {{{1, 2}}, {{2, 3}}, {}, {{2, 4}, {0, 7}}};
    vector<vector<pair<int, double>>> out = g.flattenGraph();
    match2DVectPairs(out, ans);
}
TEST_CASE("Graph::Constructor large graph", "[weight=10]")
{
    int edges[12][2];
    vector<vector<int>> v = {{0, 1, 2}, {1, 2, 3}, {3, 2, 4}, {3, 0, 7}, 
                            {5, 7, 3}, {7, 5, 4}, {9, 0, 3}, {2, 5, 4},
                            {6, 5, 2}, {4, 5, 12}, {4, 7, 10}, {9, 1, 3}};
    for(int i = 0; i < 12; i++) {
        for(int j = 0; j < 2; j++) {
            edges[i][j] = v[i][j];
        }
    }
    double edgeWeights[12];
    for(int i = 0; i < 12; i++) {
        edgeWeights[i] = v[i][2];
    }
    Graph g(10, 12, edges, edgeWeights);
    vector<vector<pair<int, double>>> ans = {{{1, 2}}, {{2, 3}}, {{5, 4}}, {{2, 4}, {0, 7}}, {{5, 12}, {7, 10}}, {{7, 3}}, {{5, 2}}, {{5, 4}}, {}, {{0, 3}, {1, 3}}};
    vector<vector<pair<int, double>>> out = g.flattenGraph();
    match2DVectPairs(out, ans);
}
TEST_CASE("Graph::DFS small graph", "[weight=6]")
{
    int edges[4][2];
    vector<vector<int>> v = {{0, 1, 2}, {1, 2, 3}, {2, 3, 4}, {2, 0, 7}};
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 2; j++) {
            edges[i][j] = v[i][j];
        }
    }
    double edgeWeights[4];
    for(int i = 0; i < 4; i++) {
        edgeWeights[i] = v[i][2];
    }
    Graph g(4, 4, edges, edgeWeights);
    vector<int> ans = {0, 1, 2, 3};
    vector<int> out = g.trackTraversal(0);
    match1DVect(out, ans);
}
TEST_CASE("Graph::DFS large graph", "[weight=10]")
{
    int edges[12][2];
    vector<vector<int>> v = {{0, 1, 2}, {1, 2, 3}, {3, 2, 4}, {3, 0, 7}, 
                            {5, 7, 3}, {7, 5, 4}, {9, 0, 3}, {2, 5, 4},
                            {6, 5, 2}, {4, 5, 12}, {4, 7, 10}, {9, 1, 3}};
    for(int i = 0; i < 12; i++) {
        for(int j = 0; j < 2; j++) {
            edges[i][j] = v[i][j];
        }
    }
    double edgeWeights[12];
    for(int i = 0; i < 12; i++) {
        edgeWeights[i] = v[i][2];
    }
    Graph g(10, 12, edges, edgeWeights);
    vector<int> ans = {9, 0, 1, 2, 5, 7};
    vector<int> out = g.trackTraversal(9);
    match1DVect(out, ans);
}
TEST_CASE("Graph::Dijkstra small graph", "[weight=6]")
{
    int edges[7][2];
    vector<vector<int>> v = {{0, 1, 2}, {1, 2, 3}, {3, 2, 4}, {3, 0, 7}, {2, 3, 12}, {2, 4, 1}, {4, 3, 1}};
    for(int i = 0; i < 7; i++) {
        for(int j = 0; j < 2; j++) {
            edges[i][j] = v[i][j];
        }
    }
    double edgeWeights[7];
    for(int i = 0; i < 7; i++) {
        edgeWeights[i] = v[i][2];
    }
    Graph g(5, 7, edges, edgeWeights);
    double ans = 7;
    double out = g.Dijkstra(0, 3);
    REQUIRE(ans == out);
}
TEST_CASE("Graph::Dijkstra large graph multiple paths 1", "[weight=10]")
{
    int edges[12][2];
    vector<vector<int>> v = {{0, 1, 2}, {1, 2, 3}, {3, 2, 4}, {3, 0, 7}, 
                            {5, 7, 3}, {7, 5, 3}, {9, 0, 3}, {2, 5, 4},
                            {6, 5, 2}, {4, 5, 12}, {4, 7, 10}, {9, 1, 3}};
    for(int i = 0; i < 12; i++) {
        for(int j = 0; j < 2; j++) {
            edges[i][j] = v[i][j];
        }
    }
    double edgeWeights[12];
    for(int i = 0; i < 12; i++) {
        edgeWeights[i] = v[i][2];
    }
    Graph g(10, 12, edges, edgeWeights);
    double ans = 6;
    double out = g.Dijkstra(9, 2);
    REQUIRE(ans == out);
}
TEST_CASE("Graph::Dijkstra large graph multiple paths 2", "[weight=10]")
{
    int edges[17][2];
    vector<vector<int>> v = {{0, 1, 2}, {1, 2, 3}, {3, 2, 4}, {3, 0, 7}, 
                            {5, 7, 3}, {7, 5, 3}, {9, 0, 3}, {2, 5, 4},
                            {6, 5, 2}, {4, 5, 12}, {4, 7, 10}, {9, 1, 3}, {0, 6, 2}, {6, 4, 15}, {0, 5, 1}, {5, 4, 12}, {7, 4, 1}};
    for(int i = 0; i < 17; i++) {
        for(int j = 0; j < 2; j++) {
            edges[i][j] = v[i][j];
        }
    }
    double edgeWeights[17];
    for(int i = 0; i < 17; i++) {
        edgeWeights[i] = v[i][2];
    }
    Graph g(10, 17, edges, edgeWeights);
    double ans = 5;
    double out = g.Dijkstra(0, 4);
    REQUIRE(ans == out);
}
TEST_CASE("Graph::Dijkstra no path", "[weight=6]")
{
    int edges[3][2];
    vector<vector<int>> v = {{0, 1, 2}, {1, 2, 3}, {3, 1, 1}};
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 2; j++) {
            edges[i][j] = v[i][j];
        }
    }
    double edgeWeights[3];
    for(int i = 0; i < 3; i++) {
        edgeWeights[i] = v[i][2];
    }
    Graph g(4, 3, edges, edgeWeights);
    double ans = DBL_MAX;
    double out = g.Dijkstra(3, 0);
    REQUIRE(ans == out);
}
TEST_CASE("Graph::constructMST() small graph", "[weight=6]")
{
    int edges[10][2];
    vector<vector<int>> v = {{0, 1, 2}, {0, 2, 4}, {1, 3, 2}, {1, 2, 3}, {2, 3, 5}, {1, 0, 2}, {2, 0, 4}, {3, 1, 2}, {2, 1, 3}, {3, 2, 5}};
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 2; j++) {
            edges[i][j] = v[i][j];
        }
    }
    double edgeWeights[10];
    for(int i = 0; i < 10; i++) {
        edgeWeights[i] = v[i][2];
    }
    Graph g(4, 10, edges, edgeWeights);
    set<vector<double>> ans = {{0, 1, 2}, {1, 2, 3}, {1, 3, 2}}; // Have to use set since ordering in this is based on increasing idx
    vector<vector<double>> out = g.constructMST(0);
    matchVectSet(out, ans);
}
TEST_CASE("Graph::constructMST() large graph", "[weight=10]")
{
    int edges[28][2];
    vector<vector<int>> v = {{0, 1, 4}, {1, 0, 4}, {1, 2, 8}, {2, 1, 8}, 
                            {2, 3, 7}, {3, 2, 7}, {3, 4, 9}, {4, 3, 9}, 
                            {4, 5, 10}, {5, 4, 10}, {5, 6, 2}, {6, 5, 2},
                            {6, 7, 1}, {7, 6, 1}, {0, 7, 8}, {7, 0, 8},
                            {1, 7, 11}, {7, 1, 11}, {2, 8, 2}, {8, 2, 2},
                            {2, 5, 4}, {5, 2, 4}, {3, 5, 14}, {5, 3, 14},
                            {8, 7, 7}, {7, 8, 7}, {8, 6, 6}, {6, 8, 6}};
    for(int i = 0; i < 28; i++) {
        for(int j = 0; j < 2; j++) {
            edges[i][j] = v[i][j];
        }
    }
    double edgeWeights[28];
    for(int i = 0; i < 28; i++) {
        edgeWeights[i] = v[i][2];
    }
    Graph g(9, 28, edges, edgeWeights);
    set<vector<double>> ans = {{0, 1, 4}, {1, 2, 8}, {2, 3, 7}, {3, 4, 9}, {2, 8, 2}, {2, 5, 4}, {5, 6, 2}, {6, 7, 1}}; // Have to use set since ordering in this is based on increasing idx
    vector<vector<double>> out = g.constructMST(0);
    matchVectSet(out, ans);
}
TEST_CASE("Graph::traverseMST() small graph", "[weight=6]")
{
    int edges[10][2];
    vector<vector<int>> v = {{0, 1, 2}, {0, 2, 4}, {1, 3, 2}, {1, 2, 3}, {2, 3, 5}, {1, 0, 2}, {2, 0, 4}, {3, 1, 2}, {2, 1, 3}, {3, 2, 5}};
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 2; j++) {
            edges[i][j] = v[i][j];
        }
    }
    double edgeWeights[10];
    for(int i = 0; i < 10; i++) {
        edgeWeights[i] = v[i][2];
    }
    Graph g(4, 10, edges, edgeWeights);
    vector<vector<double>> out = g.constructMST(0);
    std::vector<int> path = g.traverseMST(out, 0, 3);
    std::vector<int> ans = {0, 1, 3};
    match1DVect(path, ans);
}
TEST_CASE("Graph::traverseMST() large graph", "[weight=10]")
{
    int edges[28][2];
    vector<vector<int>> v = {{0, 1, 4}, {1, 0, 4}, {1, 2, 8}, {2, 1, 8}, 
                            {2, 3, 7}, {3, 2, 7}, {3, 4, 9}, {4, 3, 9}, 
                            {4, 5, 10}, {5, 4, 10}, {5, 6, 2}, {6, 5, 2},
                            {6, 7, 1}, {7, 6, 1}, {0, 7, 8}, {7, 0, 8},
                            {1, 7, 11}, {7, 1, 11}, {2, 8, 2}, {8, 2, 2},
                            {2, 5, 4}, {5, 2, 4}, {3, 5, 14}, {5, 3, 14},
                            {8, 7, 7}, {7, 8, 7}, {8, 6, 6}, {6, 8, 6}};
    for(int i = 0; i < 28; i++) {
        for(int j = 0; j < 2; j++) {
            edges[i][j] = v[i][j];
        }
    }
    double edgeWeights[28];
    for(int i = 0; i < 28; i++) {
        edgeWeights[i] = v[i][2];
    }
    Graph g(9, 28, edges, edgeWeights);
    vector<vector<double>> out = g.constructMST(0);
    std::vector<int> path = g.traverseMST(out, 2, 7);
    std::vector<int> ans = {2, 5, 6, 7};
    match1DVect(path, ans);
}