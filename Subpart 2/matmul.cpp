#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<algorithm>
#include<cmath>
#include<thread>
#include<chrono>
using namespace std;
using namespace std::chrono;
#define Mat vector<vector<float> >
#define Vec vector<float>
#define NUM_CORES 4

Mat M3;

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


void matmul_threading(Mat M1, Mat M2, int start_row, int end_row){
    int a = M1.size();
    int b = M1[0].size();
    int c = M2[0].size();
    for(int i=start_row;i<end_row;i++){
        for(int j=0;j<c;j++){
            for(int k=0;k<b;k++){
                M3[i][j] += M1[i][k]*M2[k][j];
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

    M3.resize(a, Vec(c));

    for (int i = 0; i < n; i++) {
        threads[i] = thread(matmul_threading, M1, M2, i*M1.size()/n, (i+1)*M1.size()/n);
    }

    for (auto& th : threads) {
        th.join();
    }
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

int main(){

    Mat M1 = randMat(2000,80);
    Mat M2 = randMat(80,1000);

    auto start_time = high_resolution_clock::now();
    Mat M3 = matmul(M1,M2);
    auto end_time_1 = high_resolution_clock::now();
    spawnThreads(M1,M2,NUM_CORES);
    auto end_time_2 = high_resolution_clock::now();

    cout<<"Time taken without threading: "<<duration_cast<microseconds>(end_time_1 - start_time).count()/1000<<" milliseconds"<<endl;
    cout<<"Time taken with threading: "<<duration_cast<microseconds>(end_time_2 - end_time_1).count()/1000<<" milliseconds"<<endl;

    return 0;
}
