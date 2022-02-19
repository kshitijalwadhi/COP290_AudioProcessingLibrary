#ifndef DNN_H
#define DNN_H
#include <vector>
#include <string>

using namespace std;

class DNN
{
    private:
        vector<vector<vector<float> >> weights;
        vector<vector<vector<float> >> biases;
        vector<float> output;
        vector<string> class_labels;
    public:
        DNN(vector<vector<vector<float> >> weights, vector<vector<vector<float> >> biases, vector<string> class_labels);
        void feedForward(vector<vector<float> > input);
        vector<string> topThree();
};

#endif