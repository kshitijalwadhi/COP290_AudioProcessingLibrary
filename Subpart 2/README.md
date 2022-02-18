# COP290 Task 1 (Subpart 2)

In this subpart, we experiment with different implementations of matrix multiplication. 

## Installation of Libaries

### Instructions for installing openBLAS on Ubuntu

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

### Instructions for installing MKL on Ubuntu
1. In your terminal, run:
    
   ```sudo apt-get install intel-mkl```

### Instructions for installing gnuplot on Ubuntu
1. In your terminal, run:

    ```sudo apt-get install gnuplot```
2. Start ```gnuplot``` in your terminal by simply typing
   
   ```gnuplot```


## Compliation and generating executable

First we need to execute the makefile for getting the executables.

In the makefile we have the following commands:

* The following command can be used for generating the executable through which all the functions implemented in subpart 1 can be accessed. The interface is with the main.cpp file here. It generates the `yourcode.out` file.

```console
make all
```

* The following command generates an executable file called `performance`. This is used for getting the performance accross various implementations.

```console
make performance
```

* The following command generates an executable file called `pthread_performance`. This is used for getting the performance variation with the number of threads in our pthreads implementation.

```console
make pthread_performance
```

* The following command deletes the .o files from the directory.

```console
make clean
```

## Function definitions (overlaps with Subpart 1)

* ## Fully connected layer
  
    This function performs the forward propagation step of a fully connected layer. It takes as input the input matrix, the weights matrix and the bias vector. It returns the output matrix.

  `./yourcode.out fullyconnected <input_file> <weight_file> <bias_file> <output_file> <matmul_implementation>`

  Here in `<matmul_implementation>` you need to specify the approach to be used for matrix multiplication. The available options are:
  * `normal`
  * `pthread`
  * `openblas`
  * `mkl`

* ## Activation layer

    This function performs the activation function on the input matrix. It takes as input the input matrix and the activation function. It returns the output matrix.

    `./yourcode.out activation <function> <input_file> <output_file>`

    Here in `<function>` you need to specify the activation function. The available activation functions are:
    * `sigmoid`
    * `tanh`
  
* ## Pooling 

    This function performs the pooling operation on the input matrix. This is used for subsampling. It takes as input the input matrix, the pooling type and the stride length. It returns the output matrix.

    `./yourcode.out pooling <type> <input_file> <stride> <output_file>`

    Here in `<type>` you need to specify the pooling type. The available pooling types are:
    * `max`
    * `average`

    Also, in `<stride>` you need to specify the stride of the pooling.
* ## Probability

    This function is used for implementing the activation function of the final layer of the neural network (the probability functions for binary/multi-class classification). It takes as input the input matrix and the activation function. It returns the output matrix.

    `./yourcode.out probability <function> <input_file> <output_file>`

    Here in `<function>` you need to specify the probability function. The available probability functions are:
    * `softmax`
    * `sigmoid`


## Performance Evaluation

For evaluating the performance, we make use of the `performance` and `pthread_performance` executables generated. By running these executables, we get the time taken by our implementations dumped into `.dat` files in the directory. These `.dat` files are further used by the graphing scripts to make the required plots. 

To obtain the `.eps` and `.png` plots which compare the various implementations, type `gnuplot` in your terminal to enter the `gnuplot` environment. There are two scripts, one for each of the following plots:
- Performance on varying number of threads. To obtain this plot, run the following command:
  
  ```load "pthread_script"```
- Performance across various implementations (naive, pthread, openblas, mkl). To obtain this plot, run the following command:
  
    ```load "script"```


More about the evaluation details and the graphs are given in the [report](COP290_Task1_Performance.pdf).
