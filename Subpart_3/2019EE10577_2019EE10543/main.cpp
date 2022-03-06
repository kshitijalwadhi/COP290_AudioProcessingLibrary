#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include "audio.h"
using namespace std;

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        cout << "Invalid arguments" << endl;
        cout << "Usage: ./yourcode.out <audiosample_file> <output_file>" << endl;
        return 0;
    }
    string audio_file = argv[1];
    string output_file = argv[2];
    bool flag = is_file_exist(audio_file);
    if (flag == false)
    {
        cout << "Audio file doesn't exist" << endl;
        cout << "Check the file path" << endl;
        return 0;
    }
    vector<string> class_labels = {"silence", "unknown", "yes", "no", "up", "down", "left", "right", "on", "off", "stop", "go"};
    
    pred_t* pred = new pred_t[3];
    libaudioAPI(audio_file.c_str(), pred);

    ofstream outfile;
    bool flag1 = is_file_exist(output_file);
    if (flag1 == true)
        outfile.open(output_file, ios::app);
    else
        outfile.open(output_file);
    outfile << audio_file << " ";
    for (int i = 0; i < 3; i++)
    {
        outfile << class_labels[pred[i].label] << " ";
    }
    for (int i = 0; i < 3; i++)
    {
        outfile << pred[i].prob << " ";
    }
    outfile << endl;
    outfile.close();
    return 0;
}