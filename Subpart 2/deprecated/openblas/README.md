## Instructions for installing openBLAS

1) first make sure you have essential tools, like git, gfortran

you can install the gfotran by this

     apt build-essential gfortran

2) then clone the OpenBLAS repo

    git clone https://github.com/xianyi/OpenBLAS

3) cd OpenBLAS

4) inside OpenBLAS dirrectory

   make FC=gfortran

5) then install the OpenBLAS library

     make PREFIX=path/to/lib install

6) sudo apt-get install libopenblas-dev