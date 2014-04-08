CC=gcc
FLAGS=-g
FILES=test.c malloc.c 
OBJ=test.o malloc.o 
OUT=a.out

all: build

build: $(OBJ)
	$(CC) $(FLAGS) $(OBJ)

test.o: test.c malloc.h
	$(CC) $(FLAGS) -c  test.c

malloc.o: malloc.c malloc.h
	$(CC) $(FLAGS) -c  malloc.c

clean:
	rm -rf $(OBJ) $(OUT)

rebuild: clean build
