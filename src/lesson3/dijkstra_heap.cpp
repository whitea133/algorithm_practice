// 堆优化的dijkstra算法
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

const int N = 100010; // 点的数量很多，边少，为稀疏图

typedef pair<int, int> PII; // 前面存源点到编号点的距离，后面存编号

int n, m;
// 注意这里不用 M = N * 2, M = N*2 只用在 无向图 / 树。
int h[N], e[N], ne[N], idx, w[N]; // 为稀疏图， 改用 邻接表 存储图。新加的 w 数组存的是边的权重
int dist[N];
int st[N];

void add(int a, int b, int c)
{
    e[idx] = b;
    w[idx] = c; // 
    ne[idx] = h[a];
    h[a] = idx++;
}

int dijkstra()
{
    /*
    求最短路径 → 一律用 0x3f；
    BFS 网格标记有没有访问过 → 用‑1；
    */
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;

    priority_queue<PII, vector<PII>, greater<PII>> heap; // 定义一个小根堆的规定写法。并且因为距离在前面，所以会按照距离最短的排在头部
    heap.push({0, 1});

    while (heap.size()) // 当堆不为空的时候
    {
        auto t = heap.top(); // 找到当前堆中距离最小的点
        heap.pop();
         
        int ver = t.second, distance = t.first; // ver 存点的编号，distance 存 源点 到 ver点 的距离
        if (st[ver]) continue; // 如果这个点之前已经找到过最短距离，则不用管这个点，直接continue，进入下一次循环
        // 标记节点ver已确定最短距离
        st[ver] = true;

        // 用当前新找到的最短点进行更新所有的距离
        for (int i = h[ver]; i != -1; i = ne[i]) // 遍历所有与 ver 点 有关的边
        {
            int j = e[i]; // 用 j 来存储编号
            if (dist[j] > distance + w[i])
            {
                /*
                dist[j]：原来源点到 j 的最短距离
                w[i]: 邻接表存储下，在头节点为 ver 到链表中找到终点为 i(i是idx编号) 的边，即 ver -> i 这条边，w[i] 为该边的值,e[i]为图中编号
                distance + w[i]：走源点→ver→j 这条新路径的总距离
                */
                dist[j] = distance + w[i];
                heap.push({dist[j], j});
            }
        }
    }

    if (dist[n] == 0x3f3f3f3f) return -1;
    
    return dist[n];
}

int main()
{
    scanf("%d%d", &n, &m);

    memset(h, -1, sizeof h); // 初始化所有邻接表

    while (m--)
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        /*
        朴素 Dijkstra（二重循环版本）：要自己预处理重边，a→b 只存权重最小那一条
        堆优化版（优先队列）：不需要提前手动去重边, 直接 add 就行
        */
        add(a, b, c);
    }

    int t = dijkstra();

    printf("%d\n", t);

    return 0;
}