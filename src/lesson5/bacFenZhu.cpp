// 分组背包问题，最终也可以转变为 0 ～ 1 背包问题类似代码
// 分组背包思想：集合划分是，枚举第 i 组物品选哪个，或不选
// 而之前完全背包问题的思想：枚举第 i 组物品选几个

#include <iostream>
#include <algorithm>
using namespace std;

const int N = 10;
int n, m;
int v[N][N], w[N][N], s[N]; // v[a][b] 表示 第 a 组 第 b 个物品的体积, s[i] 表示 第 i 组 有几种物品
int f[N]; // 问题同样可以优化为1维的

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i]; // 读取第 i 组 物品的种类个数
        for (int j = 0; j < s[i]; j++)
            cin >> v[i][j] >> w[i][j];
    }

    for (int i = 1; i <= n; i++)
        for (int j = m; j >= 0; j--) // 从大到小枚举所有的体积
            for (int k = 0; k < s[i]; k++) // 枚举所有的选择(在第i组条件下)，即选第 k 个物品，k为0则不选
                if (v[i][k] <= j) f[j] = max(f[j], f[j - v[i][k]] + w[i][k]);

    cout << f[m] << endl;

    return 0;
}
