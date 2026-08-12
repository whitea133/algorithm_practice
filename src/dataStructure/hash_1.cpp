// hash表--拉链法，这个算法模版允许出现重复数字
#include <iostream>
#include <cstring> // 提供std:memset、std:strcmp之类的函数。相比于string.h，多了std:前缀
using namespace std;

const int N = 100003;

int h[N], e[N], ne[N], idx; // 这里h[N]后面的数组，都是单链表要用到的数组

// 插入操作
void insert(int x)
{
    int k = (x % N + N) % N;    // 这样的操作可以保证正负数都hash为同一个正数
    // 利用单链表的头插法，以 h[k] 为头指针指向的结点
    e[idx] = x; // 先赋值
    ne[idx] = h[k]; // 新节点与h[k]指向同一个结点
    h[k] = idx++;   // 更新h[k]指向新插入的结点位置为idx，之后idx+1
}

// 查询操作
bool find(int x)
{
   int k = (x % N + N) % N; // 先找到 x 映射到了第几个数
   // 然后从 h[k] 下面的拉链，进行循环查找，直到找到x，否则返回不存在
   for (int i = h[k]; i != -1; i = ne[i])   // i != -1 表示下一个结点不是空的
   {
        if (e[i] == x) return true;
   } 
   
   return false;    // 如果没找到，则返回false
}

int main()
{
    int n;
    scanf("%d", &n);
    memset(h, -1, sizeof h);    // 空指针用-1表示。memset(内存起始地址, 填充字节值, 填充字节总长度);
    // 这里memset的操作，目的是初始化所有的头指针h[k]，都初始指向空（-1表示）。

    while (n--)
    {
        char op[2];
        int x;
        scanf("%s%d", op, &x);

        if (op[0] == 'I') insert(x);
        else
        {
            if (find(x)) puts("Yes");
            else puts("No");
        }
    }

    return 0;
}