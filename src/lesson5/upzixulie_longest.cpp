// 线性DP:最长上升子序列
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1010;

int n;
int a[N], f[N];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);

    for (int i = 1; i <= n; i++)
    {
        f[i] = 1; // 第一类：没有第 i - 1个数，当该序列前一位没有数字时，只有 a[i] 一个数
        for (int j = 1; j < i; j++) // 假设我们的第 i - 1个数是 a[j], j 从 1 开始遍历。
            if (a[j] < a[i]) // 第 i - 1个数必须满足上升这个前提。
            {
                f[i] = max(f[i], f[j] + 1);
            }
    }

    int res = 0;
    for (int i = 1; i <= n; i++) res = max(res, f[i]); // 求出最长的一个上升子序列(因为不知道以哪个为结尾，所以要遍历)

    printf("%d\n", res);

    return 0;
}