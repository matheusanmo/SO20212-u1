CC = clang
CFLAGS = -Wall -Wextra -Werror -pedantic -g

main.out : main.o matrix.o timetools.o auxiliar.o
	$(CC) -o $@ $^

main.o : main.c
	$(CC) $(CFLAGS) -o $@ -c $<

matrix.o : matrix.c
	$(CC) $(CFLAGS) -o $@ -c $<

auxiliar.o : auxiliar.c
	$(CC) $(CFLAGS) -o $@ -c $<

timetools.o : timetools.c
	$(CC) $(CFLAGS) -o $@ -c $<

