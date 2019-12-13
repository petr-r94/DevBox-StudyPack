# comment
CC = gcc
CFLAGS = -c -O2
LFLAGS = -lm
OBJS = file.o

hello: $(OBJS)
	$(CC) -o hello $(OBJS) $(LFLAGS)
	
file.o: file.c
	$(CC) $(CFLAGS) file.c
clean:
	rm *.o hello
