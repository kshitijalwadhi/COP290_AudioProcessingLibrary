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
#include "inpout.h"
using namespace std;
using namespace std::chrono;

// #define Mat vector<vector<float> >
// #define Vec vector<float>

void printMat(Mat M){
    for(int i=0;i<M.size();i++){
        for(int j=0;j<M[0].size();j++){
            cout<<M[i][j]<<" ";
        }
        cout<<endl;
    }
}

Mat randMat(int a, int b){
    Mat M(a, Vec(b));
    for(int i=0;i<a;i++){
        for(int j=0;j<b;j++){
            M[i][j] = rand()%10;
        }
    }
    return M;
}

bool isEqual(Mat M1, Mat M2){
    if(M1.size() != M2.size()){
        return false;
    }
    for(int i=0;i<M1.size();i++){
        for(int j=0;j<M1[0].size();j++){
            if(M1[i][j] != M2[i][j]){
                return false;
            }
        }
    }
    return true;
}

int main(){

    Mat M1 = randMat(2000,80);
    Mat M2 = randMat(80,1000);

    auto start_time = high_resolution_clock::now();
    Mat M4 = matmul(M1,M2);
    auto end_time_1 = high_resolution_clock::now();
    spawnThreads(M1,M2,NUM_CORES);
    auto end_time_2 = high_resolution_clock::now();
    Mat M5 = matmul_blas(M1,M2);
    auto end_time_3 = high_resolution_clock::now();
    Mat M6 = matmul_mkl(M1,M2);
    auto end_time_4 = high_resolution_clock::now();

    cout<<"Time taken without threading: "<<duration_cast<microseconds>(end_time_1 - start_time).count()/1000<<" milliseconds"<<endl;
    cout<<"Time taken with threading: "<<duration_cast<microseconds>(end_time_2 - end_time_1).count()/1000<<" milliseconds"<<endl;    
    cout<<"Time taken with blas: "<<duration_cast<microseconds>(end_time_3 - end_time_2).count()/1000<<" milliseconds"<<endl;
    cout<<"Time taken with mkl: "<<duration_cast<microseconds>(end_time_4 - end_time_3).count()/1000<<" milliseconds"<<endl;

    return 0;
}