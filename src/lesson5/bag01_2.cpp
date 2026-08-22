// 优化版 0 -1 背包问题代码。一维数组
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1010;

int n, m;
int v[N], w[N]; // v体积， w 重量权重(价值)
int f[N]; // 优化为一维数组

int main()
{
    // n是物品个数，m是背包总重量
    cin >> n >> m;

    // 从 1 开始，读入每个物品的体积和重量
    for (int i = 1; i <= n; i++) cin >> v[i] >> w[i];

    // f[0][0~m] 一定都为0，因为0表示不选物品，所以下面的循环从 i = 1 开始，到n就.
    for (int i = 1; i <= n; i++)
        for (int j = m; j >= v[i]; j--) // 优化后 j 是从 大到小 开始, 又因为 j >= v[i]，所以要修改
            // 优化前f[i][j] = f[i-1][j];
            // 优化后 f[j] = f[j]; 重复了，直接删除
            
            // 优化前 if (j >= v[i]) f[i][j] = max(f[i][j], f[i-1][j-v[i]] + w[i]); 
            f[j] = max(f[j], f[j-v[i]] + w[i]); 

    cout << f[m] << endl;

    return 0;
}