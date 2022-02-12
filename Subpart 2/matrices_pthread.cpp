#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <thread>
#include <pthread.h>
#include "matrices.h"
using namespace std;
#define NUM_CORES 4
#define Mat vector<vector<float> >
#define Vec vector<float>

Mat M3;
struct arguments {
    Mat M1;
    Mat M2;
    int start_row;
    int end_row;
};

/*
Function to perform matrix multiplication of two matrices with multi-threading
*/
void* multi(void* args)
{
    arguments* argument = (arguments*)args;
    Mat M1 = argument->M1;
    Mat M2 = argument->M2;
    int start_row = argument->start_row;
    int end_row = argument->end_row;

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
    pthread_exit(NULL);
}

Mat spawnThreads(Mat M1, Mat M2, int n)
{
    int a = M1.size();
    int b = M1[0].size();
    int c = M2[0].size();

    M3.clear();
    M3.resize(a, Vec(c));

    pthread_t threads[NUM_CORES];

    for (int i=0;i<n;i++)
    {
        arguments* arg = new arguments;
        arg->M1 = M1;
        arg->M2 = M2;
        arg->start_row = i * M1.size() / n;
        arg->end_row = (i + 1) * M1.size() / n;
        pthread_create(&threads[i], NULL, multi, (void*)arg);
    }

    for (int i=0;i<n;i++)
    {
        pthread_join(threads[i], NULL);
    }

    return M3;
}