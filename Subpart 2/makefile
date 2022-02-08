PTHREAD_FLAGS = -pthread
BLAS_FLAGS = -I /home/kshitij/libs/OpenBLAS/include -L /home/kshitij/libs/OpenBLAS/lib -lopenblas -lgfortran -lpthread
MKL_FLAGS = -lpthread -I /usr/include/mkl -L /usr/lib/x86_64-linux-gnu/mkl -fopenmp -lmkl_intel_lp64 -lmkl_core -lmkl_gnu_thread -lm -ldl

all: test.cpp
	g++ -o test test.cpp $(PTHREAD_FLAGS) $(BLAS_FLAGS) $(MKL_FLAGS)