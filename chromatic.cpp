#include <iostream>
#include <algorithm>

using namespace std;

typedef struct { int x, y; } vertex; // vertex from x to y
int n, m, color[10], ans;
vertex g[10];

int check()
{
    int colortmp[10];
    for (int i = 0; i < n; ++i)
        colortmp[i] = color[i];
    for (int i = 0; i < m; ++i)
        if (colortmp[g[i].x] == colortmp[g[i].y])
            return n;
    sort(colortmp, colortmp + n);
    int res = 1;
    for (int i = 1; i < n; ++i)
        if (colortmp[i] != colortmp[i - 1])
            ++res;
    return res;
}

void hromatic(int x) // x == position
{
    if (x == n)
    {
        ans = min(ans, check());
        return;
    }
    for (int i = 1; i <= n; ++i)
    {
        color[x] = i;
        hromatic(x + 1);
    }
}

int main()
{
    cout << "Введите количество вершин\n";
    cin >> n;
    ans = n;
    cout << "Введите количество рёбер\n";
    cin >> m;
    for (int i = 0; i < m; ++i)
    {
        cin >> g[i].x >> g[i].y;
    }
    hromatic(0);
    cout << ans << endl;
    return 0;
}

