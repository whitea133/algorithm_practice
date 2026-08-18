// 克鲁斯卡尔算法
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 200010;

int n, m;
int p[N]; // p 是并查集数据结构里面的p

struct Edge
{
    int a, b, w;

    // 重载一下小于号，让他按照权重来排序
    bool operator< (const Edge &W) const
    {
        return w < W.w;
    }
} edges[N];

// 并查集find函数的模版, 查找 x 的祖宗结点
int find(int x)
{
    if (p[x] != x) p[x] = find(p[x]);

    return p[x];
}

int main()
{
    scanf("%d%d", &n, &m);

    for (int i = 0; i < m; i++)
    {
        int a, b, w;
        scanf("%d%d%d", &a, &b, &w);
        edges[i] = {a, b, w};
    }

    sort(edges, edges + m); // 把所有边排。sort( 起始地址 , 结束后一位的地址 ) , edges是起始指针

    int res = 0, cnt = 0;
    // 初始化一下并查集
    for (int i = 1; i <= n; i++) p[i] = i;
    // 从小到大枚举所有边
    for (int i = 0; i < m; i++)
    {
        int a = edges[i].a, b = edges[i].b, w = edges[i].w;

        a = find(a), b = find(b); // 查询 a 和 b 的祖宗结点
        if (a != b) // 如果两个结点的祖宗结点是不连通的话, 就把边加进来
        {
            p[a] = b; // 把两个集合合并
            res += w; // res 存的是最小生成树中所有边的权重之和
            cnt++;  // cnt存的是我们当前加了多少条边
        }
    }

    if (cnt < n - 1) puts("impossible"); // cnt < n-1 表示所有结点是不连通的
    else printf("%d\n", res); 

    return 0;
}   