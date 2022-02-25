#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include "matrices.h"
#include "activationFns.h"
#include "subsampling.h"
#include "utils.h"
#include "dnn.cpp"
#include "dnn_weights.h"
using namespace std;

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        cout << "Invalid arguments" << endl;
        cout << "Usage: ./yourcode.out <audiosample_file> <output_file>" << endl;
        return 0;
    }
    string audio_file = argv[1];
    string output_file = argv[2];
    bool flag = is_file_exist(audio_file);
    if (flag == false)
    {
        cout << "Audio file doesn't exist" << endl;
        cout << "Check the file path" << endl;
        return 0;
    }
    Mat inp = readInput(audio_file,1,250);
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
    vector<string> class_labels = {"silence", "unknown", "yes", "no", "up", "down", "left", "right", "on", "off", "stop", "go"};
    DNN dnn(weights, biases, class_labels);
    dnn.feedForward(inp);
    vector<pair<string,float>> topThree = dnn.topThree();
    ofstream outfile;
    bool flag1 = is_file_exist(output_file);
    if (flag1 == true)
        outfile.open(output_file, ios::app);
    else
        outfile.open(output_file);
    outfile << audio_file << " ";
    for (int i = 0; i < topThree.size(); i++)
    {
        outfile << topThree[i].first << " ";
    }
    for (int i = 0; i < topThree.size(); i++)
    {
        outfile << topThree[i].second << " ";
    }
    outfile << endl;
    outfile.close();
    return 0;
}