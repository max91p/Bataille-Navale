CFLAGS = -Wall -Wextra -std=c99 -pedantic -g
CC = gcc $(CFLAGS)

all: bataille_navale clean

%.o: %.c
	$(CC) -c $< -o $@

bataille_navale: main.o fonctions.o
	$(CC) $^ -o $@ -lm
	
clean:
	@rm -f *.o 
