lab1: lab1.o lab1_func.o
	gcc -o lab1 lab1.o lab1_func.o

lab1.o: lab1.c lab1.h
	gcc -c lab1.c

lab1_func.o: lab1_func.c lab1.h
	gcc -c lab1_func.c

clean:
	rm -f lab1 lab1.o lab1_func.o
