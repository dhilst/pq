all: test.c pq.h
	$(CC) -Wall -Wextra test.c -o pqtest -lpthread

clean:
	rm pqtest
