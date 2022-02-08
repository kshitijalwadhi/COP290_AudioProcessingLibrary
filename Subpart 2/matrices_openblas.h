#ifndef FCLAYER_BLAS_H
#define FCLAYER_BLAS_H

#include <vector>

#define Mat std::vector<std::vector<float> >
#define Vec std::vector<float>

Mat matmul_blas(Mat M1, Mat M2);
Mat FC_Layer_blas(Mat M, Mat W, Mat B);


#endif