
CC = gcc
CFLAGS = -Wall -std=c99 -pedantic

SRC = main.c q1_functions.c
OBJ = $(SRC:.c=.o)
EXEC = car_rental

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJ) $(EXEC)
