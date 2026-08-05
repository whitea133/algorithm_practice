// 对应的算法题目：模拟堆
#include <iostream>
#include <algorithm>
#include <string.h>

using namespace std;

const int N = 100010;

int h[N], ph[N], hp[N], size;
// ph[k] 存的是第k个插入的点的下标。hp[k] 存的是堆里面第k个点，是在第几次被插入的。
// 即 ph[j] = k, hp[k] = j;

// 交换两个点的操作
void heap_swap(int a, int b)
{
    swap(ph[hp[a]], ph[hp[b]]);
    swap(hp[a], hp[b]);
    swap(h[a], h[b]); // 交换两个点的值
}

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
        heap_swap(u, t); // 使用我们写的特有的swap函数
        down(t);
    }

}

void up(int u)
{
    while (u / 2 && h[u / 2] > h[u]) // 如果有父结点且自己比父结点更小的话，则自己交换上去
    {
        heap_swap(u / 2, u);
        u /= 2; // 更新u的值，准备下一次while循环
    }
}

int main()
{
    int n, m = 0;
    scanf("%d", &n);

    // 建堆步骤(优化版，从n/2的为止开始down)
    for (int i = n / 2; i; i--) down(i);
    
    while (n--) // m是输出堆排序后的前m个数字
    {
        char op[10];
        int k, x;

        scanf("%s", op);
        if (!strcmp(op, "I"))   // 插入一个数
        {
            scanf("%d", &x);
            size++;
            m++;
            ph[m] = size;
            ph[size] = m;
            h[size] = x;
            up(size);
        }
        else if (!strcmp(op, "PM")) printf("%d\n", h[1]); // 输出当前堆最小值
        else if (!strcmp(op, "DM")) // 删除最小值
        {
            heap_swap(1, size);
            size--;
            down(1);
        }
        else if (!strcmp(op, "D"))  // 删除第K个插入的数
        {
            scanf("%d", &k);
            k = ph[k];  // 找到第k个插入的元素
            // 开始删除步骤
            heap_swap(k, size);
            size--;
            down(k), up(k);
        }
        else // 将第k个插入的数修改
        {
            scanf("%d", &k);
            k = ph[k];  // 找到第k个插入的数
            h[k] = x;   // 修改成x
            down(k), up(k);  
        }
    }
    return 0;
}