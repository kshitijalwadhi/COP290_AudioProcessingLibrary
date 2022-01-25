#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;

#define Mat vector<vector<float> >
#define Vec vector<float>

Mat avgPooling(Mat M,int stride){
    int n = M.size();
    vector<vector<float> > output( n/stride , vector<float> (n/stride));

    int itr_i=0;
    int itr_j=0;

    for(int i=0; i<n;i+=stride){
        for(int j=0; j<n; j+=stride){
            float sum = 0;
            for(int x=0;x<stride;x++){
                for(int y=0;y<stride;y++){
                    sum += M[i+x][j+y];
                }
            }
            output[itr_i][itr_j] = sum/(stride*stride);
            itr_j+=1;
        }
        itr_j = 0;
        itr_i+=1;
    }
    return output;
}

int main(){
    Mat M = {{1,-2,3,4.4},{5,6,7,8},{9,10,11,12},{13,14,15,16}};
    Mat output = avgPooling(M,2);
    for(int i=0;i<output.size();i++){
        for(int j=0;j<output[0].size();j++){
            cout<<output[i][j]<<" ";
        }
        cout<<endl;
    }
    return 0;
}