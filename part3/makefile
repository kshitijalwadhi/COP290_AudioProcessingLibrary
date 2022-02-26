CC = g++

BLAS_ROOT = /home/kshitij/libs/OpenBLAS
MKL_INCLUDE_ROOT = /usr/include/mkl
MKL_LIB_ROOT = /usr/lib/x86_64-linux-gnu/mkl

PTHREAD_FLAGS = -pthread
BLAS_FLAGS = -I $(BLAS_ROOT)/include -L $(BLAS_ROOT)/lib -lopenblas -lgfortran -lpthread
MKL_FLAGS = -lpthread -I $(MKL_INCLUDE_ROOT) -L $(MKL_LIB_ROOT) -fopenmp -lmkl_intel_lp64 -lmkl_core -lmkl_gnu_thread -lm -ldl

DEPS = activationFns.h utils.h matrices_mkl.h matrices_pthread.h matrices_openblas.h matrices.h subsampling.h dnn.h audio.h
OBJ_MAIN = main.o activationFns.o utils.o matrices_mkl.o matrices_pthread.o matrices_openblas.o matrices.o subsampling.o dnn.o audio.o

%.o: %.cpp $(DEPS)
	$(CC) -c -fpic -o $@ $< $(CFLAGS)

shared: $(OBJ_MAIN)
	$(CC) -shared -o lib/libaudio.so $^ $(BLAS_FLAGS) $(MKL_FLAGS) $(PTHREAD_FLAGS)

# all: $(OBJ_MAIN)
# 	$(CC) -o yourcode.out $^ $(BLAS_FLAGS) $(MKL_FLAGS) $(PTHREAD_FLAGS) -laudio -L lib
all: 
	$(CC) main.cpp -o yourcode.out -laudio -L lib

clean:
	rm -f *.o 