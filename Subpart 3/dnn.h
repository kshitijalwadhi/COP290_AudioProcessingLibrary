#ifndef DNN_H
#define DNN_H
#include <vector>

using namespace std;

class DNN
{
    private:
        vector<vector<vector<float> >> weights;
        vector<vector<float>> biases;
    public:
        DNN(vector<vector<vector<float> >> weights, vector<vector<float>> biases);
        void feedForward(vector<vector<float> > input);
        vector<string> topThree();
};

#endif