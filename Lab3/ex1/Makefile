TARGET=bin

$(TARGET):seqlock.o
	gcc seqlock.o -pthread -o bin

seqlock.o:seqlock.h seqlock.c
	gcc -c seqlock.c -o seqlock.o

clean:
	rm --force seqlock.o bin