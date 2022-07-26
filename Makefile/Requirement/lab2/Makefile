CC=gcc
CFLAGS=-I.
DEPS = lab2.h
OBJ = lab2.o lab2_func.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

lab2: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f lab2 $(OBJ)
