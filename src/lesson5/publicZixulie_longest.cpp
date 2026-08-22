// 线性DP:最长公共子序列
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1010;

int n, m;
char a[N], b[N]; // 两个字符串
int f[N][N]; // f[i][j] 表示 a字符串的前i个子串 和 b字符串的前 j 个子串 的最长公共子序列。

int main()
{
    scanf("%d%d", &n, &m);
    scanf("%s%s", a + 1, b + 1);

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {   // 这里集合的划分方法，直接背吧
            f[i][j] = max(f[i-1][j], f[i][j-1]);
            if (a[i] == b[j]) f[i][j] = max(f[i][j], f[i-1][j-1] + 1);
        }

    printf("%d\n", f[n][m]);

    return 0;
}   