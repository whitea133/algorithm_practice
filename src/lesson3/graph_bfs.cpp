// 图的宽度优先遍历bfs : 对应算法题目 -- 图中点的层次(输出一个整数表示1号点到n号点的最短距离)
// 点的编号从 1 ～ n
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 100010;

int n, m;
int h[N], e[N], ne[N], idx;
int d[N], q[N]; // d是我们的距离，q是我们的队列

void add(int a, int b)
{
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx++;
}

int bfs()
{
    // 下面是初始化操作
    int hh = 0, tt = 0;
    q[0] = 1; // 第一个元素是起点1
    memset(d, -1, sizeof d); // -1表示该点没有被遍历过
    d[1] = 0; // 第一个点被遍历过了,距离为0。注意 d 从 1 开始，因为题目规定点编号是 1 ~ n

    // bfs框架
    while (hh <= tt) // 如果队列不为空
    {
        int t = q[hh++]; // 每一次都取队头，用 t 保存

        for (int i = h[t]; i != -1; i = ne[i]) // 扩展一下当前这个点
        {
            int j = e[i]; // 每次用j来表示当前t这个点可以到的点
            if (d[j] == -1) // 如果 j 没有被遍历扩展过的话
            {
                d[j] = d[t] + 1; // 扩展 j 这个点
                q[++tt] = j; // 把 j 这个点加到队尾里面
            }
        }
    }
    return d[n] ;
}

int main()
{
    cin >> n >> m;

    memset(h, -1, sizeof h);

    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        add(a, b);
    }

    cout << bfs() << endl;

    return 0;
}



