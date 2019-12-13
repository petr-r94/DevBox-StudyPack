# comment
CC = gcc
CFLAGS= -Wall -fopenmp

omp: serial
	$(CC) $(CFLAGS) mSortOmp.c -o sortOmp

serial:
	$(CC) $(CFLAGS) mSortSerial.c -o sortSerial
	
clean:
	rm *.o sortSerial sortOmp
