OLD  := MMult0
NEW  := openmp
1    := native
2    := openblas
3    := pthread
4    := openmp
#
# sample makefile
#

CC         := gcc
LINKER     := $(CC)
CFLAGS     := -Wall -g  -msse3 -O1
LDFLAGS    := -lm
BLAS_LIB   := -lopenblas
PTHREAD    := -lpthread
OPENMP     := -fopenmp

UTIL       := copy_matrix.o \
              compare_matrices.o \
              random_matrix.o \
              dclock.o \
              REF_MMult.o \
              print_matrix.o

TEST_OBJS  := test_MMult.o $(NEW).o
TEST_OBJS1 := test_MMult.o $(1).o
TEST_OBJS2 := test_MMult.o $(2).o
TEST_OBJS3 := test_MMult.o $(3).o
TEST_OBJS4 := test_MMult.o $(4).o

%.o: %.c
	$(CC) $(CFLAGS) $(OPENMP) -c $< -o $@

all:
	make clean;
	make test_MMult1.x
	make test_MMult2.x
	make test_MMult3.x
	make test_MMult4.x

test_MMult1.x: $(TEST_OBJS1) $(UTIL) parameters.h
	$(LINKER) $(TEST_OBJS1) $(UTIL) $(LDFLAGS) \
       $(OPENMP) $(BLAS_LIB) $(PTHREAD) -o $@

test_MMult2.x: $(TEST_OBJS2) $(UTIL) parameters.h
	$(LINKER) $(TEST_OBJS2) $(UTIL) $(LDFLAGS) \
       $(OPENMP) $(BLAS_LIB) $(PTHREAD) -o $@


test_MMult3.x: $(TEST_OBJS3) $(UTIL) parameters.h
	$(LINKER) $(TEST_OBJS3) $(UTIL) $(LDFLAGS) \
       $(OPENMP) $(BLAS_LIB) $(PTHREAD) -o $@


test_MMult4.x: $(TEST_OBJS4) $(UTIL) parameters.h
	$(LINKER) $(TEST_OBJS4) $(UTIL) $(LDFLAGS) \
       $(OPENMP) $(BLAS_LIB) $(PTHREAD) -o $@




export OMP_NUM_THREADS=2
export GOTO_NUM_THREADS=1

run:
	make all
	echo "version = '$(1)';" > output_$(1).m
	echo "version = '$(2)';" > output_$(2).m
	echo "version = '$(3)';" > output_$(3).m
	echo "version = '$(4)';" > output_$(4).m
	echo $$OMP_NUM_THREADS
	./test_MMult1.x >> output_$(1).m
	./test_MMult2.x >> output_$(2).m
	./test_MMult3.x >> output_$(3).m
	./test_MMult4.x >> output_$(4).m
	cp output_$(1).m output_1.m
	cp output_$(2).m output_2.m
	cp output_$(3).m output_3.m
	cp output_$(4).m output_4.m

clean:
	rm -f *.o *~ core *.x

cleanall:
	rm -f *.o *~ core *.x output*.m *.eps *.png *.jpg
