## Instructions for installing openBLAS on Ubuntu

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

## Instructions for installing MKL on Ubuntu
1. In your terminal, run:
    
   ```sudo apt-get install intel-mkl```
   
   TO-DO

## Instructions for installing gnuplot on Ubuntu
1. In your terminal, run:

    ```sudo apt-get install gnuplot```
2. Start ```gnuplot``` in your terminal by simply typing
   
   ```gnuplot```
