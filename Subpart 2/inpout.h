#ifndef INPUTOUTPUT_H
#define INPUTOUTPUT_H

#include <vector>

#define Mat std::vector<std::vector<float> >
#define Vec std::vector<float>

bool is_file_exist(std::string filename);
Mat read_matrix(std::string filename);
Vec read_vector(std::string filename);
void print_vector(Vec V);
void print_matrix(Mat M);
void write_matrix(Mat M, std::string filename);
void write_vector(Vec V, std::string filename);


#endif