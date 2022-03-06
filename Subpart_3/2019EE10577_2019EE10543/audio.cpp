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
#include "dnn_weights.h"
using namespace std;

struct pred_t
{
    int label;
    float prob;
};

void libaudioAPI(const char* audiofeatures, pred_t* pred){
    Mat inp = readInput(audiofeatures,1,250);
    Mat w1 = reshape(IP1_WT, 250, 144);
    Mat w2 = reshape(IP2_WT, 144, 144);
    Mat w3 = reshape(IP3_WT, 144, 144);
    Mat w4 = reshape(IP4_WT, 144, 12);
    Mat b1 = reshape(IP1_BIAS, 1, 144);
    Mat b2 = reshape(IP2_BIAS, 1, 144);
    Mat b3 = reshape(IP3_BIAS, 1, 144);
    Mat b4 = reshape(IP4_BIAS, 1, 12);
    vector<Mat> weights = {w1, w2, w3, w4};
    vector<Mat> biases = {b1, b2, b3, b4};
    DNN dnn(weights, biases);
    dnn.feedForward(inp);
    vector<pair<int,float>> topThree = dnn.topThree();
    for (int i = 0; i < topThree.size(); i++)
    {
        pred[i].label = topThree[i].first;
        pred[i].prob = topThree[i].second;
    }
}
