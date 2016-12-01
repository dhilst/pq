#include <arpa/inet.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

#include "pq.h"

static pq_head t1_head = PQ_HEAD_INIT;
static pq_head t2_head = PQ_HEAD_INIT;

void *t1(void *arg)
{
	(void)arg; /* supress warnigs */
	while (!pq_isterminated(&t1_head)) {
		pqn *data = pq_get_tail(&t1_head, 0);
		assert(data);
		printf("%s => %s\n", __func__, (char *)data->data);
		pq_put_head(&t2_head, data);
	}
	printf("%s terminated\n", __func__);
	return NULL;
}

void *t2(void *arg)
{
	(void)arg; /* supress warnings */
	while (!pq_isterminated(&t2_head)) {
		pqn *data = pq_get_tail(&t2_head, 0);
		assert(data);
		printf("%s => %s\n", __func__, (char *)data->data);
		pq_put_head(&t1_head, data);
	}
	printf("%s terminated\n", __func__);
	return NULL;
}
#define ARRAY_SIZE(a) (int)(sizeof(a)/sizeof(*(a)))

bool cb(pqn *n, void *arg)
{
	(void)arg; /* supress warning */
	printf("cb: %s\n", (char *)pqn_getdata(n));
	return true;
}

int main(void)
{
	pthread_t t1id, t2id;
	char *msg[] = { "Hello", "my", "dear", "friend", "How", "are", "you", "?" };


	int i;
	for (i = 0; i < ARRAY_SIZE(msg); i++)
		pq_put_head(&t1_head, pqn_new(msg[i]));

	pq_foreach(&t1_head, cb, NULL);
	sleep(5);

	pthread_create(&t1id, NULL, t1, NULL);
	pthread_create(&t2id, NULL, t2, NULL);

	while (1)
		sleep(3);

	pq_terminate(&t1_head);
	pq_terminate(&t2_head);
	return 0;
}
