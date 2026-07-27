// 单调队列（常见题型为求输出滑动窗口的最小值/最小值）
#include <iostream>
using namespace std;

const int N = 1000010;

int n, k;
int a[N], q[N]; // a存的是我们原来的值，q是我们的单调队列（存的是下标）

int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);

    int hh = 0, tt = -1;
    for (int i = 0; i < n; i++)
    {
        // 判断队头是否已经滑出了窗口
        if (hh <= tt && i - k + 1 > q[hh]) hh++;
        while (hh <= tt && a[q[tt]] >= a[i]) tt--;
        q[++tt] = i;
        if (i >= k - 1) printf("%d ", a[q[hh]]);
    }

    puts("");   // 输出一个回车

    hh = 0, tt = -1;
    for (int i = 0; i < n; i++)
    {
        // 判断队头是否已经滑出了窗口
        if (hh <= tt && i - k + 1 > q[hh]) hh++;
        while (hh <= tt && a[q[tt]] <= a[i]) tt--;
        q[++tt] = i;
        if (i >= k - 1) printf("%d ", a[q[hh]]);
    }

    puts("");   // 输出一个回车


    return 0;
}