#ifndef FCLAYER_H
#define FCLAYER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
using namespace std;
#define Mat vector<vector<float> >
#define Vec vector<float>

/*
Function to perform matrix multiplication of two matrices in O(n^3) time
Input:
    Mat A: Matrix A
    Mat B: Matrix B
Output:
    Mat: Result of matrix multiplication
*/

Mat matmul(Mat M1, Mat M2)
{
    int a = M1.size();
    int b = M1[0].size();
    int c = M2[0].size();
    Mat M3(a, Vec(c));
    for (int i = 0; i < a; i++)
    {
        for (int j = 0; j < c; j++)
        {
            for (int k = 0; k < b; k++)
            {
                M3[i][j] += M1[i][k] * M2[k][j];
            }
        }
    }
    return M3;
}

/*
Function to perform addition of two matrices.
Input:
    Mat A: Matrix A
    Mat B: Matrix B
Output:
    Mat: Result of addition
*/
Mat add(Mat M1, Mat M2)
{
    int a = M1.size();
    int b = M1[0].size();
    Mat M3(a, Vec(b));
    for (int i = 0; i < a; i++)
    {
        for (int j = 0; j < b; j++)
        {
            M3[i][j] = M1[i][j] + M2[i][j];
        }
    }
    return M3;
}

/*
Function to perform the forward pass of a fully connected layer
Input:
    Mat input: Input to the layer
    Mat weights: Weights of the layer
    Mat bias: Bias of the layer
Output:
    Mat: Output of the layer
*/

Mat FC_Layer(Mat M, Mat W, Mat B)
{
    Mat output = matmul(M, W);
    output = add(output, B);
    return output;
}

#endif