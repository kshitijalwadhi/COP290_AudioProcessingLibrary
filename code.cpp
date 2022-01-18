#include<iostream>
#include<fstream>
#include<sstream>
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

Mat maxPooling(Mat M,int stride){
    int n = M.size();
    vector<vector<float> > output( n/stride , vector<float> (n/stride));

    int itr_i=0;
    int itr_j=0;

    for(int i=0; i<n;i+=stride){
        for(int j=0; j<n; j+=stride){
            float temp = -INFINITY;
            for(int x=0;x<stride;x++){
                for(int y=0;y<stride;y++){
                    temp = max(temp,M[i+x][j+y]);
                }
            }
            output[itr_i][itr_j] = temp;
            itr_j+=1;
        }
        itr_j = 0;
        itr_i+=1;
    }
    return output;
}

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

int main(int argc, char** argv){

    if(argc==1){
        cout<<"Invalid arguments"<<endl;
        cout<<"Usage: ./code <function_name> ...."<<endl;
        return 0;
    }

    string fun = argv[1];

    if (fun=="fullyconnected"){
        if (argc != 5){
            cout<<"Invalid arguments"<<endl;
            cout<<"Usage: ./code fullyconnected <input_file> <weight_file> <bias_file>"<<endl;
            return 0;
        }
        string input_file = argv[2];
        string weight_file = argv[3];
        string bias_file = argv[4];
        Mat M = readMatrix(input_file);
        Mat W = readMatrix(weight_file);
        Mat B = readMatrix(bias_file);

        if((M[0].size()!=W.size()) || (W[0].size()!=B[0].size()) || (M.size()!=B.size())){
            cout<<"Invalid matrix dimensions"<<endl;
            return 0;
        }

        Mat output = FC_Layer(M,W,B);
        printMat(output);
    }

    else if (fun=="relu"){
        if (argc != 3){
            cout<<"Invalid arguments"<<endl;
            cout<<"Usage: ./code relu <input_file>"<<endl;
            return 0;
        }
        string input_file = argv[2];
        Mat M = readMatrix(input_file);
        Mat output = relu(M);
        printMat(output);
    }

    else if (fun=="tanh"){
        if (argc != 3){
            cout<<"Invalid arguments"<<endl;
            cout<<"Usage: ./code tanh <input_file>"<<endl;
            return 0;
        }
        string input_file = argv[2];
        Mat M = readMatrix(input_file);
        Mat output = tanh(M);
        printMat(output);
    }

    else if (fun=="maxpooling"){
        if (argc != 3){
            cout<<"Invalid arguments"<<endl;
            cout<<"Usage: ./code maxpooling <input_file>"<<endl;
            return 0;
        }
        string input_file = argv[2];
        //int stride = stoi(argv[3]);
        Mat M = readMatrix(input_file);
        Mat output = maxPooling(M,2);
        printMat(output);
    }

    else if (fun=="avgpooling"){
        if (argc != 3){
            cout<<"Invalid arguments"<<endl;
            cout<<"Usage: ./code avgpooling <input_file>"<<endl;
            return 0;
        }
        string input_file = argv[2];
        //int stride = stoi(argv[3]);
        Mat M = readMatrix(input_file);
        Mat output = avgPooling(M,2);
        printMat(output);
    }

    else if (fun=="sigmoid"){
        if (argc != 3){
            cout<<"Invalid arguments"<<endl;
            cout<<"Usage: ./code sigmoid <input_file>"<<endl;
            return 0;
        }
        string input_file = argv[2];
        Vec V = readVector(input_file);
        Vec output = sigmoid(V);
        printVec(output);
    }

    else if (fun=="softmax"){
        if (argc != 3){
            cout<<"Invalid arguments"<<endl;
            cout<<"Usage: ./code softmax <input_file>"<<endl;
            return 0;
        }
        string input_file = argv[2];
        Vec V = readVector(input_file);
        Vec output = softmax(V);
        printVec(output);
    }

    return 0;
}