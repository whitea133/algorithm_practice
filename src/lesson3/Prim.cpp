#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 510, INF = 0x3f3f3f3f;

int n, m;
int g[N][N]; // 稠密图用邻接矩阵比较好
int dist[N]; // dist[i] 是 点 i 距离集合 的最短距离
bool st[N]; // st[i] false 表示当前 i 在集合外

int prim()
{
    memset(dist, 0x3f, sizeof dist);

    int res = 0; // res 存的是最小生成树里边所有边的长度之和
    
    for (int i = 0; i < n; i++)
    {
        // 找到集合外距离当前集合最近的 点。默认是从 1 点开始。
        int t = -1;
        for (int j = 1; j <= n; j++)
            if (!st[j] && (t == -1 || dist[t] > dist[j])) t = j;
    
        if (i && dist[t] == INF) return INF; // 如果不是第一个点，且当前的结点上不连通的，则不存在最小生成树
        if (i) res += dist[t]; // 只要t不是第一个点，dist[t]表示我们当前这个点和我们连通集合里面边的长度
        
        // 用 t 来更新一下其他点到这个集合的距离。注意一定要先累加后更新,因为可能有自环g[t][t] = 0 或者小于0，从而改变dist[t]。
        for (int j = 1; j <= n; j++) dist[j] = min(dist[j], g[t][j]);

        st[t] = true;        
    }

    return res;
}

int main()
{
    scanf("%d%d", &n, &m);

    memset(g, 0x3f, sizeof g);

    while (m--)
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        g[a][b] = g[b][a] = min(g[a][b], c); // 无向图，要定义两条边，其次题目有重边，我们只保留最短的那条边。
    }

    int t = prim();

    if (t == INF) puts("impossible"); // 如果 t 为正无穷，表示不存在生成树(所有点不连通的时候不存在生成树)
    else printf("%d\n", t);

}

