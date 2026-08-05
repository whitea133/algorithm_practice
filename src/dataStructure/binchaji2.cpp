// 对应acwing算法题：联通块中的数量
#include <iostream>
using namespace std;

const int N = 100010;

int n, m;
int p[N], size[N];   // father数组，存储每个结点的父结点是谁。
// size[N]记录当前结点所在的整个集合的点点总数。注意规定只有根结点的size有意义

// find核心函数，返回x所在集合的编号 + 路径压缩
int find(int x)
{
    if (p[x] != x) p[x] = find(p[x]);   // 如果 x 不是根结点的话(即p[x] != x)，就让他的父结点，等于他父结点的祖宗结点
    return p[x];
}

int main()
{
    scanf("%d%d", &n, &m);

    // 初始的时候，所有结点都是独立的，因此自己是根结点,p v[i] = i
    for (int i = 0; i < n; i++) 
    {
        p[i] = i;
        size[i] = 1;    // 初始时所有的结的集合都只有自己一个
    }

    while (m--)
    {
        char op[5];
        int a, b;
        // 注意这里用%s来读取，是因为这样可以自动忽略空格和回车
        scanf("%s", op);

        // 合并操作：合并x属于的集合与y属于的集合
        if (op[0] == 'C') 
        {
            scanf("%d%d", &a, &b);
            if (find(a) == find(b)) continue;   // 如果a和b已经在同一个集合里面了，直接跳过当前的合并操作(跳过一次while循环)
            size[find(b)] += size[find(a)]; // 更新整个新集合的点的个数
            p[find(a)] = find(b); // a的祖宗结点的父亲等于b的祖宗结点
        }
        else if (op[1] == '1')   // 判断两个结点是否是在同一个集合里面
        {
            scanf("%d%d", &a, &b);
            if (find(a) == find(b)) puts("Yes");
            else puts("No");
        }
        else    // 询问当前结点所处集合的结点总数
        {
            scanf("%d", &a);
            printf("%d\n", size[find(a)]);  // 找到a点的根结点，返回根结点的size即可
        }
    }

    return 0;
}
