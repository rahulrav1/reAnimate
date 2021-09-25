#include <vector>
#include <iostream>
#include <stdlib.h>
#include "Matrix.h"
Matrix::Matrix(unsigned nx, unsigned ny) {
    x = nx;
    y = ny;
    matrix.resize(x);
    for(unsigned i = 0; i < x; i++) {
        matrix[i].resize(y);
    }
    nul = false;
    isTransposed = false;
}
Matrix::Matrix(std::vector<double> vec, unsigned nx, unsigned ny) {
    x = nx;
    y = ny;
    matrix.resize(x);
    for(unsigned i = 0; i < x; i++) {
        matrix[i].resize(y);
    }
    for(unsigned i = 0; i < x; i++) {
        for(unsigned j = 0; j < y; j++) {
            if(i * y + j < vec.size()) {
                matrix[i][j] = vec[i*y+j];
            }
            else {
                matrix[i][j] = 0;
            }
        }
    }
    nul = false;
    isTransposed = false;
}
Matrix::Matrix(const Matrix& mat) {
    matrix.resize(mat.getX());
    for(unsigned i = 0; i < mat.getX(); i++) {
        matrix[i].resize(mat.getY());
        for(unsigned ii = 0; ii < mat.getY(); ii++) {
            matrix[i][ii] = mat.getXY(i,ii);
        }
    }
    x = mat.getX();
    y = mat.getY();
}
std::vector<double>& Matrix::operator[] (int inp) {
    return matrix[inp];
}
std::vector<double> Matrix::operator() (int inp){
    return matrix[inp];
}
void Matrix::removeColumn(unsigned i) {
    matrix.erase(matrix.begin() + i);
    x--;
}
void Matrix::removeRow(unsigned i) {
    for(unsigned j = 0; j < x; j++) {
        matrix[j].erase(matrix[j].begin() + i);
    }
    y--;
}
void Matrix::insertRow(unsigned i, std::vector<double> inp) {
    for(unsigned j = 0; j < x; j++) {
        matrix[j].insert(matrix[j].begin() + i, inp[j]);
    }
    y++;
}
void Matrix::insertColumn(unsigned i, std::vector<double> inp) {
    matrix.insert(matrix.begin() + i, inp);
    x++;
}
std::vector<double> Matrix::getRow(unsigned i) {
    std::vector<double> out;
    for(unsigned j = 0; j < x; j++) {
        out.push_back(matrix[j][i]);
    }
    return out;
}
std::vector<double> Matrix::getColumn(unsigned i) {
    std::vector<double> out;
    if(i > y)
        return out;
    out = matrix[i];
    return out;
}

void Matrix::transpose() {
    std::vector<std::vector<double>> tran = matrix;
    int z = x;
    x = y;
    y = z;    
    matrix.clear();
    matrix.resize(x);
    for(unsigned i = 0; i < x; i++) {
        matrix[i].resize(y);
    }
    for(unsigned i = 0; i < x; i++) {
        for(unsigned ii = 0; ii < y; ii++) {
            matrix[i][ii] = tran[ii][i];
        }
    }                          
}
std::vector<double> Matrix::RowEch(std::vector<double> inp){
    insertColumn(x, inp);
    for (unsigned k=0; k<y; k++){
        for(unsigned i = x - 1; i >= k && i < x; i--){
            if(matrix[k][k] == 0) {
                unsigned int p = k;
                while(matrix[k][p]==0 && p < y)
                p++;
                unsigned u = 0;
                for(double d: getRow(p)) {
                    matrix[u][k] +=d;
                    u++;
                }
                if(matrix[k][p]==0)
                    break;
            }
            matrix[i][k] /= matrix[k][k];
        }
        for (unsigned i=k+1; i<y; i++) {
           double scale = matrix[k][i]/matrix[k][k];
            for (unsigned j=0; j<x; j++) {
                matrix[j][i] -= matrix[j][k]*scale;
            }
        }
    }
    std::vector<double> out = getColumn(x - 1);
    removeColumn(x - 1);
    return out;
}
std::vector<double> Matrix::substitute(std::vector<double> vec) {
    insertColumn(x, vec);
    for (unsigned k = y-1; k < y; k--){
        for (unsigned i=0; i<k; i++){
            double scale = matrix[k][i];
            for (unsigned j=i+1; j<x; j++) {
                matrix[j][i] -= matrix[j][k]*scale;
            }
        }
    }
    std::vector<double> out = getColumn(x - 1);
    removeColumn(x - 1);
    return out;
 }
 std::vector<double> Matrix::solveForWeights(Matrix inp) {
    std::vector<double> out;
    for(unsigned i = 0; i < inp.getX(); i++) {
        out.push_back(1);
    }
    out = inp.RowEch(out);  
    out = inp.substitute(out);
    return out;
}