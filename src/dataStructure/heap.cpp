// 对应的算法题目：堆排序
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 100010;

int n, m;
int h[N], size; // h是heap数组，size是表示h当前存储了多少个元素

void down(int u)
{
    int t = u;  
    // 先判断有没有左儿子，看是否需要交换
    if (u * 2 <= size && h[u * 2] < h[t]) t = u * 2;
    // 再判断是否有右儿子，看是否需要交换
    if (u * 2 + 1 <= size && h[u * 2 + 1] < h[t]) t = u * 2 + 1;
    // 上面执行完之后，得到的 t 就是三个结点中的最小值的下标
    if (u != t) // 如果的确当前结点不是最小值，需要交换，则开始交换
    {
        swap(h[u], h[t]);
        down(t);
    }

}

void up(int u)
{
    while (u / 2 && h[u / 2] > h[u]) // 如果有父结点且自己比父结点更小的话，则自己交换上去
    {
        swap(h[u / 2], h[u]);
        u /= 2; // 更新u的值，准备下一次while循环
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &h[i]);
    size = n;

    // 建堆步骤(优化版，从n/2的为止开始down)
    for (int i = n / 2; i; i--) down(i);
    
    while (m--) // m是输出堆排序后的前m个数字
    {
        printf("%d ",h[1]); // 输出当前堆顶的元素
        // 下面是删除堆顶的元素
        h[1] = h[size];
        size--;
        down(1);
    }



    return 0;
}