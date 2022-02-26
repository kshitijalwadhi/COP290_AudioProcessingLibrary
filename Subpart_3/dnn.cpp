#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include "matrices.h"
#include "activationFns.h"
#include "subsampling.h"
#include "utils.h"
using namespace std;

class DNN
{
    private:
        vector<Mat> weights;
        vector<Mat> biases;
        Vec output;
        vector<string> class_labels;

    public:
        DNN(vector<Mat> weights, vector<Mat> biases)
        {
            this->weights = weights;
            this->biases = biases;
        }

        /* 
        input shape: [1,250]
        architecture: FC1 [250x144] -> RELU -> FC2 [144x144] -> RELU -> 
        FC3 [144X144] -> RELU -> FC4 [144x12] -> softmax
        */
        void feedForward(Mat input)
        {
            for (int i = 0; i < weights.size()-1; i++)
            {
                input = FC_Layer(input, weights[i], biases[i],0);
                input = relu(input);
            }
            input = FC_Layer(input, weights[weights.size()-1], biases[weights.size()-1],0);
            this->output = softmax(flatten(input));
            return;
        }

        vector<pair<int,float>> topThree()
        {
            vector<pair<int,float>> topThree;
            for (int i = 0; i < 3; i++)
            {
                int max_index = 0;
                for (int j = 0; j < output.size(); j++)
                {
                    if (output[j] > output[max_index])
                    {
                        max_index = j;
                    }
                }
                topThree.push_back({max_index, output[max_index]});
                output[max_index] = -1;
            }
            return topThree;
        }

};
