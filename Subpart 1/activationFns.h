#ifndef ACTIVATIONFNS_H
#define ACTIVATIONFNS_H

#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;
#define Mat vector<vector<float> >
#define Vec vector<float>

Mat relu(Mat input){
    for(int i=0;i<input.size();i++){
        for(int j=0;j<input[0].size();j++){
            if(input[i][j]<0){
                input[i][j]=0;
            }
        }
    }
    return input;
}

Mat tanh(Mat input){
    for(int i=0;i<input.size();i++){
        for(int j=0;j<input[0].size();j++){
            input[i][j]=tanh(input[i][j]);
        }
    }
    return input;
}


Vec sigmoid(Vec input){
    int n = input.size();
    for(int i=0;i<n;i++){
        input[i] = 1/(1+exp(-input[i]));
    }
    return input;
}

Vec softmax(Vec input){
    int n = input.size();
    float sum = 0;
    for(int i=0;i<n;i++){
        sum += exp(input[i]);
    }
    for(int i=0;i<n;i++){
        input[i] = exp(input[i])/sum;
    }
    return input;
}

#endif