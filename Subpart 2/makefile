CC = g++

BLAS_ROOT = /home/kshitij/libs/OpenBLAS
MKL_INCLUDE_ROOT = /usr/include/mkl
MKL_LIB_ROOT = /usr/lib/x86_64-linux-gnu/mkl

PTHREAD_FLAGS = -pthread
BLAS_FLAGS = -I $(BLAS_ROOT)/include -L $(BLAS_ROOT)/lib -lopenblas -lgfortran -lpthread
MKL_FLAGS = -lpthread -I $(MKL_INCLUDE_ROOT) -L $(MKL_LIB_ROOT) -fopenmp -lmkl_intel_lp64 -lmkl_core -lmkl_gnu_thread -lm -ldl

DEPS = activationFns.h utils.h matrices_mkl.h matrices_pthread.h matrices_openblas.h matrices.h subsampling.h
OBJ_MAIN = main.o activationFns.o utils.o matrices_mkl.o matrices_pthread.o matrices_openblas.o matrices.o subsampling.o
OBJ_PERFORMANCE = test.o matrices.o matrices_pthread.o matrices_openblas.o matrices_mkl.o utils.o

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(OBJ_MAIN)
	$(CC) -o $@ $^ $(BLAS_FLAGS) $(MKL_FLAGS) $(PTHREAD_FLAGS)

performance: $(OBJ_PERFORMANCE)
	$(CC) -o $@ $^ $(PTHREAD_FLAGS) $(BLAS_FLAGS) $(MKL_FLAGS)

clean:
	rm -f *.o 