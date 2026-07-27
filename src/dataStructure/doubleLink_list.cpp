// 双链表数据结构
#include <iostream>
using namespace std;

const int N = 100010;

int m;
int e[N], l[N], r[N], idx;  // l表示front结点，r表示next节点

// 初始化
void init()
{
    // 0表示左端点，1表示右端点(偷懒写法)
    r[0] = 1, l[1] = 0;
    idx = 2;    // idx 从 2 开始，应为 0 和 1 已经用过了
}

// 在下标为 k 的点右边插入一个新的节点。tips：可以调用该函数 add(l[k], x)来实现在 k 的左边插入一个新节点
void add(int k, int x)
{
    e[idx] = x;
    // 下面的两步是先将新节点的 l 和 r 指针设置好
    r[idx] = r[k];
    l[idx] = k;
    // 更新左右两个节点中要修改的指针。注意顺序千万不能写反。后面再改r[k]
    l[r[k]] = idx;
    r[k] = idx; 
}

// 双链表中删除第 k 个 点
void remove(int k)
{
    r[l[k]] = r[k]; // “k节点左边的节点”的右边，直接等于 k 的右边
    l[r[k]] = l[k]; // “k节点右边的节点”的左边，直接等于 k 的左边
}


