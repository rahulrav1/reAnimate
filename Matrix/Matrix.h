#pragma once
#include <vector>
#include <iostream>
class Matrix {
    public:
        Matrix(unsigned x, unsigned y);
        Matrix(std::vector<double> vec, unsigned x, unsigned y);
        Matrix(const Matrix& mat);
        void setValue(double val, unsigned x, unsigned y);
        void removeRow(unsigned i);
        void removeColumn(unsigned i);
        void insertColumn(unsigned i, std::vector<double> inp);
        void insertRow(unsigned i, std::vector<double> inp);
        void transpose();
        std::vector<double> RowEch(std::vector<double> inp);
        std::vector<double> substitute(std::vector<double>vec);
        std::vector<double> getRow(unsigned i);
        std::vector<double> getColumn(unsigned i);
        void setXY(unsigned x, unsigned y, double val) {
            matrix[x][y] = val;
        }
        double getXY(unsigned x, unsigned y) const{
            return matrix[x][y];
        }
        std::vector<double>& operator[] (int inp);
        std::vector<double> operator() (int inp);
        Matrix operator* (Matrix& inp) {
            if(nul || inp.nul || y != inp.getX()) {
                Matrix k(0,0);
                k.setNull();
                return k;
            }
            Matrix mat(x, inp.getY());
            // (A, B) * (B, C)
            for(unsigned i = 0; i < x; i++) {
                for(unsigned j = 0; j < inp.getY(); j++) {
                    for(unsigned k = 0; k < y; k++) {
                        mat.setXY(i, j, mat.getXY(i, j) + (this -> getXY(i, k) * inp.getXY(k, j)));
                    }
                }
            }
            return mat;
        }
        Matrix operator+ (Matrix& inp){
            if(nul || inp.nul || x!=inp.getX() || y!=inp.getY()) {
                Matrix k(0, 0);
                k.setNull();
                return k;
            }
            Matrix mat(x, y);
            for(unsigned i = 0; i < x; i++) {
                for(unsigned j = 0; j < y; j++) {
                    mat.setXY(i, j, this -> getXY(i, j) + inp.getXY(i, j));
                }
            }
            return mat;

        }
        std::vector<double> solveForWeights(Matrix inp);
        void setNull() {
            nul = true;
        }
        bool isNull() {
            return nul;
        }
        unsigned getX() const{
            return x;
        }
        unsigned getY() const{
            return y;
        }
        unsigned size() const{
            return matrix.size();
        }
    private:
        std::vector<std::vector<double> > matrix;
        unsigned x;
        unsigned y;
        bool nul;
        bool isTransposed;
};
/*class MatrixVector : Matrix {
    MatrixVector(unsigned y): Matrix(1, y) {
    
    }
    MatrixVector(std::vector<double> inp, unsigned x) : Matrix(inp, x, 1) {
        
    }
    unsigned getSize() {
        return std::max(this->getY(), this->getX());
    }
    double norm() {
        double out = 0;
        unsigned cx, cy;
        if(this -> getX() > this -> getY()) {
            cy = 0;
            for(int i = 0; i < this -> getX(); i++) {
                out += this -> getXY(i, cy);
            }
        }
        else {
            cx = 0;
            for(int i = 0; i < this -> getY(); i++) {
                out += this -> getXY(cx, i);
            }
        }
        return out / getSize();
    }
};*/