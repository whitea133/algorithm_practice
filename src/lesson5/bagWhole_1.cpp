// 完全背包问题，每一个物品都可以取无限个，当然不能超过总重量
// 朴素版完全背包问题代码
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1010;

int n, m;
int v[N], w[N];
int f[N][N];

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> v[i] >> w[i];

    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= m; j++)
            for (int k = 0; k * v[i] <= j; k++) 
            // k = 0 包括了不选物品i到情况了。所以不用先 f[i][j] = f[i-1][j], 再 for (int k = 1)开始进行更新
            f[i][j] = max(f[i][j], f[i-1][j- v[i] * k] + w[i] * k);
    

    cout << f[n][m] << endl;

    return 0;
}