#include <arpa/inet.h>
#include <stdbool.h>
#include <stdio.h>

#include "pq.h"

static pq_head t1_head = PQ_HEAD_INIT;
static pq_head t2_head = PQ_HEAD_INIT;

void *t1(void *arg)
{
	(void)arg; /* supress warnigs */
	while (pq_continue(&t1_head)) {
		pqn *data = pq_get_tail(&t1_head, 0);
		assert(data);
		sprintf((char *)data->data, "PING");
		printf("%s => %s\n", __func__, (char *)data->data);
		pq_put_head(&t2_head, data);
	}
	printf("%s terminated\n", __func__);
	return NULL;
}

void *t2(void *arg)
{
	(void)arg; /* supress warnings */
	while (pq_continue(&t2_head)) {
		pqn *data = pq_get_tail(&t2_head, 0);
		assert(data);
		sprintf((char *)data->data, "PONG");
		printf("%s => %s\n", __func__, (char *)data->data);
		pq_put_head(&t1_head, data);
	}
	printf("%s terminated\n", __func__);
	return NULL;
}

int main(void)
{
	pthread_t t1id, t2id;
	char msg[] = "PING";

	pthread_create(&t1id, NULL, t1, NULL);
	pthread_create(&t2id, NULL, t2, NULL);

	pq_put_head(&t1_head, pqn_new(msg));

	sleep(3);

	pq_terminate(&t1_head);
	pq_terminate(&t2_head);
	return 0;
}
