// bfs 走迷宫问题
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

typedef pair<int, int> PII;

const int N = 110;

int n, m;
int g[N][N]; // g数组存的是题目的地图
int d[N][N]; // d数组存的是每一个点到起点的距离
PII q[N * N], Prev[N][N]; // Prev数组用来记录前一点在哪里， 注意必须是大P

int bfs()
{
    // 采用手动模拟队列的写法
    int hh = 0, tt = 0;
    q[0] = {0, 0};

    memset(d, -1, sizeof d); // -1表示我们的地点没有走过, 如果没有走过且到达了最终地点，那么就是最短的
    d[0][0] = 0; // 为0表示已经走过了

    int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1}; // 用向量表示四个方向。(-1, 0)上, (0, 1)右, (1, 0)下，(0, -1)左

    while (hh <= tt) // 当队列不为空
    {
        auto t = q[hh++];   // 取出来队头

        for (int i = 0; i < 4; i++)
        {
            int x = t.first + dx[i], y = t.second + dy[i]; // 按照上右下左的顺序， 尝试移动
            if (x >= 0 && x < n && y >= 0 && y < m && g[x][y] == 0 && d[x][y] == -1) // 如果满足走过去的条件, 且是第一次搜到
            {
                d[x][y] = d[t.first][t.second] + 1; // 距离+1，
                Prev[x][y] = t; // 保存前一个点 
                q[++tt] = {x, y}; // 把 [x, y] 这个点加进来, 加到队尾
            }
        }
    }

    int x = n - 1, y = m - 1;
    // 从尾到头输出一下整个路径
    while (x || y)
    {
        cout << x << ' ' << y << endl;
        auto t = Prev[x][y];
        x = t.first, y = t.second;
    }

    return d[n-1][m-1];

}

int main()
{
    cin >> n >> m;
    // 先把整个地图读入进来
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++) cin >> g[i][j];
    }

    cout << bfs() << endl;


}
