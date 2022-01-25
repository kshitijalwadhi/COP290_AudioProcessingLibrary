#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;

#define Mat vector<vector<float> >
#define Vec vector<float>

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

Mat FC_Layer(Mat M, Mat W, Mat B){
    Mat output = matmul(M,W);
    for(int i=0;i<B.size();i++){
        for(int j=0;j<B[0].size();j++){
            output[i][j] += B[i][j];
        }
    }
    return output;
}

int main(){
    Mat M = {{1,1,1},{1,1,1}};
    Mat W = {{1,1},{1,1},{1,1}};
    Mat B = {{1,1},{1,1}};
    Mat output = FC_Layer(M,W,B);
    for(int i=0;i<output.size();i++){
        for(int j=0;j<output[0].size();j++){
            cout<<output[i][j]<<" ";
        }
        cout<<endl;
    }
    return 0;
}