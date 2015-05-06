#include <iostream>

using namespace std;
int n, m, a[30][30];
bool use[30];

int find_path(int u, int v, int f)
{
    if (u == v)
        return f;
    use[u] = 1;
    for (int i = 0; i < n; ++i) {
        if (!use[i] && a[u][i] != 0) {
            int df = find_path(i, v, min(f, a[u][i]));
            if (df > 0) {
                a[u][i] -= df;
                a[i][u] += df;
                return df;
            }
        }
    }
    return 0;
}

int max_flow(int s, int t)
{
    for (int flow = 0; ; ) {
        int df = find_path(s, t, 1000000);
        if (df == 0)
            return flow;
        flow += df;
        for (int i = 0; i < n; ++i)
            use[i] = 0;
    }
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
        a[u][v] = w;
    }
    int tmp = max_flow(0, n - 1);
    cout << tmp << endl;
    return 0;
}
