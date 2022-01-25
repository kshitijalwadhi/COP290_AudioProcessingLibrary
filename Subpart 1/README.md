# Audio Processing Library (Subpart-1)

## Compliation and generating executable

First we need to compile the c++ file and generate an executable. For that, run the following command in your terminal:

```console
make
```

## Functions implemented

In this section, we discuss the functions implemented in the library and how to use them.

* ## Fully connected layer
  
  `./main.out fullyconnected <input_file> <weight_file> <bias_file> <output_file> `

* ## Activation layer

    `./main.out activation <function> <input_file> <output_file>`

    Here in `<function>` you need to specify the activation function. The available activation functions are:
    * `sigmoid`
    * `tanh`
  
* ## Pooling 

    `./main.out pooling <type> <input_file> <stride> <output_file>`

    Here in `<type>` you need to specify the pooling type. The available pooling types are:
    * `max`
    * `average`

    Also, in `<stride>` you need to specify the stride of the pooling.
* ## Probability

    `./main probability <function> <input_file> <output_file>`

    Here in `<function>` you need to specify the probability function. The available probability functions are:
    * `softmax`
    * `sigmoid`