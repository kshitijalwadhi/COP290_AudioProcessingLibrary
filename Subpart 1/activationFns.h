#ifndef ACTIVATIONFNS_H
#define ACTIVATIONFNS_H

#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<cmath>
using namespace std;
#define Mat vector<vector<float> >
#define Vec vector<float>

/*
Function to perform relu on a matrix
Input:
    M: input matrix
Output:
    output: output matrix
*/
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

/*
Function to perform tanh on a matrix
Input:
    M: input matrix
Output:
    output: output matrix
*/
Mat tanh(Mat input){
    for(int i=0;i<input.size();i++){
        for(int j=0;j<input[0].size();j++){
            //input[i][j]=tanh(input[i][j]);
            float x = input[i][j];
            input[i][j] = (exp(2*x)-1)/(exp(2*x)+1);
        }
    }
    return input;
}

/*
Function to perform sigmoid on a vector
Input:
    V: input vector
Output:
    output: output vector
*/
Vec sigmoid(Vec input){
    int n = input.size();
    for(int i=0;i<n;i++){
        input[i] = 1/(1+exp(-input[i]));
    }
    return input;
}

/*
Function to perform softmax on a vector
Input:
    V: input vector
Output:
    output: output vector
*/
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