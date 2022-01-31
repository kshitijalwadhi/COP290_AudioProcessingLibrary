# Audio Processing Library (Subpart-1)

## Compliation and generating executable

First we need to compile the c++ file and generate an executable. For that, run the following command in your terminal:

```console
make
```

## Functions implemented

In this section, we discuss the functions implemented in the library and how to use them.

* ## Fully connected layer
  
    This function performs the forward propagation step of a fully connected layer. It takes as input the input matrix, the weights matrix and the bias vector. It returns the output matrix.

  `./main.out fullyconnected <input_file> <weight_file> <bias_file> <output_file> `

* ## Activation layer

    This function performs the activation function on the input matrix. It takes as input the input matrix and the activation function. It returns the output matrix.

    `./main.out activation <function> <input_file> <output_file>`

    Here in `<function>` you need to specify the activation function. The available activation functions are:
    * `sigmoid`
    * `tanh`
  
* ## Pooling 

    This function performs the pooling operation on the input matrix. This is used for subsampling. It takes as input the input matrix, the pooling type and the stride length. It returns the output matrix.

    `./main.out pooling <type> <input_file> <stride> <output_file>`

    Here in `<type>` you need to specify the pooling type. The available pooling types are:
    * `max`
    * `average`

    Also, in `<stride>` you need to specify the stride of the pooling.
* ## Probability

    This function is used for implementing the activation function of the final layer of the neural network (the probability functions for binary/multi-class classification). It takes as input the input matrix and the activation function. It returns the output matrix.

    `./main probability <function> <input_file> <output_file>`

    Here in `<function>` you need to specify the probability function. The available probability functions are:
    * `softmax`
    * `sigmoid`