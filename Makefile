CC = clang
CFLAGS = -Wall -Wextra -Werror -pedantic

main.out : main.o matrix.o
	$(CC) -o $@ $^

main.o : main.c
	$(CC) $(CFLAGS) -o $@ -c $<

matrix.o : matrix.c
	$(CC) $(CFLAGS) -o $@ -c $<

