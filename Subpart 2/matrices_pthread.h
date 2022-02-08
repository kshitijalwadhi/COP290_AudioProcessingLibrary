#ifndef FCLAYER_PTHREAD_H
#define FCLAYER_PTHREAD_H
#include <vector>
#define NUM_CORES 4

#define Mat std::vector<std::vector<float> >
#define Vec std::vector<float>

void matmul_threading(Mat M1, Mat M2, int start_row, int end_row);
void spawnThreads(Mat M1, Mat M2, int n);
Mat FC_Layer_pthread(Mat M, Mat W, Mat B);


#endif