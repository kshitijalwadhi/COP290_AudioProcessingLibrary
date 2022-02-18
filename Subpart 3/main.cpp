#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include "matrices.h"
#include "activationFns.h"
#include "subsampling.h"
#include "utils.h"
#include "dnn.h"
using namespace std;

// call the library from here after taking the arguments
int main(int argc, char **argv)
{
    Mat inp = randMat(1, 250);
    Mat w1 = randMat(250, 144);
    Mat w2 = randMat(144, 144);
    Mat w3 = randMat(144, 144);
    Mat w4 = randMat(144, 12);
    Vec b1 = randVec(144);
    Vec b2 = randVec(144);
    Vec b3 = randVec(144);
    Vec b4 = randVec(12);
    vector<Mat> weights = {w1, w2, w3, w4};
    vector<Vec> biases = {b1, b2, b3, b4};
    DNN dnn(weights, biases);
    dnn.feedForward(inp);
    vector<string> topThree = dnn.topThree();

    return 0;
}