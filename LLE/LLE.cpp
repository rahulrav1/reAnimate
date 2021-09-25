#include <vector>
#include "LLE.h"
#include <algorithm>
#include <math.h>
LLE::LLE(double ballSize, std::vector<cs225::PNG*> inps) {
    maxWidth = 100;
    maxHeight = 100;
    inputs = inps;
    NHoodSize = ballSize;
    for(cs225::PNG* k : inputs) {
        maxWidth = std::max(k->width(), maxWidth);
        maxHeight = std::max(k->height(), maxHeight);
        }
    
}

void LLE::setNeighbors() {
    for(unsigned i = 0; i < inputs.size(); i++){
        std::vector<unsigned> vals;
        for(unsigned ii = 0; ii < inputs.size(); ii++) {
            if(i == ii) {
                continue;
            }
            if(inputs[ii]->dist(inputs[i]) <= NHoodSize) {
                vals.push_back(ii);
            }
        }
        neighbors.push_back(vals);
    }
}
Matrix LLE::computeWeights(){
    Matrix out = Matrix(inputs.size(), inputs.size());
    for(unsigned i = 0; i < inputs.size(); i++){
        
        Matrix Z = Matrix(neighbors[i].size(),maxWidth*maxHeight);
        if(Z.getX() == 0 || Z.getY() == 0)
            continue;

        for(unsigned int j = 0; j < neighbors[i].size(); j++) {
            for(unsigned int jj = 0; jj < maxHeight*maxWidth; jj++) {
                 if(jj > (inputs[j]->height() - 1)*(inputs[j]->width() - 1)) {
                    if(jj > (inputs[i]->height() - 1)*(inputs[i]->width() - 1)){
                    Z[j][jj] = 0;
                    } else{
                    Z[j][jj] = inputs[i]->getPixel(jj%(inputs[i]->width()),jj/(inputs[i]->width())).val();
                    }
                    continue;
                } else if(jj > (inputs[i]->height() - 1)*(inputs[i]->width() - 1)) {
                    Z[j][jj]= -1*(inputs[j]->getPixel(jj%(inputs[j]->width()),jj/(inputs[j]->width())).val());
                    continue;
                }
                Z[j][jj] = inputs[j]->getPixel(jj%(inputs[j]->width()),jj/(inputs[j]->width())).dist(inputs[i]->getPixel(jj%(inputs[i]->width()),jj/(inputs[i]->width())));
            }
        }
        //std::cout<<"gorg"<<std::endl;
        Matrix toTP = Z;
        //i do not understand why but if these print staments are removed the code seg faults
        //i guess it also serves as a good way of making sure the code is actually progressing
        std::cout<<Z.getX()<<" "<<Z.getY()<<std::endl;
        toTP.transpose();
        Matrix C = Z*toTP;
        std::cout<<toTP.getX()<<" "<<toTP.getY()<<std::endl;
        std::vector<double>weightVec = C.solveForWeights(C);
        for(unsigned b = 0; b <weightVec.size();b++)
            weightVec[b] = fabs(weightVec[b]);
        weightVec[i] = 0.005;
        double sum = 0;
        for(unsigned j = 0; j < weightVec.size(); j++) {
            sum += weightVec[j];
        }

        int weightVecNext = 0;
        for(unsigned j=0; j < inputs.size(); j++) {
            if(std::find(neighbors[i].begin(), neighbors[i].end(), j) != neighbors[i].end()) {
            out[i][weightVecNext] = fabs(weightVec[weightVecNext]/sum);
            weightVecNext++;
            }
            else {
            out[i][j] = 0;
            }
        }
    }
    return out;
}
Graph LLE::getGraphFromAdjacency(Matrix inp) {
    std::vector<double> weightVec;
    std::vector<std::pair<int,int>>edgeVec;
    for(unsigned i = 0; i < inp.getX(); i++) {
        for(unsigned ii = 0; ii < inp.getY(); ii++) {
            weightVec.push_back(inp[i][ii]);
            edgeVec.push_back(std::pair<int,int>(i,ii));
        }
    }

    while(std::find(weightVec.begin(), weightVec.end(), 0) != weightVec.end()) {
        int p = std::find(weightVec.begin(), weightVec.end(), 0) - weightVec.begin();
        weightVec.erase(weightVec.begin()+p);
        edgeVec.erase(edgeVec.begin()+p);
    }

    int numEdges = weightVec.size();
    int edgeList[numEdges][2];
    double weights[numEdges];
    for(int i = 0; i < numEdges; i++) {
        weights[i] = weightVec[i];
        edgeList[i][0] = edgeVec[i].first;
        edgeList[i][1] = edgeVec[i].second;
    } 

    Graph(inp.getX(),numEdges, edgeList, weights);
   return Graph(inp.getX(),numEdges, edgeList, weights);
}