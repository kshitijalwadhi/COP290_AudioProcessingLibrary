#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;

#define Mat vector<vector<float> >
#define Vec vector<float>

Vec sigmoid(Vec input){
    int n = input.size();
    for(int i=0;i<n;i++){
        input[i] = 1/(1+exp(-input[i]));
    }
    return input;
}