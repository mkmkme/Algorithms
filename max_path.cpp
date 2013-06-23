#include <iostream>

using namespace std;
int a[100][100], maxp = 0, n, m;
bool use[100][100];

void watch_point(int point, int deep) // aka dfs
{
    if (deep > maxp) maxp = deep;
    for (int i = 0; i < n; ++i)
        if (a[point][i] == 1 && !use[point][i])
        {
            use[point][i] = use[i][point] = 1;
            watch_point(i, deep + 1);
            use[point][i] = use[i][point] = 0;
        }
}

int main()
{
    int u, v;
    cout << "Введите количество вершин\n";
    cin >> n;
    cout << "Введите количество рёбер\n";
    cin >> m;
    for (int i = 0; i < m; ++i)
    {
        cin >> u >> v;
        a[u][v] = a[v][u] = 1;
    }
    for (int i = 0; i < n; ++i)
        watch_point(i, 0);
    cout << maxp << '\n';
    return 0;
}
