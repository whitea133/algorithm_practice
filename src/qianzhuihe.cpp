// 前缀和算法
#include <iostream>
using namespace std;

const int N = 100010;

int n, m;
int a[N], s[N];

int main()
{
    scanf("%d%d", &n, &m);  // n是数组长度，m是要计算多少次前缀和
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);

    for (int i = 1; i <= n; i++) s[i] = s[i-1] + a[i];  // q求前缀和

    while (m--) // 用这里的算法O(1)，改进了原版需要循环 += c 的O(n)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        printf("%d\n", s[r] - s[l-1]);  // 算部分和
    }

    return 0;
}