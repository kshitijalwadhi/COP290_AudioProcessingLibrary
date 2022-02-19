#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include "matrices.h"
#include "activationFns.h"
#include "subsampling.h"
#include "utils.h"
//#include "dnn.h"
#include "dnn.cpp"
using namespace std;

int main(int argc, char **argv)
{
    srand(time(NULL));
    Mat inp = randMat(1, 250);
    Mat w1 = randMat(250, 144);
    Mat w2 = randMat(144, 144);
    Mat w3 = randMat(144, 144);
    Mat w4 = randMat(144, 12);
    Mat b1 = randMat(1, 144);
    Mat b2 = randMat(1, 144);
    Mat b3 = randMat(1, 144);
    Mat b4 = randMat(1, 12);
    vector<Mat> weights = {w1, w2, w3, w4};
    vector<Mat> biases = {b1, b2, b3, b4};
    vector<string> class_labels = {"silence", "unknown", "yes", "no", "up", "down", "left", "right", "on", "off", "stop", "go"};
    DNN dnn(weights, biases, class_labels);
    dnn.feedForward(inp);
    vector<string> topThree = dnn.topThree();
    for (int i = 0; i < topThree.size(); i++)
    {
        cout << topThree[i] << endl;
    }
    return 0;
}