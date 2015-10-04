OBJS = tester.o drive.o fs.o
CFLAGS=-std=c99 -g
CC = gcc

all:  ${OBJS}
	${CC} ${OBJS} -o project2

clean:
	rm *.o project2
