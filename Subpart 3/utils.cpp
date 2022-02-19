#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include "matrices.h"
#include "matrices_mkl.h"
#include "matrices_openblas.h"
#include "matrices_pthread.h"
using namespace std;
#define NUM_CORES 4

/*
Function to check if the file exists
Input:
    filename: name of the file
Output:
    true if the file exists
    false if the file does not exist
*/
bool is_file_exist(string filename)
{
    ifstream ifile(filename.c_str());
    if (ifile)
    {
        ifile.close();
        return true;
    }
    else
    {
        return false;
    }
}

/*
Function to read Matrix from a file
Input:
    filename: name of the file
Output:
    M: Matrix read from the file
*/
Mat read_matrix(string filename)
{
    Vec temp;
    ifstream file(filename);
    string line;
    // read dimensions
    getline(file, line);
    stringstream ss(line);
    int m;
    ss >> m;
    getline(file, line);
    ss.clear();
    ss.str(line);
    int n;
    ss >> n;

    // read matrix
    while (getline(file, line))
    {
        stringstream ss(line);
        string token;
        while (getline(ss, token, ' '))
        {
            temp.push_back(stof(token));
        }
    }

    Mat M;
    M.resize(n);
    for (int i = 0; i < n; i++)
    {
        M[i].resize(m);
    }
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            M[j][i] = temp[i * n + j];
        }
    }
    return M;
}

/*
Function to read a vector from a file
Input:
    filename: name of the file
Output:
    V: vector read from the file
*/
Vec read_vector(string filename)
{
    Vec V;
    ifstream file(filename);
    string line;
    // read dimensions
    getline(file, line);
    stringstream ss(line);
    int n;
    ss >> n;
    // read vector
    while (getline(file, line))
    {
        stringstream ss(line);
        string token;
        while (getline(ss, token, ' '))
        {
            V.push_back(stof(token));
        }
    }
    return V;
}

/*
Function to print a vector
Input:
    V: vector to be printed
*/
void print_vector(Vec V)
{
    for (int i = 0; i < V.size(); i++)
    {
        cout << V[i] << " ";
    }
    cout << endl;
}

/*
Function to print a matrix
Input:
    M: matrix to be printed
*/
void print_matrix(Mat M)
{
    for (int i = 0; i < M.size(); i++)
    {
        for (int j = 0; j < M[0].size(); j++)
        {
            cout << M[i][j] << " ";
        }
        cout << endl;
    }
}

/*
Function to write a Matrix M to a file
Input:
    M: Matrix to be written
    filename: name of the file
*/
void write_matrix(Mat M, string filename)
{
    ofstream file(filename);
    file << M[0].size() << endl
         << M.size() << endl;
    for (int i = 0; i < M[0].size(); i++)
    {
        for (int j = 0; j < M.size(); j++)
        {
            file << M[j][i] << endl;
        }
    }
}

/*
Function to write a vector V to a file
Input:
    V: vector to be written
    filename: name of the file
*/
void write_vector(Vec V, string filename)
{
    ofstream file(filename);
    file << V.size() << endl;
    for (int i = 0; i < V.size(); i++)
    {
        file << V[i] << endl;
    }
}

Mat randMat(int a, int b){
    Mat M(a, Vec(b));
    for(int i=0;i<a;i++){
        for(int j=0;j<b;j++){
            float num = (float) rand()/RAND_MAX;
            float ran_sign = rand()%2;
            if (ran_sign == 0)
                num = -num;
            M[i][j] = num;
        }
    }
    return M;
}

Vec randVec(int a){
    Vec V(a);
    for(int i=0;i<a;i++){
        V[i] = (float) rand()/RAND_MAX;
    }
    return V;
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
    int method: Method to be used for matrix multiplication (0: Standard, 1: Pthread, 2: OpenBLAS, 3: MKL)
Output:
    Mat: Output of the layer
*/
Mat FC_Layer(Mat M, Mat W, Mat B, int method=0)
{
    if(method==0)
    {
        Mat output = matmul(M, W);
        output = add(output, B);
        return output;
    }
    else if(method == 1)
    {
        if (M.size() < NUM_CORES)
        {
            Mat output = matmul(M, W);
            output = add(output, B);
            return output;
        }
        Mat M3 = spawnThreads(M, W, NUM_CORES);
        return add(M3, B);
    }
    else if(method==2)
    {
        Mat output = matmul_blas(M, W);
        output = add(output, B);
        return output;
    }
    else
    {
        Mat output = matmul_mkl(M, W);
        output = add(output, B);
        return output;
    }
}

Vec flatten(Mat M){
    Vec V;
    for(int i=0;i<M.size();i++){
        for(int j=0;j<M[0].size();j++){
            V.push_back(M[i][j]);
        }
    }
    return V;
}