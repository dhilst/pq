# Descripion

This is a simple, very very simple, synchronous queue for exchaning messages
between pthreads. The source is distribuited as a header so using is just a
matter of including it. Almost every function is declared as inline and
there are lots of possible improvements. This has been done in one day,
so don't take it too serious. If you need something "better" I would
recommend: [Thread Safe FIFO bounded queue](https://apr.apache.org/docs/apr-util/0.9/group__APR__Util__FIFO.html)

# Program Usage

This is a simple linked list with locking included. The list elements are
called "nodes". `pq` stands for Pthread Queue and pqn stands for Pthread
Queue Node.

First you allocate queue heads, this will hold the lock, conditional variable
and the first node pointer.
```c
static pq_head myhead = PQ_HEAD_INIT;
```

Consumer thread should grab nodes with `pq_get_tail`. This fucntion blocks
until a new node is avaible, or till some timeout happens. The producer uses
`pq_put_head` to post nodes to consumer.

To create nodes one use `pq_new(void *data)` where data is an opaque pointer to
user's data, a new pqn will be allocated an returned. The user's data can be
retrived at `pqn->data` pointer. When node is not needed anymore it *must* be
freed with `free()`.

Take a look at test.c for more information.

Thats it!
