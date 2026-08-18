    // 地杰斯特拉算法
    #include <cstring>
    #include <iostream>
    #include <algorithm>
    using namespace std;

    const int N = 510; // 点才510个，一般就是边多，为稠密图

    int n, m;
    int g[N][N]; // 稠密图采用邻接矩阵最好
    int dist[N];
    bool st[N];

    int dijkstra()
    {
        // 初始化 距离dist矩阵，都初始化为正无穷，这里用 0x3f代替
        memset(dist, 0x3f, sizeof dist); 
        dist[1] = 0; // 1 号点初始化为0

        for (int i  = 0; i < n; i++) // 迭代 n 次
        {
            // t = -1 表示刚刚开始的标记
            int t = -1;
            for (int j = 1; j <= n; j++)
            {
                if (!st[j] && (t == -1 || dist[t] > dist[j])) t = j;
            }
            // -----  上面 3 行 代码的作用是：t = 当前还没确定最短距离的点中，距离源点最近的那个点的编号。求 t ----

            st[t] = true; // 找到距离源点最短距离的点 t 后，标志 st[t] = true, 意味着该点已找到最短距离

            // 拿 t 来更新其他点的距离
            for (int j = 1; j <= n; j++) dist[j] = min(dist[j], dist[t] + g[t][j]);
        }

        if (dist[n] == 0x3f3f3f3f) return -1; // 1 和 n 是 不连通的， 返回-1

        return dist[n]; //  否则返回1 到 n 的最短距离

    }

    int main()
    {
        scanf("%d%d", &n, &m);

        // 初始化邻接矩阵
        memset(g, 0x3f, sizeof g);  // 这里用 3f 来代表。刷题首选这个 0x3f 做无限大标记。用 0xff 会有相加溢出问题

        // 读入 m 条边, 下面的代码是 邻接矩阵 插入边的方式，要背
        while (m--)
        {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            g[a][b] = min(g[a][b], c); // 根据题目条件，a和b可能有多条边，我只保留最短的边，来简化问题
        }

        int t = dijkstra();

        printf("%d\n", t);

        return 0;
    }
