// 朴素版 0 -1 背包问题代码
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1010;

int n, m;
int v[N], w[N]; // v体积， w 重量权重(价值)
int f[N][N];

int main()
{
    // n是物品个数，m是背包总重量
    cin >> n >> m;

    // 从 1 开始，读入每个物品的体积和重量
    for (int i = 1; i <= n; i++) cin >> v[i] >> w[i];

    // f[0][0~m] 一定都为0，因为0表示不选物品，所以下面的循环从 i = 1 开始，到n就.
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= m; j++) // 这里 j 从 0 开始，其实1也可以，不过按照模版就行
        {
            f[i][j] = f[i-1][j]; // 如果不选物品i，那么情况肯定满足
            if (j >= v[i]) f[i][j] = max(f[i][j], f[i-1][j-v[i]] + w[i]); // 如果选物品i，则必须满足 容量j 要大于等于物品i的体积 v[i]
        }

    cout << f[n][m] << endl;

    return 0;
}