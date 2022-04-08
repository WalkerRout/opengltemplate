CC     = gcc
OBJS   = src/*.c src/include/*.c
OBJ    = bin/glt
CFLAGS = -Wall -pedantic
LIBS   = -lglad -ldl -lglfw -lGL
# -ldl throws errors if it isnt the *last* library linked

all: build run

build:
	$(CC) $(OBJS) $(CFLAGS) $(LIBS) -o $(OBJ)

run:
	./$(OBJ)

clean:
	rm -rf bin/*
	echo "Cleaned bin!"

