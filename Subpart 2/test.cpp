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
bool check_correctness = true;

int main(){

    ofstream f_mean,f_all,f_stat;
    f_mean.open("results_mean.dat");
    f_all.open("results_all.dat");
    f_stat.open("results_stat.dat");

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
            Mat M3 = spawnThreads(M1,M2,NUM_CORES);
            auto end_time_2 = high_resolution_clock::now();
            Mat M5 = matmul_blas(M1,M2);
            auto end_time_3 = high_resolution_clock::now();
            Mat M6 = matmul_mkl(M1,M2);
            auto end_time_4 = high_resolution_clock::now();

            if (check_correctness)
            {
                bool flag1 = isEqual(M4,M3);
                bool flag2 = isEqual(M3,M5);
                bool flag3 = isEqual(M5,M6);
                bool flag = flag1 && flag2 && flag3;
                if(flag==false)
                    cout<<"Results are different"<<endl;
            }

            times_normal.push_back(duration_cast<microseconds>(end_time_1 - start_time).count());
            times_pthread.push_back(duration_cast<microseconds>(end_time_2 - end_time_1).count());
            times_openblas.push_back(duration_cast<microseconds>(end_time_3 - end_time_2).count());
            times_mkl.push_back(duration_cast<microseconds>(end_time_4 - end_time_3).count());
        }

        float avg_normal = 0;
        float avg_pthread = 0;
        float avg_openblas = 0;
        float avg_mkl = 0;
        float std_normal = 0;
        float std_pthread = 0;
        float std_openblas = 0;
        float std_mkl = 0;
        for(int j=0;j<NUM_TESTS;j++)
        {
            avg_normal += times_normal[j];
            avg_pthread += times_pthread[j];
            avg_openblas += times_openblas[j];
            avg_mkl += times_mkl[j];
            f_all<<i<<" "<<times_normal[j]<<" "<<times_pthread[j]<<" "<<times_openblas[j]<<" "<<times_mkl[j]<<endl;
        }
        avg_normal = avg_normal/times_normal.size();
        avg_pthread = avg_pthread/times_pthread.size();
        avg_openblas = avg_openblas/times_openblas.size();
        avg_mkl = avg_mkl/times_mkl.size();

        for(int j =0;j<NUM_TESTS;j++)
        {
            std_normal += (times_normal[j]-avg_normal)*(times_normal[j]-avg_normal);
            std_pthread += (times_pthread[j]-avg_pthread)*(times_pthread[j]-avg_pthread);
            std_openblas += (times_openblas[j]-avg_openblas)*(times_openblas[j]-avg_openblas);
            std_mkl += (times_mkl[j]-avg_mkl)*(times_mkl[j]-avg_mkl);
        }
        std_normal = sqrt(std_normal/NUM_TESTS);
        std_pthread = sqrt(std_pthread/NUM_TESTS);
        std_openblas = sqrt(std_openblas/NUM_TESTS);
        std_mkl = sqrt(std_mkl/NUM_TESTS);

        f_mean << i << " " << avg_normal << " " << avg_pthread << " " << avg_openblas << " " << avg_mkl << endl;
        f_stat << i << " " << avg_normal << " " << std_normal << " " << avg_pthread << " " << std_pthread << " " << avg_openblas << " " << std_openblas << " " << avg_mkl << " " << std_mkl << endl;
    }
    f_mean.close();
    f_stat.close();
    f_all.close();
    return 0;
}