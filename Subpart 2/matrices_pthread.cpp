#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <thread>
#include "matrices.h"
using namespace std;
#define NUM_CORES 4
#define Mat vector<vector<float> >
#define Vec vector<float>

Mat M3;

/*
Function to perform matrix multiplication of two matrices with multi-threading
Input:
    Mat A: Matrix A
    Mat B: Matrix B
Output:
    Mat: Result of matrix multiplication
*/

void matmul_threading(Mat M1, Mat M2, int start_row, int end_row)
{
    int a = M1.size();
    int b = M1[0].size();
    int c = M2[0].size();
    for (int i = start_row; i < end_row; i++)
    {
        for (int j = 0; j < c; j++)
        {
            for (int k = 0; k < b; k++)
            {
                M3[i][j] += M1[i][k] * M2[k][j];
            }
        }
    }
}

void spawnThreads(Mat M1, Mat M2, int n)
{
    std::vector<thread> threads(n);
    int a = M1.size();
    int b = M1[0].size();
    int c = M2[0].size();

    M3.clear();
    M3.resize(a, Vec(c));

    for (int i = 0; i < n; i++)
    {
        threads[i] = thread(matmul_threading, M1, M2, i * M1.size() / n, (i + 1) * M1.size() / n);
    }

    for (auto &th : threads)
    {
        th.join();
    }
}