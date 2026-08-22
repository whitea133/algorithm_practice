// 完全背包问题优化1: 通过数学性质，消去循环 k，直接让后面的等于 f[i][j-v] + w
// 优化2: k 循环去掉后，按照 0 - 1背包的优化方法，改成一维的 f[N]。
// 和0 - 1 背包问题不同的是， j 是从 0开始的，从小到大，因为是 f[i][j-v] + w, 第 i 层的
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1010;

int n, m;
int v[N], w[N];
int f[N];

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> v[i] >> w[i];

    for (int i = 1; i <= n; i++)
        for (int j = v[i]; j <= m; j++) // 因为 j 必须 >= v[i],因此 j 从 v[i] 开始即。
            // k = 0 包括了不选物品i到情况了。所以不用先 f[i][j] = f[i-1][j], 再 for (int k = 1)开始进行更新
            f[j] = max(f[j], f[j - v[i]] + w[i]);
    

    cout << f[m] << endl;

    return 0;
}