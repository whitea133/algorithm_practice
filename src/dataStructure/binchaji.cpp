#include <iostream>
using namespace std;

const int N = 100010;

int n, m;
int p[N];   // father数组，存储每个结点的父结点是谁

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
    for (int i = 0; i < n; i++) p[i] = i;

    while (m--)
    {
        char op[2];
        int a, b;
        // 注意这里用%s来读取，是因为这样可以自动忽略空格和回车
        scanf("%s%d%d", op, &a, &b);    // 这里的a和b是对应结点的编号

        // 合并操作：合并x属于的集合与y属于的集合
        if (op[0] == 'M') p[find(a)] = find(b); // a的祖宗结点的父亲等于b的祖宗结点
        else    // 判断两个结点是否是在同一个集合里面
        {
            if (find(a) == find(b)) puts("Yes");
            else puts("No");
        }
    }

    return 0;
}
