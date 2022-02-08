#ifndef SUBSAMPLING_H
#define SUBSAMPLING_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
using namespace std;
#define Mat vector<vector<float> >
#define Vec vector<float>

/*
Function to perform max pooling on a matrix
Input:
    M: input matrix
    stride: size of the pooling window
Output:
    output: output matrix
*/
Mat max_pooling(Mat M, int stride)
{
    int n = M.size();
    Mat output(n / stride, Vec(n / stride));

    int itr_i = 0;
    int itr_j = 0;

    for (int i = 0; i < n; i += stride)
    {
        for (int j = 0; j < n; j += stride)
        {
            float temp = -INFINITY;
            for (int x = 0; x < stride; x++)
            {
                for (int y = 0; y < stride; y++)
                {
                    temp = max(temp, M[i + x][j + y]);
                }
            }
            output[itr_i][itr_j] = temp;
            itr_j += 1;
        }
        itr_j = 0;
        itr_i += 1;
    }
    return output;
}

/*
Function to perform average pooling on a matrix
Input:
    M: input matrix
    stride: size of the pooling window
Output:
    output: output matrix
*/
Mat avg_pooling(Mat M, int stride)
{
    int n = M.size();
    Mat output(n / stride, Vec(n / stride));

    int itr_i = 0;
    int itr_j = 0;

    for (int i = 0; i < n; i += stride)
    {
        for (int j = 0; j < n; j += stride)
        {
            float avg = 0;
            int t = 1;

            for (int x = 0; x < stride; x++)
            {
                for (int y = 0; y < stride; y++)
                {
                    avg += (M[i + x][j + y] - avg) / t;
                    t += 1;
                }
            }
            output[itr_i][itr_j] = avg;
            itr_j += 1;
        }
        itr_j = 0;
        itr_i += 1;
    }
    return output;
}

#endif