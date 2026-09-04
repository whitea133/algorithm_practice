#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 310;

int n, m;
int h[N][N]; // 每一个点的高度
int f[N][N];
int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};

int dp(int x, int y) // 用递归求解 DP
{
    int &v = f[x][y]; // C++的引用写法，所有对v的操作，都是对f[x][y]的操作。两者是同一个东西
    if (v != -1) return v; // v已经被算过，直接返回

    v = 1; // v最小为1，因为至少可以走当前脚下那块地
    for (int i = 0; i < 4; i++) // 枚举上下左右四个方向
    {
        int a = x + dx[i], b = y + dy[i];
        if (a >= 1 && a <= n && b >= 1 && b <= m && h[a][b] < h[x][y]) // 不超出边界，不低于下一个点
        {
            v = max(v, dp(a, b) + 1);
        }
    }
    
    return v;
}

int main()
{
    scanf("%d%d", &n, &m);

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &h[i][j]);

    memset(f, -1, sizeof f); // -1表示每个状态都没有被算过

    int res = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            res = max(res, dp(i ,j));

    printf("%d\n", res);

    return 0;
}