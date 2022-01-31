#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
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

        bool flag = is_file_exist(input_file) && is_file_exist(weight_file) && is_file_exist(bias_file);
        if(flag == false){
            cout<<"One of the files don't exist"<<endl;
            cout<<"Check the file paths"<<endl;
            return 0;
        }
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

        bool flag = is_file_exist(input_file);
        if(flag == false){
            cout<<"Input file doesn't exist"<<endl;
            cout<<"Check the file path"<<endl;
            return 0;
        }

        Mat M = readMatrix(input_file);
        Mat output;
        if (function == "relu")
            output = relu(M);
        else if (function == "tanh")
            output = tanh(M);
        else{
            cout<<"Invalid function"<<endl;
            cout<<"Usage: ./main activation <function>(relu/tanh) <input_file> <output_file>"<<endl;
            return 0;
        }
        //printMat(output);
        writeMatrix(output,output_file);
    }

    else if (fun=="pooling"){
        if (argc != 6){
            cout<<"Invalid arguments"<<endl;
            cout<<"Usage: ./main pooling <type> <input_file> <stride> <output_file>"<<endl;
            return 0;
        }
        try{
            string type = argv[2];
            string input_file = argv[3];
            string stride = argv[4];
            string output_file = argv[5];

            bool flag = is_file_exist(input_file);
            if(flag == false){
                cout<<"Input file doesn't exist"<<endl;
                cout<<"Check the file path"<<endl;
                return 0;
            }

            Mat M = readMatrix(input_file);
            int s = stoi(stride);
            Mat output;
            if (type == "max")
                output = maxPooling(M,s);
            else if (type == "average")
                output = avgPooling(M,s);
            else{
                cout<<"Invalid pooling type"<<endl;
                cout<<"Usage: ./main pooling <type>(max/average) <input_file> <stride> <output_file>"<<endl;
                return 0;
            }
            //printMat(output);
            writeMatrix(output,output_file);
        }
        catch(exception& e){
            cout<<"Invalid arguments"<<endl;
            cout<<"Usage: ./main pooling <type> <input_file> <stride> <output_file>"<<endl;
            return 0;
        }
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

        bool flag = is_file_exist(input_file);
        if(flag == false){
            cout<<"Input file doesn't exist"<<endl;
            cout<<"Check the file path"<<endl;
            return 0;
        }

        Vec V = readVector(input_file);
        Vec output;
        if (type == "softmax")
            output = softmax(V);
        else if (type == "sigmoid")
            output = sigmoid(V);
        else{
            cout<<"Invalid function"<<endl;
            cout<<"Usage: ./main probability <function>(softmax/sigmoid) <input_file> <output_file>"<<endl;
            return 0;
        }
        //printVec(output);
        writeVector(output,output_file);
    }

    else{
        cout<<"Invalid function name"<<endl;
        cout<<"Usage: ./main <function_name> ...."<<endl;
        return 0;
    }

    return 0;
}