#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<cmath>
#include<thread>
#include<chrono>
#include "/home/kshitij/libs/OpenBLAS/cblas.h"
using namespace std;
using namespace std::chrono;
#define Mat vector<vector<float> >
#define Vec vector<float>
//#define NUM_CORES 4


Mat matmul(Mat M1, Mat M2){
    int a = M1.size();
    int b = M1[0].size();
    int c = M2[0].size();
    Mat M3(a, Vec(c));
    for(int i=0;i<a;i++){
        for(int j=0;j<c;j++){
            for(int k=0;k<b;k++){
                M3[i][j] += M1[i][k]*M2[k][j];
            }
        }
    }
    return M3;
}

Mat matmul_blas(Mat M1, Mat M2){
    int a = M1.size();
    int b = M1[0].size();
    int c = M2[0].size();
    float *A_rowmajor = new float[a*b];
    float *B_colmajor = new float[b*c];
    float *C_rowmajor = new float[a*c];
    for(int i=0;i<a;i++){
        for(int j=0;j<b;j++){
            A_rowmajor[i*b+j] = M1[i][j];
        }
    }
    for(int i=0;i<b;i++){
        for(int j=0;j<c;j++){
            B_colmajor[i*c+j] = M2[i][j];
        }
    }
    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, a, c, b, 1.0, A_rowmajor, b, B_colmajor, c, 0.0, C_rowmajor, c);
    Mat M3(a, Vec(c));
    for(int i=0;i<a;i++){
        for(int j=0;j<c;j++){
            M3[i][j] = C_rowmajor[i*c+j];
        }
    }
    return M3;
}

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
    Mat M3 = matmul_blas(M1,M2);
    auto end_time_2 = high_resolution_clock::now();

    bool equal = isEqual(M4,M3);
    if(!equal){
        cout<<"Matrices are not equal"<<endl;
    }
    else{
        cout<<"Time taken using O(n^3) algo: "<<duration_cast<microseconds>(end_time_1 - start_time).count()/1000<<" milliseconds"<<endl;
        cout<<"Time taken using openBLAS: "<<duration_cast<microseconds>(end_time_2 - end_time_1).count()/1000<<" milliseconds"<<endl;    
    }

    return 0;
}
