#ifndef FCLAYER_MKL_H
#define FCLAYER_MKL_H

#include <vector>

#define Mat std::vector<std::vector<float> >
#define Vec std::vector<float>

Mat matmul_mkl(Mat M1, Mat M2);


#endif