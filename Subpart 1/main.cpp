#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<algorithm>
#include<cmath>
#include "fclayer.h"
#include "activationFns.h"
#include "subsampling.h"
#include "inpout.h"
using namespace std;

#define Mat vector<vector<float> >
#define Vec vector<float>

int main(int argc, char** argv){

    if(argc==1){
        cout<<"Invalid arguments"<<endl;
        cout<<"Usage: ./main <function_name> ...."<<endl;
        return 0;
    }

    string fun = argv[1];

    if (fun=="fullyconnected"){
        if (argc != 6){
            cout<<"Invalid arguments"<<endl;
            cout<<"Usage: ./main fullyconnected <input_file> <weight_file> <bias_file> <output_file>"<<endl;
            return 0;
        }
        string input_file = argv[2];
        string weight_file = argv[3];
        string bias_file = argv[4];
        string output_file = argv[5];
        Mat M = readMatrix(input_file);
        Mat W = readMatrix(weight_file);
        Mat B = readMatrix(bias_file);

        if((M[0].size()!=W.size()) || (W[0].size()!=B[0].size()) || (M.size()!=B.size())){
            cout<<"Invalid matrix dimensions"<<endl;
            return 0;
        }

        Mat output = FC_Layer(M,W,B);
        //printMat(output);
        writeMatrix(output,output_file);
    }

    else if (fun=="activation"){
        if (argc != 5){
            cout<<"Invalid arguments"<<endl;
            cout<<"Usage: ./main activation <function> <input_file> <output_file>"<<endl;
            return 0;
        }
        string function = argv[2];
        string input_file = argv[3];
        string output_file = argv[4];
        Mat M = readMatrix(input_file);
        Mat output;
        if (function == "relu")
            output = relu(M);
        else
            output = tanh(M);
        //printMat(output);
        writeMatrix(output,output_file);
    }

    else if (fun=="pooling"){
        if (argc != 6){
            cout<<"Invalid arguments"<<endl;
            cout<<"Usage: ./main pooling <type> <input_file> <stride> <output_file>"<<endl;
            return 0;
        }
        string type = argv[2];
        string input_file = argv[3];
        int stride = stoi(argv[4]);
        string output_file = argv[5];
        Mat M = readMatrix(input_file);
        printMat(M);
        Mat output;
        if (type == "max")
            output = maxPooling(M,stride);
        else
            output = avgPooling(M,stride);
        //printMat(output);
        writeMatrix(output,output_file);
    }

    else if (fun=="probability"){
        if (argc != 5){
            cout<<"Invalid arguments"<<endl;
            cout<<"Usage: ./main probability <function> <input_file> <output_file>"<<endl;
            return 0;
        }
        string type = argv[2];
        string input_file = argv[3];
        string output_file = argv[4];
        Vec V = readVector(input_file);
        Vec output;
        if (type == "softmax")
            output = softmax(V);
        else
            output = sigmoid(V);
        //printVec(output);
        writeVector(output,output_file);
    }

    return 0;
}