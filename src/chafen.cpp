// 差分：前缀和的逆运算
// 给定长度为 n 的数组，进行 m 次区间操作：[l, r] 所有数字加上 c，最后输出整个数组。
#include <iostream>
using namespace std;

const int N = 100010;

int n, m;
int a[N], b[N];

void insert(int l, int r, int c)
{
    b[l] += c;
    b[r + 1] -= c;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);

    for (int i = 1; i <= n; i++) insert(i, i, a[i]);    // 这里是直接利用插入来创造出b数组，2而无需使用b[i] = a[i] - a[i-1]来构造

    while (m--)
    {
        int l, r, c;
        scanf("%d%d%d", &l, &r, &c);
        insert(l, r, c); 
    }
    // 求前缀和的公式：s[i] = s[i-1] + a[i]
    for (int i = 1; i <= n; i++) b[i] += b[i-1]; // 用b[i]来表示a[i]变化后的结果，然后输出。b[i]不再是差分后的数组了

    for (int i = 1; i <= n; i++) printf("%d ", b[i]);

    return 0;
}