#include <iostream>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 100010, M = N * 2; // 图一共有 n-1 条边，每条边占 2 个位置，总边存储量最多 2n。后面的e[M], ne[M]会用到

/*
h 的括号内：树上真实节点编号
e、ne 的括号内：边的存储下标 idx
e [idx] 赋值等号右边：树上真实节点编号
ne [idx] 赋值等号右边：另一个边的 idx
*/
int h[N], e[M], ne[M], idx; // h存的是单个链表的链表头， e存储下标idx对应的是哪个结点， ne存的是每个节点的next指针是多少

// 插入一条a 指向 b 的边
void add(int a, int b) 
{
    // 头插法插入新的边
    e[idx] = b; // 先把节点b赋值上
    ne[idx] = h[a]; // ne的指向和h头结点一样
    h[a] = idx++; // h[a] 指向刚刚插入的结点 idx。然后idx+1
}



int main()
{
    memset(h, -1, sizeof h);
}

