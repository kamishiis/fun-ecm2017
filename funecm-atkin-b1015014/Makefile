# Makefile

PROGRAM = funecm
OBJS = atkin.o point.o double_add.o normal_add.o ecm.o BSGS2.o scalar.o main.o
CC = gcc
LIBRARY = -lgmp -lrt

ifeq ($(ARCHITECTURE),Xeonphi) # for Xeonphi
	CFLAGS = -mmic -openmp -O2
	LIBDIR = -L/usr/local/lib
else # for Xeon
	CFLAGS = -fopenmp -O2
	LIBDIR = -L/home/b1015014/gmp-6.1.2/.libs -g #-L/home/project8/gmp/lib
endif

$(PROGRAM): $(OBJS)
	$(CC) $(CFLAGS) -o $(PROGRAM) $^ $(LIBRARY) $(LIBDIR)

main.o: main.c
	$(CC) $(CFLAGS) -c $<
point.o: point.c
	$(CC) $(CFLAGS) -c $<
double_add.o: double_add.c
	$(CC) $(CFLAGS) -c $<
normal_add.o: normal_add.c
	$(CC) $(CFLAGS) -c $<
ecm.o: ecm.c
	$(CC) $(CFLAGS) -c $<
BSGS2.o: BSGS2.c
	$(CC) $(CFLAGS) -c $<
scalar.o: scalar.c
	$(CC) $(CFLAGS) -c $<
atkin.o: atkin.c
	$(CC) $(CFLAGS) -c $<

all: clean $(PROGRAM)

clean:
	-rm -f $(PROGRAM) $(OBJS)
