
all: stats.o
	gcc -o stats stats.o

stats.o: stats.c stats.h
	gcc -c -g stats.c

run: all
	./stats

clean:
	rm *~
	rm *.o

