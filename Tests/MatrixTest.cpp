#include <iostream>
#include <vector>
#include "../cs225/catch/catch.hpp"
#include "../Matrix/Matrix.h"

using namespace std;

void match1DVect(vector<double> & output, vector<double> & ans){

  REQUIRE(output.size() == ans.size());

  for(size_t i = 0; i < ans.size(); ++i) {
    if(Approx(output[i]).margin(.1) != ans[i]) {
        INFO("At index value: " + std::to_string(i) + " your vector was incorrect.");
        REQUIRE(output[i] == ans[i]);
    }
  }
}

TEST_CASE("Matrix dimension constructor", "[weight=6]") {
    Matrix k (4, 4);
    REQUIRE(k.getXY(0,0) == 0);
}
TEST_CASE("Matrix vector constructor", "[weight=6]") {
    vector<double> vec;
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(5);
    Matrix k (vec, 2, 2);
    REQUIRE(k.getXY(0,0) == 2);
    REQUIRE(k.getXY(0,1) == 3);
}
TEST_CASE("Matrix copy constructor", "[weight=10]") {
    vector<double> vec;
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(5);
    Matrix k (vec, 2, 2);
    Matrix m(k);
    REQUIRE(k.getXY(0,0) == 2);
    REQUIRE(k.getXY(1,1) == 5);
}
TEST_CASE("Matrix getRow() small matrix", "[weight=6]") {
    vector<double> vec;
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(5);
    vec.push_back(12);
    vec.push_back(13);
    vec.push_back(14);
    vec.push_back(15);
    vec.push_back(21);
    Matrix k (vec, 3, 3);
    REQUIRE(k.getRow(1) == vector<double>{3, 12, 15});
}
TEST_CASE("Matrix getRow() large matrix", "[weight=10]") {
    vector<double> vec;
    vec.push_back(1);
    vec.push_back(3);
    vec.push_back(5);
    vec.push_back(9);
    vec.push_back(1);
    vec.push_back(3);
    vec.push_back(1);
    vec.push_back(7);
    vec.push_back(4);
    vec.push_back(3);
    vec.push_back(9);
    vec.push_back(7);
    vec.push_back(5);
    vec.push_back(2);
    vec.push_back(0);
    vec.push_back(9);
    Matrix k (vec, 4, 4);
    REQUIRE(k.getRow(3) == vector<double>{9, 7, 7, 9});
}
TEST_CASE("Matrix insertRow() small matrix", "[weight=6]") {
    vector<double> vec;
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(5);
    vec.push_back(12);
    vec.push_back(13);
    vec.push_back(14);
    vec.push_back(15);
    vec.push_back(21);
    Matrix k (vec, 3, 3);
    k.insertRow(1, vector<double>{7, 8, 9});
    REQUIRE(k.getRow(1) == vector<double>{7, 8, 9});
    REQUIRE(k.getRow(2) == vector<double>{3, 12, 15});
}
TEST_CASE("Matrix insertRow() large matrix", "[weight=10]") {
    vector<double> vec;
    vec.push_back(1);
    vec.push_back(3);
    vec.push_back(5);
    vec.push_back(9);
    vec.push_back(1);
    vec.push_back(3);
    vec.push_back(1);
    vec.push_back(7);
    vec.push_back(4);
    vec.push_back(3);
    vec.push_back(9);
    vec.push_back(7);
    vec.push_back(5);
    vec.push_back(2);
    vec.push_back(0);
    vec.push_back(9);
    Matrix k (vec, 4, 4);
    k.insertRow(2, vector<double>{0, 0, 0, 0});
    REQUIRE(k.getRow(2) == vector<double>{0, 0, 0, 0});
    REQUIRE(k.getRow(0) == vector<double>{1, 1, 4, 5});
}
TEST_CASE("Matrix removeRow() small matrix", "[weight=6]") {
    vector<double> vec;
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(5);
    vec.push_back(12);
    vec.push_back(13);
    vec.push_back(14);
    vec.push_back(15);
    vec.push_back(21);
    Matrix k (vec, 3, 3);
    k.removeRow(1);
    REQUIRE(k.getRow(0) == vector<double>{2, 5, 14});
    REQUIRE(k.getRow(1) == vector<double>{4, 13, 21});
}
TEST_CASE("Matrix removeRow() large matrix", "[weight=10]") {
    vector<double> vec;
    vec.push_back(1);
    vec.push_back(3);
    vec.push_back(5);
    vec.push_back(9);
    vec.push_back(1);
    vec.push_back(3);
    vec.push_back(1);
    vec.push_back(7);
    vec.push_back(4);
    vec.push_back(3);
    vec.push_back(9);
    vec.push_back(7);
    vec.push_back(5);
    vec.push_back(2);
    vec.push_back(0);
    vec.push_back(9);
    Matrix k (vec, 4, 4);
    k.removeRow(2);
    REQUIRE(k.getRow(0) == vector<double>{1, 1, 4, 5});
    REQUIRE(k.getRow(2) == vector<double>{9, 7, 7, 9});
}
TEST_CASE("Matrix getColumn() small matrix", "[weight=6]") {
    vector<double> vec;
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(5);
    vec.push_back(12);
    vec.push_back(13);
    vec.push_back(14);
    vec.push_back(15);
    vec.push_back(21);
    Matrix k (vec, 3, 3);
    REQUIRE(k.getColumn(2) == vector<double>{14, 15, 21});
}
TEST_CASE("Matrix getColumn() large matrix", "[weight=10]") {
    vector<double> vec;
    vec.push_back(1);
    vec.push_back(3);
    vec.push_back(5);
    vec.push_back(9);
    vec.push_back(1);
    vec.push_back(3);
    vec.push_back(1);
    vec.push_back(7);
    vec.push_back(4);
    vec.push_back(3);
    vec.push_back(9);
    vec.push_back(7);
    vec.push_back(5);
    vec.push_back(2);
    vec.push_back(0);
    vec.push_back(9);
    Matrix k (vec, 4, 4);
    REQUIRE(k.getColumn(3) == vector<double>{5, 2, 0, 9});
}
TEST_CASE("Matrix insertColumn() small matrix", "[weight=6]") {
    vector<double> vec;
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(5);
    vec.push_back(12);
    vec.push_back(13);
    vec.push_back(14);
    vec.push_back(15);
    vec.push_back(21);
    Matrix k (vec, 3, 3);
    k.insertColumn(2, vector<double>{-1, -2, -3});
    REQUIRE(k.getColumn(2) == vector<double>{-1, -2, -3});
    REQUIRE(k.getColumn(3) == vector<double>{14, 15, 21});
}
TEST_CASE("Matrix insertColumn() large matrix", "[weight=10]") {
    vector<double> vec;
    vec.push_back(1);
    vec.push_back(3);
    vec.push_back(5);
    vec.push_back(9);
    vec.push_back(1);
    vec.push_back(3);
    vec.push_back(1);
    vec.push_back(7);
    vec.push_back(4);
    vec.push_back(3);
    vec.push_back(9);
    vec.push_back(7);
    vec.push_back(5);
    vec.push_back(2);
    vec.push_back(0);
    vec.push_back(9);
    Matrix k (vec, 4, 4);
    k.insertColumn(2, vector<double>{0, 0, 0, 0});
    REQUIRE(k.getColumn(2) == vector<double>{0, 0, 0, 0});
    REQUIRE(k.getColumn(4) == vector<double>{5, 2, 0, 9});
}
TEST_CASE("Matrix removeColumn() small matrix", "[weight=6]") {
    vector<double> vec;
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(5);
    vec.push_back(12);
    vec.push_back(13);
    vec.push_back(14);
    vec.push_back(15);
    vec.push_back(21);
    Matrix k (vec, 3, 3);
    k.removeColumn(1);
    REQUIRE(k.getColumn(0) == vector<double>{2, 3, 4});
    REQUIRE(k.getColumn(1) == vector<double>{14, 15, 21});
}
TEST_CASE("Matrix removeColumn() large matrix", "[weight=10]") {
    vector<double> vec;
    vec.push_back(1);
    vec.push_back(3);
    vec.push_back(5);
    vec.push_back(9);
    vec.push_back(1);
    vec.push_back(3);
    vec.push_back(1);
    vec.push_back(7);
    vec.push_back(4);
    vec.push_back(3);
    vec.push_back(9);
    vec.push_back(7);
    vec.push_back(5);
    vec.push_back(2);
    vec.push_back(0);
    vec.push_back(9);
    Matrix k (vec, 4, 4);
    k.removeColumn(2);
    REQUIRE(k.getColumn(2) == vector<double>{5, 2, 0, 9});
    REQUIRE(k.getColumn(1) == vector<double>{1, 3, 1, 7});
}
TEST_CASE("Matrix transpose works for small matrix", "[weight=6]") {
    vector<double> vec;
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(5);
    Matrix k (vec, 2, 2);
    k.transpose();
    REQUIRE(k.getRow(0) == vector<double>{2, 3});
    REQUIRE(k.getRow(1) == vector<double>{4, 5});
    REQUIRE(k.getXY(1, 1) == 5);
}
TEST_CASE("Matrix transpose works for large matrix", "[weight=10]") {
    vector<double> vec;
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(5);
    vec.push_back(1);
    vec.push_back(8);
    vec.push_back(9);
    vec.push_back(10);
    vec.push_back(12);
    vec.push_back(13);
    vec.push_back(14);
    vec.push_back(15);
    vec.push_back(21);
    vec.push_back(32);
    vec.push_back(47);
    vec.push_back(52);
    Matrix k (vec, 4, 4);
    k.transpose();
    REQUIRE(k.getRow(1) == vector<double>{1, 8, 9, 10});
    REQUIRE(k.getColumn(2) == vector<double>{4, 9, 14, 47});
    REQUIRE(k.getXY(2, 3) == 47);
}
TEST_CASE("Matrix solveForWeights() for small matrix", "[weight=6]") {
    vector<double> vec;
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(5);
    vec.push_back(1);
    vec.push_back(13);
    vec.push_back(14);
    vec.push_back(15);
    vec.push_back(21);
    Matrix k (vec, 3, 3);
    vector<double> out = k.solveForWeights(k);
    vector<double> ans = {-.283, -.039, .125};
    match1DVect(out, ans);
}
TEST_CASE("Matrix solveForWeights() for large matrix", "[weight=10]") {
    vector<double> vec;
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(5);
    vec.push_back(1);
    vec.push_back(8);
    vec.push_back(9);
    vec.push_back(10);
    vec.push_back(12);
    vec.push_back(13);
    vec.push_back(14);
    vec.push_back(15);
    vec.push_back(21);
    vec.push_back(32);
    vec.push_back(47);
    vec.push_back(52);
    Matrix k (vec, 4, 4);
    k.transpose();
    vector<double> out = k.solveForWeights(k);
    vector<double> ans = {-0.0, .4, -1.8, 1.4};
    match1DVect(out, ans);
}
TEST_CASE("Matrix Row Echelon for small matrix", "[weight=6]") {
    vector<double> vec;
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(5);
    vec.push_back(1);
    vec.push_back(13);
    vec.push_back(14);
    vec.push_back(15);
    vec.push_back(21);
    Matrix k (vec, 3, 3);
    std::vector<double> rrefVec;
    rrefVec.push_back(1);
    rrefVec.push_back(1);
    rrefVec.push_back(1);
    vector<double> out = k.RowEch(rrefVec);
    REQUIRE(k.getXY(0, 0) == 1);
    REQUIRE(k.getXY(2, 2) == 1);
}
TEST_CASE("Matrix Row Echelon for large matrix", "[weight=10]") {
    vector<double> vec;
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(5);
    vec.push_back(1);
    vec.push_back(8);
    vec.push_back(9);
    vec.push_back(10);
    vec.push_back(12);
    vec.push_back(13);
    vec.push_back(14);
    vec.push_back(15);
    vec.push_back(21);
    vec.push_back(32);
    vec.push_back(47);
    vec.push_back(52);
    Matrix k (vec, 4, 4);
    std::vector<double> rrefVec;
    rrefVec.push_back(1);
    rrefVec.push_back(1);
    rrefVec.push_back(1);
    rrefVec.push_back(1);
    vector<double> out = k.RowEch(rrefVec);
    REQUIRE(k.getXY(3, 0) == 10.5);
    REQUIRE(k.getXY(1, 1) == 1);
}
TEST_CASE("Matrix substitute for small matrix", "[weight=6]") {
    vector<double> vec;
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(5);
    vec.push_back(1);
    vec.push_back(13);
    vec.push_back(14);
    vec.push_back(15);
    vec.push_back(21);
    Matrix k (vec, 3, 3);
    std::vector<double> rrefVec;
    rrefVec.push_back(1);
    rrefVec.push_back(1);
    rrefVec.push_back(1);
    vector<double> out = k.substitute(rrefVec);
    vector<double> ans = {-2491, -14, 1};
    match1DVect(out, ans);
}
TEST_CASE("Matrix substitute for large matrix", "[weight=10]") {
    vector<double> vec;
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(5);
    vec.push_back(1);
    vec.push_back(8);
    vec.push_back(9);
    vec.push_back(10);
    vec.push_back(12);
    vec.push_back(13);
    vec.push_back(14);
    vec.push_back(15);
    vec.push_back(21);
    vec.push_back(32);
    vec.push_back(47);
    vec.push_back(52);
    Matrix k (vec, 4, 4);
    std::vector<double> rrefVec;
    rrefVec.push_back(1);
    rrefVec.push_back(1);
    rrefVec.push_back(1);
    rrefVec.push_back(1);
    vector<double> out = k.substitute(rrefVec);
    vector<double> ans = {54155776, -21513, -46, 1};
    match1DVect(out, ans);
}
TEST_CASE("Matrix multiplication for small matrix", "[weight=6]") {
    vector<double> vec;
    vec.push_back(13);
    vec.push_back(14);
    vec.push_back(15);
    vec.push_back(21);
    Matrix k (vec, 2, 2);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(5);
    Matrix l (vec, 2, 2);
    Matrix res = k * l;
    REQUIRE(res.getXY(1, 0) == 510);
    REQUIRE(res.getXY(0, 1) == 476);
    REQUIRE(res.getXY(0, 0) == 379);
}
TEST_CASE("Matrix multiplication for large matrix", "[weight=10]") {
    vector<double> vec;
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(5);
    vec.push_back(1);
    vec.push_back(13);
    vec.push_back(14);
    vec.push_back(15);
    vec.push_back(21);
    Matrix k (vec, 3, 3);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(5);
    vec.push_back(1);
    vec.push_back(13);
    Matrix l (vec, 3, 2);
    Matrix res = k * l;
    REQUIRE(res.getXY(2, 0) == 109);
    REQUIRE(res.getXY(2, 1) == 390);
    REQUIRE(res.getXY(0, 0) == 20);
}

