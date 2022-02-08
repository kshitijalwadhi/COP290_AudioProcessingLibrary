#ifndef MATRICES_H
#define MATRICES_H

#include <vector>
std::vector<std::vector<float> > matmul(std::vector<std::vector<float> > M1, std::vector<std::vector<float> > M2);
std::vector<std::vector<float> > add(std::vector<std::vector<float> > M1, std::vector<std::vector<float> > M2);
std::vector<std::vector<float> > FC_Layer(std::vector<std::vector<float> > M, std::vector<std::vector<float> > W, std::vector<std::vector<float> > B);

#endif