CC = g++

BLAS_ROOT = $(MKL_BLAS_PATH)

PTHREAD_FLAGS = -pthread
BLAS_FLAGS = -I $(BLAS_ROOT)/include -L $(BLAS_ROOT)/lib -lopenblas -lgfortran -lpthread

DEPS = activationFns.h utils.h matrices_pthread.h matrices_openblas.h matrices.h subsampling.h dnn.h audio.h
OBJ_MAIN = main.o activationFns.o utils.o matrices_pthread.o matrices_openblas.o matrices.o subsampling.o dnn.o audio.o

%.o: %.cpp $(DEPS)
	$(CC) -c -fpic -o $@ $< $(CFLAGS)

all: $(OBJ_MAIN) 
	if [ ! -d lib ]; then \
		mkdir lib; \
	fi
	$(CC) -shared -o lib/libaudio.so $^ $(BLAS_FLAGS) $(PTHREAD_FLAGS)
	$(CC) main.cpp -o yourcode.out -laudio -L lib

clean:
	rm -f *.o 