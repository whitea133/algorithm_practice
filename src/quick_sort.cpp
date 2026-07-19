#include <iostream>
using namespace std;
// 快速排序
const int N = 1e6 + 10;

int n;
int q[N];

void quick_sort(int q[], int l, int r)
{
    if (l >= r) return; // 如果当前数组只有个1或0个元素，则返回
    
    int x = q[l], i = l - 1, j = r + 1;
    while (i < j) // 如果 i >= j，则说明指针已经相遇，则要停止继续遍历数组
    {
        do i++; while (q[i] < x);
        do j--; while (q[j] > x);
        if (i < j) swap(q[i], q[j]);    // 如果 i >= j，则说明指针已经相遇，则不进行交换元素
    }

    quick_sort(q, l, j);
    quick_sort(q, j + 1, r);
}

int main(void)
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d", &q[i]);

    quick_sort(q, 0, n - 1);
    for (int i = 0; i < n; i++)  printf("%d ", q[i]);

    return 0;
}