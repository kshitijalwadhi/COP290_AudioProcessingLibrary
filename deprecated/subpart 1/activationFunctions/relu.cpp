#include<iostream>
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

int main(){
    Mat M = {{1,-2,3,4.4},{5,6,7,8},{9,10,11,12}};
    Mat output = relu(M);
    for(int i=0;i<output.size();i++){
        for(int j=0;j<output[0].size();j++){
            cout<<output[i][j]<<" ";
        }
        cout<<endl;
    }
    return 0;
}