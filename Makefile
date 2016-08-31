all: test.c pq.h
	$(CC) -Wall -Wextra -g test.c -o pqtest -lpthread

clean:
	rm pqtest
