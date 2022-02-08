#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
using namespace std;
#define Mat vector<vector<float> >
#define Vec vector<float>

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