#include <vector>
#include <iostream>
#include <unistd.h>
#include <sys/time.h>
#include <cstring>
#include <iomanip>
#include <errno.h>
#include <sys/wait.h>

using namespace std;

double calc_time(const timeval &begin, const timeval &end);

int main()
{
    char p[255], a[255];
    struct timeval totalTimeBegin;
    struct timeval totalTimeEnd;
    gettimeofday(&totalTimeBegin, nullptr);

    while (cin >> p >> a)
    {
        struct timeval begin;
        struct timeval end;
        gettimeofday(&begin, nullptr);

        pid_t p_id;
        p_id = fork();

        if (p_id == 0)
        {
            vector<char *> args = {p, a, nullptr};
            execv(p, args.data());
            cout << "> Erro: " << strerror(errno) << endl
                 << flush;
            cout.flush();
            _exit(errno);
        }
        else
        {
            int stts;
            waitpid(p_id, &stts, WUNTRACED);
            gettimeofday(&end, nullptr);
            double son_son = calc_time(begin, end);

            cout << "> Demorou " << fixed << setprecision(1) << son_son
                 << " segundos, retornou " << WEXITSTATUS(stts) << endl;
            cout.flush();
        }
    }

    gettimeofday(&totalTimeEnd, nullptr);
    double total = calc_time(totalTimeBegin, totalTimeEnd);

    cout << ">> O tempo total foi de " << fixed << setprecision(1) << total << " segundos" << endl;
    cout.flush();
    return 0;
}

double calc_time(const timeval &begin, const timeval &end)
{
    return (end.tv_sec - begin.tv_sec) + (end.tv_usec - begin.tv_usec) / 1e6;
}
