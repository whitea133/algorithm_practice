#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 510, M = 10010;

int n, m, k; // k 是 最多不能经过 k 条边
int dist[N], backup[N];

struct Edge
{
    int a, b, w;
}edges[N];

int bellman_ford()
{
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;

    for (int i = 0; i < k; i++) // 这里的迭代次数，与输入的 k 息息相关
    {
        // 备份一下，保证我们每次的迭代，都只用上一次迭代的结果进行更新，而不是本次迭代的结果，这样可以避免连锁更新
        memcpy(backup, dist, sizeof dist);
        
        for (int j = 0; j < m; j++)
        {
            int a = edges[j].a, b = edges[j].b, w = edges[j].w;
            dist[b] = min(dist[b], backup[a] + w);    
        }
    }

    // 有负权的图，才会是用以下的判断方式。
    if (dist[n] > 0x3f3f3f3f / 2) return -1; // 这里注意要 / 2 一下。就是表示距离大于一个比较大的数。(负权所致)

    return dist[n];
}

int main()
{
    scanf("%d%d%d", &n, &m, &k);

    // 初始化所有边
    for (int i = 0; i < m; i++)
    {
        int a, b, w;
        scanf("%d%d%d", &a, &b, &w);
        edges[i] = {a, b, w};
    }

    int t = bellman_ford();

    if (t == -1) puts("impossible");
    else printf("%d\n", t);
    
    return 0;
}