#ifndef SUBSAMPLING_H
#define SUBSAMPLING_H

#include <vector>

#define Mat std::vector<std::vector<float> >
#define Vec std::vector<float>

Mat max_pooling(Mat M, int stride);
Mat avg_pooling(Mat M, int stride);

#endif