// 多重背包问题, 每个物品的数量各不相同，用s[i] 表示
// 朴素版的多重背包代码。和完全背包类似
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 110;

int n, m;
int v[N], w[N], s[N];
int f[N][N];

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> v[i] >> w[i] >> s[i];

    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= m; j++)
            // 枚举一下第 i 个 物品选多少个，比完全背包问题多了更多的一个有限数量的限制, 即 k <= s[i]
            for (int k = 0; k <= s[i] && k * v[i] <= j; k++)
            {
                f[i][j] = max(f[i][j], f[i-1][j - v[i] * k] + w[i] * k);
            }

    
    cout << f[n][m] << endl;
    
    return 0;
}