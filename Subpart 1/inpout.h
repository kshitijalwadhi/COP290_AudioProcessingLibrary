#ifndef INPUTOUTPUT_H
#define INPUTOUTPUT_H

#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;
#define Mat vector<vector<float> >
#define Vec vector<float>

Mat readMatrix(string filename){
    Vec temp;
    ifstream file(filename);
    string line;
    // read dimensions
    getline(file,line);
    stringstream ss(line);
    int m;
    ss >> m;
    getline(file,line);
    ss.clear();
    ss.str(line);
    int n;
    ss >> n;

    // read matrix
    while(getline(file,line)){
        stringstream ss(line);
        string token;
        while(getline(ss,token,' ')){
            temp.push_back(stof(token));
        }
    }

    Mat M;
    M.resize(n);
    for(int i=0;i<n;i++){
        M[i].resize(m);
    }
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            M[j][i] = temp[i*n+j];
        }
        }
    return M;
}

Vec readVector(string filename){
    Vec V;
    ifstream file(filename);
    string line;
    // read dimensions
    getline(file,line);
    stringstream ss(line);
    int n;
    ss >> n;
    // read vector
    while(getline(file,line)){
        stringstream ss(line);
        string token;
        while(getline(ss,token,' ')){
            V.push_back(stof(token));
        }
    }
    return V;
}

void printVec(Vec V){
    for(int i=0;i<V.size();i++){
        cout<<V[i]<<" ";
    }
    cout<<endl;
}

void printMat(Mat M){
    for(int i=0;i<M.size();i++){
        for(int j=0;j<M[0].size();j++){
            cout<<M[i][j]<<" ";
        }
        cout<<endl;
    }
}

void writeMatrix(Mat M, string filename){
    ofstream file(filename);
    file<<M[0].size()<<endl<<M.size()<<endl;
    for(int i=0;i<M[0].size();i++){
        for(int j=0;j<M.size();j++){
            file<<M[j][i]<<endl;
        }
    }
}

void writeVector(Vec V, string filename){
    ofstream file(filename);
    file<<V.size()<<endl;
    for(int i=0;i<V.size();i++){
        file<<V[i]<<endl;
    }
}

#endif