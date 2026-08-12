// 拓扑排序 -- 对应题目：有向图的拓扑排序
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 100010;

int n, m; // n是点的个数, m是边的个数
int h[N], e[N], ne[N], idx;
int q[N], d[N]; // q是队列， d是对应点的入度

void add(int a, int b)
{
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx++;
}

bool topsort()
{
    int hh = 0, tt = -1;

    for (int i = 1; i <= n; i++)
    {
        if (!d[i]) q[++tt] = i; // 把所有入度为0点结点插到队列里面去
    }

    while (hh <= tt) // 当队列不为空的时候
    {
        int t = q[hh++]; // 取队头元素
        // 扩展一下队列
        for (int i = h[t]; i != -1; i = ne[i])
        {
            int j = e[i]; // 找到出边, 以及出去的结点j
            d[j]--; // j的入度-1，表示删除 t->j 的边
            if (d[j] == 0) q[++tt] = j; // 如果 j 的入度为0了，则说明可以作为起点，可以加入队列中
        }
    }

    return tt == n - 1; // 判断一下所有的结点是否都入队了(共n个点，下标0~n-1)，如果是，则存在拓扑序列，返回true
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
        d[b]++; // 记得更新一下b的入度, 因为是多了 a -> b的边
    }

    if (topsort()) // topsort返回是否存在一个拓扑排序
    {
        // 拓扑序列后，q里面0  ~ n-1 次序，恰好就是拓扑序列
        for (int i = 0; i < n; i++) printf("%d ", q[i]);
        puts("");
    }
    else
    {
        puts("-1");
    }

    return 0;
}