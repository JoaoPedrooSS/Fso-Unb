#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int work(int id);

pthread_mutex_t mut;
int count;

struct thread_arg {
    int vezes;
};
void *thread_func(void *arg)
{
    struct thread_arg *args = (struct thread_arg *)arg;

    for (int i = 0; i < args->vezes; i++)
    {
        pthread_mutex_lock(&mut);
        int id = count;
        count++;
        pthread_mutex_unlock(&mut);
        work(id);
    }

    return NULL;
}
