#include <iostream>

using namespace std;

int a[30][30], minc = (1 << 30) - 1, n, m;
bool use[30];

void dfs(int x, int d, int c) //point, deep, cost
{
    use[x] = 1;
    if (d == n - 1 && a[x][0] != 0)
        minc = min(minc, c + a[x][0]);
    for (int i = 0; i < m; ++i)
        if (a[x][i] != 0 && !use[i])
            dfs(i, d + 1, c + a[x][i]);
    use[x] = 0;
}

int main()
{
    int u, v, w;
    cout << "Введите количество вершин\n";
    cin >> n;
    cout << "Введите количество рёбер\n";
    cin >> m;
    for (int i = 0; i < m; ++i) {
        cin >> u >> v >> w;
        a[u][v] = a[v][u] = w;
    }
    dfs(0, 0, 0);
    cout << minc << endl;
    return 0;
}

