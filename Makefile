CC = clang
CFLAGS = -Wall -Wextra -pedantic -g -pthread
LDFLAGS = -pthread

main.out : main.o matrix.o timetools.o auxiliar.o sequential.o threaded.o
	$(CC) $(LDFLAGS) -o $@ $^

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

threaded.o : threaded.c
	$(CC) $(CFLAGS) -o $@ -c $<

