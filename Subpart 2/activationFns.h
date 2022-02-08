#ifndef ACTIVATIONFNS_H
#define ACTIVATIONFNS_H
#include <vector>

#define Mat std::vector<std::vector<float> >
#define Vec std::vector<float>

Mat relu(Mat input);
Mat tanh(Mat input);
Vec sigmoid(Vec input);
Vec softmax(Vec input);


#endif