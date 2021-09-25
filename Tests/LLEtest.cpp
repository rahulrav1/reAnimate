#include <iostream>
#include <vector>
#include "../LLE/LLE.h"
#include "../cs225/catch/catch.hpp"
#include "../cs225/PNG.h"
#include "../Graph/Graph.h"
#include <dirent.h>
std::vector<cs225::PNG*> smallTestPNGs(){
    std::vector<cs225::PNG*> pngs;
    DIR *dir; struct dirent *diread;
    std::vector<std::string> files;

    std::string userDir = "Data/Dragon_Force";

    if ((dir = opendir(userDir.c_str())) != nullptr) {
        while ((diread = readdir(dir)) != nullptr) {
            files.push_back(diread->d_name);
            std::cout<<diread->d_name<<std::endl;
        }
        closedir (dir);
    }
    int c = 0;
    for(std::string i : files) {
        //weird effect of reading directories, generate files . and .., to be removed
        if(c < 2) {
            c++;
            continue;
        }
        if(c>5)
        break;
        c++;
        cs225::PNG* toAdd = new cs225::PNG();
        std::string path;
        path+="Data/Dragon_Force/";
        path+= i;
        std::cout<<path<<std::endl;
        toAdd->readFromFile(path);
        pngs.push_back(toAdd);
    }
    return pngs;
}
std::vector<cs225::PNG*> testPNGs(){
    std::vector<cs225::PNG*> pngs;
    DIR *dir; struct dirent *diread;
    std::vector<std::string> files;

    std::string userDir = "Data/Dragon_Force";

    if ((dir = opendir(userDir.c_str())) != nullptr) {
        while ((diread = readdir(dir)) != nullptr) {
            files.push_back(diread->d_name);
            std::cout<<diread->d_name<<std::endl;
        }
        closedir (dir);
    }
    int c = 0;
    for(std::string i : files) {
        //weird effect of reading directories, generate files . and .., to be removed
        if(c < 2) {
            c++;
            continue;
        }
        cs225::PNG* toAdd = new cs225::PNG();
        std::string path;
        path+="Data/Dragon_Force/";
        path+= i;
        std::cout<<path<<std::endl;
        toAdd->readFromFile(path);
        pngs.push_back(toAdd);
    }
    return pngs;
}
TEST_CASE("LLE SetNeighbors empty", "[weight=10]") {
    std::vector<cs225::PNG*> PNGVec = testPNGs();
    LLE lle = LLE(7, PNGVec);
    lle.setNeighbors();
    std::vector<std::vector<unsigned>> valVec = lle.getNeighbors();
    std::vector<unsigned> testVec;
    REQUIRE(testVec == valVec[3]);
}
TEST_CASE("LLE SetNeighbors small", "[weight=10]") {
    std::vector<cs225::PNG*> PNGVec = testPNGs();
    LLE lle = LLE(700, PNGVec);
    lle.setNeighbors();
    std::vector<std::vector<unsigned>> valVec = lle.getNeighbors();
    std::vector<unsigned> testVec;
    testVec.push_back(8);
    REQUIRE(testVec == valVec[3]);
}
TEST_CASE("LLE SetNeighbors large", "[weight=10]") {
    std::vector<cs225::PNG*> PNGVec = testPNGs();
    LLE lle = LLE(2300, PNGVec);
    lle.setNeighbors();
    std::vector<std::vector<unsigned>> valVec = lle.getNeighbors();
    std::vector<unsigned> testVec;
    testVec.push_back(1);
    testVec.push_back(8);
    testVec.push_back(12);
    testVec.push_back(14);
    testVec.push_back(18);
    testVec.push_back(19);
    testVec.push_back(24);
    testVec.push_back(25);
    testVec.push_back(28);
    testVec.push_back(29);
    testVec.push_back(32);
    REQUIRE(testVec == valVec[3]);
}
TEST_CASE("LLE SetSolution", "[weight=10]") {
    std::vector<cs225::PNG*> PNGVec = testPNGs();
    LLE lle = LLE(7000, PNGVec);
    lle.setNeighbors();
    Matrix out = lle.computeWeights();
    double uBound1 = 0.0212;
    double lBound1 = 0.0209;
    double lBound2 = 0.0416;
    double uBound2 = 0.0420;
    double zero = 0;
    REQUIRE(out[8][36] == zero);
    REQUIRE(((out[0][0] > lBound1) && (out[0][0] < uBound1)));
    REQUIRE(((out[1][0] > lBound2) && (out[1][0] < uBound2)));
}
TEST_CASE("LLE Adgjacency Graph", "[weight=10]") {
    std::vector<cs225::PNG*> PNGVec = testPNGs();
    LLE lle = LLE(7000, PNGVec);
    lle.setNeighbors();
    Matrix out = lle.computeWeights();
    Graph g = lle.getGraphFromAdjacency(out);
    std::vector<int> travVec = g.trackTraversal(0);
    REQUIRE(travVec.size() == PNGVec.size() - 1);
    g.supremumDijkstra(3,27);
    std::vector<int> DijkVec = g.getDijkPath(0, 17);
    std::vector<int> testVec;
    testVec.push_back(0);
    testVec.push_back(3);
    testVec.push_back(32);
    testVec.push_back(14);
    testVec.push_back(12);
    testVec.push_back(6);
    testVec.push_back(2);
    testVec.push_back(15);
    testVec.push_back(17);
    REQUIRE(DijkVec == testVec);
}