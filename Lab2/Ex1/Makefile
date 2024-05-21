bin:calculateAverage.o
	gcc calculateAverage.o -o bin
calculateAverage.o:calculateAverage.c	
	gcc -c calculateAverage.c -pthread -o calculateAverage.o

clean: 
	rm -rf *.o bin
.phony: clean	