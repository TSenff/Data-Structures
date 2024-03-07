CC=gcc
CFLAG=
LFLAG=
NAME= test

all:$(NAME)

$(NAME): testing.c generic_stack.h generic_stack.c
	$(CC) testing.c generic_stack.h generic_stack.c -o $(NAME)

clean:
	rm -f *.o

purge: clean
	rm -f $(NAME)