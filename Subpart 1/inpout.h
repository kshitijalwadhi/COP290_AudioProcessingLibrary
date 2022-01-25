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
    Mat temp;
    ifstream file(filename);
    string line;
    while(getline(file,line)){
        stringstream ss(line);
        string token;
        vector<float> row;
        while(getline(ss,token,' ')){
            row.push_back(stof(token));
        }
        temp.push_back(row);
    }
    Mat M;
    for(int i=0;i<temp[0].size();i++){
        vector<float> row;
        for(int j=0;j<temp.size();j++){
            row.push_back(temp[j][i]);
        }
        M.push_back(row);
    }

    return M;
}

Vec readVector(string filename){
    Vec V;
    ifstream file(filename);
    string line;
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

#endif