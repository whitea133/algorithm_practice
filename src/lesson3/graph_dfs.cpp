// dfs 图/树的深度优先搜索 : 对应题目 -- 树的重心
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 100010, M = N * 2; // 图一共有 n-1 条边，每条边占 2 个位置，总边存储量最多 2n。后面的e[M], ne[M]会用到

int n, m;
int h[N], e[M], ne[M], idx; // e[i] 表示下标为i的时候，对应图中的哪个结点，图中的节点是用字母/数字表示的。相当于把idx转化成图中字母/数字
bool st[N]; // 因为每个节点最多只遍历一次，因此要用一个布尔数组记录

int ans = N; // 用来记录答案的一个全局变量

// 边的添加 -- 代码模版。 注意 a, b 是图中的编号
void add(int a, int b)
{
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx++;
}

// 深度优先搜索 -- 代码模版
int dfs(int u) // u 表示把 u 点删掉,
{
    st[u] = true; // 标记一下， 已经被搜过了

    int sum = 1, res = 0; // sum记录当前子树所有结点的个数。 res存储的是把当前子树删除后，每一个连通块里结点个数的最大值
    for (int i = h[u]; i != -1; i = ne[i]) // 遍历一下 u 的所有出边
    {
        int j = e[i]; // e[i] 表示当前链表里的节点，对应图里面的编号是多少(编号是字母，也可以是数字）。这里用 j 暂存
        if (!st[j]) 
        {
            int s = dfs(j); // 用 s 来表示当前子 j 这个子树的结点个数
            res = max(res, s); // j 属于 删除父结点后的连通块，因此要比较取结点个数最大值
            sum += s;
        }
    }

    res = max(res, n-sum);

    ans = min(ans, res); // 取 ans 和当前一次dfs的res进行对比。更新最小值

    return sum; // 返回的是当前子树下所有结点的个数
}

int main()
{
    cin >> n;
    memset(h, -1, sizeof h);
    
    for (int i = 0; i < n - 1; i++) // 题目要求是接下来 n - 1 行里面，输入a, b 表示两者之间有一条边
    {
        int a, b;
        cin >> a >> b;
        add(a, b), add(b, a); // 因为是无向边，因此 add 两次
    }

    dfs(1); // 从图中的 1 号点开始搜，注意 1 是图中的编号 

    cout << ans << endl;

    return 0;
}