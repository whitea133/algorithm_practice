// SPFA 算法判断是否有 负环
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

typedef pair<int, int> PII;

const int N = 100010;

int n, m;
int h[N], e[N], ne[N], idx, w[N];
int dist[N], cnt[N]; // 判断负环，需要 cnt 数组。cnt[i] 表示从 源点 到 i 最短路径的边条数
bool st[N]; // st[i] 存的是当前 i 这个点是否在我们的queue队列当中，防止存储到重复的结点

void add(int a, int b, int c)
{
    e[idx] = b;
    w[idx] = c;
    ne[idx] = h[a];
    h[a] = idx++;
}

int spfa()
{
    // 判断负环不需要初始化dist数组
    queue<int> q;
    // 初始要把所有点都加入队列中，因为负环不一定都是从 1 开始的
    for (int i = 1; i <= n; i++)
    {
        st[i] = true;
        q.push(i);
    }

    while (q.size()) // 当队列不空的时候
    {
        int t = q.front();
        q.pop();
        st[t] = false;

        // 更新一下 t 所有的邻边
        for (int i = h[t]; i != -1; i = ne[i])
        {
            int j = e[i];
            if (dist[j] > dist[t] + w[i])
            {
                dist[j] = dist[t] + w[i];
                cnt[j] = cnt[t] + 1; // 每次更新的时候，同时更新一下cnt数组

                if (cnt[j] >= n) return true; // n 个顶点，没有负环的情况下，两点之间的最短路径最多经过 n‑1 条边。
                /*
                如果出现环，还能不停更新变短
                这个环只能是负环（环走一圈总权值为负数，绕一圈距离就变小一点，可以无限绕）。
                普通正环：绕一圈总距离变大，不会触发更新，cnt 不会上涨。
                0 环：绕一圈距离不变，不会进入 if，cnt 也不会上涨。
                负环：绕一圈总距离变小，会反复触发更新，cnt 不断增加，直到 cnt [j] ≥ n
                */

                if (!st[j])
                {
                    q.push(j);
                    st[j] = true;
                }
            }
        }
    }
 
    return false;
}

int main()
{
    scanf("%d%d", &n, &m);
    memset(h, -1, sizeof h);

    while (m--)
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c);
    }

    if (spfa()) puts("Yes");
    else puts("No");

    return 0;
}
