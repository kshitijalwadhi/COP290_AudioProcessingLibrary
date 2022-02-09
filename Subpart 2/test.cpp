#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>
#include <cmath>
#include "matrices.h"
#include "matrices_mkl.h"
#include "matrices_openblas.h"
#include "matrices_pthread.h"
#include "activationFns.h"
#include "subsampling.h"
#include "utils.h"
using namespace std;
using namespace std::chrono;

#define NUM_CORES 4

int START_SZ = 64;
int END_SZ = 1024;
int NUM_TESTS = 4;

int main(){

    ofstream f;
    f.open("results.txt");

    for (int i = START_SZ;i<END_SZ;i*=2)
    {
        vector<float> times_normal;
        vector<float> times_pthread;
        vector<float> times_openblas;
        vector<float> times_mkl;

        for(int j=0;j<NUM_TESTS;j++)
        {
            Mat M1 = randMat(i,i);
            Mat M2 = randMat(i,i);

            auto start_time = high_resolution_clock::now();
            Mat M4 = matmul(M1,M2);
            auto end_time_1 = high_resolution_clock::now();
            spawnThreads(M1,M2,NUM_CORES);
            auto end_time_2 = high_resolution_clock::now();
            Mat M5 = matmul_blas(M1,M2);
            auto end_time_3 = high_resolution_clock::now();
            Mat M6 = matmul_mkl(M1,M2);
            auto end_time_4 = high_resolution_clock::now();

            times_normal.push_back(duration_cast<microseconds>(end_time_1 - start_time).count()/1000);
            times_pthread.push_back(duration_cast<microseconds>(end_time_2 - end_time_1).count()/1000);
            times_openblas.push_back(duration_cast<microseconds>(end_time_3 - end_time_2).count()/1000);
            times_mkl.push_back(duration_cast<microseconds>(end_time_4 - end_time_3).count()/1000);
        }

        float avg_normal = 0;
        float avg_pthread = 0;
        float avg_openblas = 0;
        float avg_mkl = 0;
        for(int j=0;j<NUM_TESTS;j++)
        {
            avg_normal += times_normal[j];
            avg_pthread += times_pthread[j];
            avg_openblas += times_openblas[j];
            avg_mkl += times_mkl[j];
        }
        avg_normal = avg_normal/times_normal.size();
        avg_pthread = avg_pthread/times_pthread.size();
        avg_openblas = avg_openblas/times_openblas.size();
        avg_mkl = avg_mkl/times_mkl.size();

        f << i << " " << avg_normal << " " << avg_pthread << " " << avg_openblas << " " << avg_mkl << endl;
    }
    f.close();
    return 0;
}