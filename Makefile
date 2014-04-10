CC=gcc
FLAGS=-g -w
FILES=malloc.c test.c 
OBJ=malloc.o test.o 
OUT=a.out

all: build

build: $(OBJ)
	$(CC) $(FLAGS) $(OBJ)

malloc.o: malloc.c
	$(CC) $(FLAGS) -c  malloc.c

test.o: test.c
	$(CC) $(FLAGS) -c  test.c

clean:
	rm -rf $(OBJ) $(OUT)

rebuild: clean build
