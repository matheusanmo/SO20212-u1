CC = clang
CFLAGS = -Wall -Wextra -pedantic -g

main.out : main.o matrix.o timetools.o auxiliar.o sequential.o
	$(CC) -o $@ $^

main.o : main.c
	$(CC) $(CFLAGS) -o $@ -c $<

matrix.o : matrix.c
	$(CC) $(CFLAGS) -o $@ -c $<

auxiliar.o : auxiliar.c
	$(CC) $(CFLAGS) -o $@ -c $<

timetools.o : timetools.c
	$(CC) $(CFLAGS) -o $@ -c $<

sequential.o : sequential.c
	$(CC) $(CFLAGS) -o $@ -c $<
