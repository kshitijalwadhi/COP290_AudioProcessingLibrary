# COP290 Task 1 (Subpart 3)

In this subpart, we implement an API to perform the task of audio classification. We implement a DNN architecture comprising of a couple of fully connected layers.

This library uses the weights given in the `dnn_weights.h` file. 

## Installation Instruction for openBLAS:

1) Ensure you have essential tools, like git, gfortran. You can install the gfotran as follows:

    ```apt build-essential gfortran```

2) Clone the OpenBLAS repo

    ```git clone https://github.com/xianyi/OpenBLAS```

    ```cd OpenBLAS```

3) Inside OpenBLAS directory, run:

   ```make FC=gfortran```

4) Install the OpenBLAS library:

    ```make PREFIX=path/to/lib install```

5) Finally, run:
   
   ```sudo apt-get install libopenblas-dev```

## Compliation and generating executable

We make use of a makefile to ease in the process of generation of executable. The following terminal commands are used for getting the final executable file. 

```console
export MKL_BLAS_PATH=/path/to/openblas
export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH
make all
```

Here is an explanation of what these commands are doing:

```console
export MKL_BLAS_PATH=/path/to/openblas
```
The above command exports an environment variable to be used for providing the path to library to the makefile. 

```console
export LD_LIBRARY_PATH=./lib:$LD_LIBRARY_PATH
```

The above command exports an environment variable specifying the path to the shared library. This will be used by the final executable at the time of running. 

```console
make all
```

The above command runs the all directive in makefile which executes a set of commands which do the following: 

1) creates the `lib` folder if it doesn't exist in the directory.
2) creates the shared library.
3) creates the `yourcode.out` executable. 

```console
make clean
```

The above command is used for removing the *.o files from the directory. This is an optional command.

## Usage of executable file

```console
/yourcode.out <input_file> <output_file>
```

Here: 

`input_file` is the path to the input .txt file which contains the features extracted from the audio file. This file will contain 250 space separated floats that represent the audio file.

`output_file` is the path where the results will be dumped. For every input, the following will be the output generated in the file:

`<input_file> label1 label2 label3 prob1 prob2 prob3`

where `label_i` is the label predicted at $i^{th}$ position and `prob_i` is the probability of this label. 

## Report

For more information about the functions implemented and the performance report, please refer to this [report](COP290_Task_1_Report.pdf)