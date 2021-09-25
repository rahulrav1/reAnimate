#pragma once
#include <vector>
#include "../cs225/PNG.h"
#include "../cs225/HSLAPixel.h"
#include "../Matrix/Matrix.h"
#include "../Graph/Graph.h"
class LLE {
    public:
        LLE(double ballSize, std::vector<cs225::PNG*> inps);


        Matrix computeWeights();

        void setNeighbors();

       Graph getGraphFromAdjacency(Matrix inp);
       unsigned getmaxWidth() {return maxWidth;}
       unsigned getmaxHeight() {return maxHeight;}
       std::vector<std::vector<unsigned>> getNeighbors(){return neighbors;} //for testing
    private:
        double NHoodSize;
        unsigned maxWidth;
        unsigned maxHeight;
        std::vector<cs225::PNG*> inputs;
        std::vector<std::vector<unsigned>> neighbors;
};
