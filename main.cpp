#include <iostream>
#include <vector>
#include "Graph/Graph.h"
#include "LLE/LLE.h"
#include "cs225/PNG.h"
#include "cs225/Animation.h"
#include "Matrix/Matrix.h"
#include <dirent.h>

int main() {
    double ballSize;
    std::cout<<"enter a number for the ball size, or type 1 for defualt "<<std::endl;
    std::cin>>ballSize;
    if (ballSize == 1)
    ballSize = 7000;

    std::vector<cs225::PNG*> pngs;
    DIR *dir; struct dirent *diread;
    std::vector<std::string> files;

    std::string userDir = "Data/Dragon_Force";
    std::cout<<"enter directory, or type default for default"<<std::endl;
    std::cin>>userDir;
    if(userDir == "default")
    userDir = "Data/Dragon_Force";

    if ((dir = opendir(userDir.c_str())) != nullptr) {
        while ((diread = readdir(dir)) != nullptr) {
            files.push_back(diread->d_name);
            std::cout<<diread->d_name<<std::endl;
        }
        closedir (dir);
    }
    std::cout<<"read dir names" << std::endl;
    int c = 0;
    std::sort(files.begin(), files.end());
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
    std::cout<<"read dir files" << std::endl;
    
    LLE lle = LLE(ballSize, pngs);
    lle.setNeighbors();
    std::cout<<"set negihbors"<<std::endl;
    Matrix k = lle.computeWeights();
    Graph g = lle.getGraphFromAdjacency(k);

    std::vector<int> travVec = g.trackTraversal(0);
    if(travVec.size() != pngs.size() - 1) {
        std::cout<<"ball set of size "<<ballSize<<" does not form cover over images ("<<travVec.size()<<"||"<<pngs.size() - 1<<") output may fail"<<std::endl;
    }

    int inp1 = 0;
    int inp2 = 0;
    std::cout<<"enter a number between 0 and "<<travVec.size()<<std::endl;
    std::cin>>inp1;
    std::cout<<"enter a number between 0 and "<<travVec.size()<<std::endl;
    std::cin>>inp2;

    g.supremumDijkstra(inp1,inp2);
    std::vector<int> DijkVec = g.getDijkPath(inp1, inp2);
    Animation animation;

    unsigned int wMax = 0;
    unsigned int hMax = 0;
    for(int r : DijkVec) {
        hMax = std::max(hMax, pngs[r]->height());
        wMax = std::max(wMax, pngs[r]->width());
    }
    PNG first = PNG(wMax,hMax);
    for(unsigned i = 0; i<first.width(); i++){
            for(unsigned j = 0; j<first.height(); j++){
                first.getPixel(i,j)=HSLAPixel(0,0,0);
            }
    }
    animation.addFrame(first);

    for(int r : DijkVec) {
        std::cout<<r<<std::endl;
        PNG rpng = *(pngs[r]);
        //animation class doesnt handle transparency well, so a black screen is added
        for(unsigned i = 0; i<rpng.width(); i++){
            for(unsigned j = 0; j<rpng.height(); j++){
                rpng.getPixel(i,j)=HSLAPixel(0,0,0);
            }
        }
        //added twice to reduce epilepsy effect
        animation.addFrame(*(pngs[r]));
        animation.addFrame(*(pngs[r]));
        animation.addFrame(rpng);
    }
    std::vector<std::vector<double>> MST = g.constructMST(0);//(inp1 + 1)%travVec.size());
    std::vector<int> MSTVec = g.traverseMST(MST,inp1,inp2);
    Animation animationMST;
    unsigned int wMaxMST = 0;
    unsigned int hMaxMST = 0;
    for(int r : MSTVec) {
        hMax = std::max(hMaxMST, pngs[r]->height());
        wMax = std::max(wMaxMST, pngs[r]->width());
    }

    PNG firstMST = PNG(wMaxMST,hMaxMST);
    for(unsigned i = 0; i<firstMST.width(); i++){
            for(unsigned j = 0; j<firstMST.height(); j++){
                firstMST.getPixel(i,j)=HSLAPixel(0,0,0);
            }
    }

    animationMST.addFrame(firstMST);

    for(int r : MSTVec) {
        std::cout<<r<<std::endl;
        PNG rpng = *(pngs[r]);
        //animation class doesnt handle transparency well, so a black screen is added
        for(unsigned i = 0; i<rpng.width(); i++){
            for(unsigned j = 0; j<rpng.height(); j++){
                rpng.getPixel(i,j)=HSLAPixel(0,0,0);
            }
        }
        //added twice to reduce epilepsy effect
        animationMST.addFrame(*(pngs[r]));
        animationMST.addFrame(*(pngs[r]));
        animationMST.addFrame(rpng);
    }


    std::cout<<"write to file (default for output.gif): "<<std::endl;
    std::string outStr = "output.gif";
    std::cin>>outStr;
    if(outStr == "default")
    outStr ="output";
    std::string MSToutStr = outStr + "MST.gif";
    outStr += ".gif";
    animation.write(outStr);
    animationMST.write(MSToutStr);
    return 0;
}