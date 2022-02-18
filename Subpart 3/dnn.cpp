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
        vector<Vec> biases;
        Vec output;        

    public:
        DNN(vector<Mat> weights, vector<Vec> biases)
        {
            this->weights = weights;
            this->biases = biases;
        }

        /* 
        input shape: [1,250]
        architecture: FC1 [250x144] -> RELU -> FC2 [144x144] -> RELU -> 
        FC3 [144X144] -> RELU -> FC4 [144x12] -> softmax
        */
        void feedForward(Vec input)
        {
            for (int i = 0; i < weights.size(); i++)
            {
                // code here
            }
            return;
        }

        vector<string> topThree()
        {
            vector<string> topThree;
            // code here
            return topThree;
        }

};
