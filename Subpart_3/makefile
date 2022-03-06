CC = g++ -std=c++11

BLAS_ROOT = $(MKL_BLAS_PATH%/)

BLAS_FLAGS = -I $(BLAS_ROOT)/include -L $(BLAS_ROOT)/lib -lopenblas -lgfortran -lpthread
PTHREAD_FLAGS = -pthread

DEPS = activationFns.h utils.h matrices_pthread.h matrices_openblas.h matrices.h subsampling.h dnn.h audio.h
OBJ_MAIN = activationFns.o utils.o matrices_pthread.o matrices_openblas.o matrices.o subsampling.o dnn.o audio.o

%.o: %.cpp $(DEPS)
	$(CC) -c -fpic -o $@ $< $(CFLAGS)

all: $(OBJ_MAIN) 
	$(CC) -shared -o libaudio.so $^ $(BLAS_FLAGS) $(PTHREAD_FLAGS)
	$(CC) main.cpp -o yourcode.out -laudio -L .

clean:
	rm -f *.o 