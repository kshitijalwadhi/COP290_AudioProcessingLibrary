#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;

#define Mat vector<vector<float> >
#define Vec vector<float>

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