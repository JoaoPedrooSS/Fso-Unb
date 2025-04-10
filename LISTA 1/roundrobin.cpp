#include <iostream>
#include <queue>
using namespace std;

int main()
{
    int q, n;
    int c, valor;
    int time_now = 0;
    queue<pair<int, int>> processes;

    cin >> n >> q;

    for (int i = 0; i < n; i++)
    {
        cin >> c >> valor;
        processes.push({c, valor * 1000});
    }

    while (!processes.empty())
    {
        pair<int, int> process = processes.front();
        processes.pop();

        int time = process.second;
        int id = process.first;

        if (time <= q)
        {
            time_now += time;
            cout << id << " (" << time_now << ")" << endl;
        }
        else
        {
            time_now += q;
            processes.push({id, time - q});
        }
    }

    return 0;
}
