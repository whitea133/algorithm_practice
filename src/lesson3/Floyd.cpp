// Floyd算法求最短路
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 210, INF = 1e9;

int n, m, Q; // Q 是询问个数, 多次循环从 x 到 y 到最短距离
int d[N][N];

void floyd()
{
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
}

int main()
{
    scanf("%d%d%d", &n, &m, &Q);

    // 初始化 d[N][N]
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (i == j) d[i][j] = 0;
            else d[i][j] = INF;

    while (m--)
    {
        int a, b, w;
        scanf("%d%d%d", &a, &b, &w);
        // 如果有多条边，保留最小边即可
        d[a][b] = min(d[a][b], w);

    }

    floyd();

    // 处理所有询问
    while (Q--)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        if (d[a][b] > INF / 2) puts("impossible"); // 如果 a 到 b 不存在通路的话，他的最短距离不一定是正无穷，可能会比正无穷小一些。
        else printf("%d\n", d[a][b]);
    }

    return 0;
}

