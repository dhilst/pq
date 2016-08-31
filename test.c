#include <arpa/inet.h>
#include <stdbool.h>
#include <stdio.h>

#include "pq.h"

static pq_head t1_head = PQ_HEAD_INIT;
static pq_head t2_head = PQ_HEAD_INIT;

void *t1(void *arg)
{
	(void)arg; /* supress warnigs */
	while (true) {
		pqn *data = pq_get_tail(&t1_head, 0);
		printf("%s => %s\n", __func__, (char *)data->data);
		pq_put_head(&t2_head, data);
	}
	return NULL;
}

void *t2(void *arg)
{
	(void)arg; /* supress warnings */
	while (true) {
		pqn *data = pq_get_tail(&t2_head, 0);
		printf("%s => %s\n", __func__, (char *)data->data);
		pq_put_head(&t1_head, data);
	}
	return NULL;
}

int main(void)
{
	pthread_t t1id, t2id;
	pqn *ping = pqn_new("PING");
	pqn *pong = pqn_new("PONG");
	pq_put_head(&t1_head, ping);
	pq_put_head(&t2_head, pong);
	pthread_create(&t1id, NULL, t1, NULL);
	pthread_create(&t2id, NULL, t2, NULL);

	while (true)
		sleep(~0l);
	return 0;
}
