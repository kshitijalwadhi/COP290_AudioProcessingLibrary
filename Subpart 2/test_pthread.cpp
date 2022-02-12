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

int START_SZ = 32;
int END_SZ = 513;
int NUM_TESTS = 30;
int MAX_THREADS = 4;

int main(){

    ofstream f_mean,f_all,f_stat;
    f_mean.open("results_pthread_mean.dat");
    f_all.open("results_pthread_all.dat");
    f_stat.open("results_pthread_stat.dat");

    for (int i = START_SZ;i<END_SZ;i*=2)
    {
        for (int numT=1;numT<=MAX_THREADS;numT++)
        {
            vector<float> times_pthread;

            for(int j=0;j<NUM_TESTS;j++)
            {
                Mat M1 = randMat(i,i);
                Mat M2 = randMat(i,i);
                auto start_time = high_resolution_clock::now();
                Mat M3 = spawnThreads(M1,M2,numT);
                auto end_time = high_resolution_clock::now();

                times_pthread.push_back(duration_cast<microseconds>(end_time - start_time).count());
                f_all << i << " " << numT << " " << duration_cast<microseconds>(end_time - start_time).count() << endl;
            }

            float avg_pthread = 0;
            float std_pthread = 0;
            for(int j=0;j<NUM_TESTS;j++)
            {
                avg_pthread += times_pthread[j];
            }
            avg_pthread /= NUM_TESTS;
            for(int j=0;j<NUM_TESTS;j++)
            {
                std_pthread += pow(times_pthread[j]-avg_pthread,2);
            }
            std_pthread = sqrt(std_pthread/NUM_TESTS);

            f_mean << i << " " << numT << " " << avg_pthread << endl;
            f_stat << i << " " << numT << " " << avg_pthread << " " << std_pthread << endl;
        }
    }
    f_mean.close();
    f_stat.close();
    f_all.close();
    return 0;
}