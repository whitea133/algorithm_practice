// 区间dp(f[i][j]状态表示的时候，表示的是一个区间。比如表示从 i 到 j 这个区间)
// 石子合并问题: 要求合并所有石子的花费最小 （石子是有序列的，相邻的）
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 310;

int n;
int s[N]; // 要用到前缀和算法，来完成石子合并
int f[N][N];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &s[i]);

    for (int i = 1; i <= n; i++) s[i] += s[i-1];

    for (int len = 2; len <= n; len++) // 区间的长度，至少要两个石子才能合并
    {
        for (int  i = 1; i + len - 1 <= n; i++) // 枚举石子的左端点，已知长度，则可知道右端点
        {
            int l = i, r = i + len - 1;
            f[l][r] = 1e8;
            for (int k = l; k < r; k++) // 枚举划分的边界 k ，找到 l 到 r 最小花费的划分边界 k
                f[l][r] = min(f[l][r], f[l][k] + f[k+1][r] + s[r] - s[l-1]);
        }
    }

    printf("%d\n", f[1][n]); // 从 1 石子合并到 n 石子
    return 0;
}