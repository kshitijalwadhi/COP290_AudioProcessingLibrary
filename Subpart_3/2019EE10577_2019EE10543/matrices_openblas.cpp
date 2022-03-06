#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include "matrices.h"
#include "cblas.h"
using namespace std;
#define Mat vector<vector<float> >
#define Vec vector<float>

/*
Function to perform matrix multiplication of two matrices with openblas
Input:
    Mat A: Matrix A
    Mat B: Matrix B
Output:
    Mat: Result of matrix multiplication
*/
Mat matmul_blas(Mat M1, Mat M2)
{
    int a = M1.size();
    int b = M1[0].size();
    int c = M2[0].size();
    float *A_rowmajor = new float[a * b];
    float *B_colmajor = new float[b * c];
    float *C_rowmajor = new float[a * c];
    for (int i = 0; i < a; i++)
    {
        for (int j = 0; j < b; j++)
        {
            A_rowmajor[i * b + j] = M1[i][j];
        }
    }
    for (int i = 0; i < b; i++)
    {
        for (int j = 0; j < c; j++)
        {
            B_colmajor[i * c + j] = M2[i][j];
        }
    }
    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, a, c, b, 1.0, A_rowmajor, b, B_colmajor, c, 0.0, C_rowmajor, c);
    Mat M3(a, Vec(c));
    for (int i = 0; i < a; i++)
    {
        for (int j = 0; j < c; j++)
        {
            M3[i][j] = C_rowmajor[i * c + j];
        }
    }
    return M3;
}

