#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int son = 0;
int signal_count = 0;

void create(int id);

int main()
{
    signal(SIGUSR1, create);
    signal(SIGUSR2, create);

    while (signal_count < 3)
    {
        pause();
    }
    exit(0);
}

void create(int id)
{
    signal_count++;

    if (signal_count == 1)
    {
        son = id;
        int n = fork();
        if (n == 0)
        {
            exit(0);
        }
    }
    else if (signal_count == 2 && son != 0)
    {
        wait(NULL);
    }
    else if (signal_count == 3)
    {
        exit(0);
    }
}
