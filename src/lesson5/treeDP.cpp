// 树形DP：没有上司的舞会
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 6010;
int n;
int happy[N];
int h[N], e[N], ne[N], idx; // 邻接表
int f[N][2];
bool has_father[N]; // 根结点是没有父节点的结点

void add(int a, int b)
{
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx++;
}

void dfs(int u)
{
    f[u][1] = happy[u]; // 选择u，则要加上u到幸福度

    for (int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        dfs(j); // 递归处理, 自底向上。

        f[u][0] += max(f[j][0], f[j][1]);
        f[u][1] += f[j][0];
    }
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &happy[i]); // 先输入所有人的幸福度

    memset(h, -1, sizeof h); // 初始化所有领接表的表头
    for (int i = 0; i < n - 1; i++)
    {
        int a, b;
        scanf("%d%d", &a, &b); // a，b表示 b 是 a 的父节点
        has_father[a] = true;
        add(b, a);
    }
     
    int root = 1; // 根结点从1开始枚举
    while (has_father[root]) root++; // 找到根结点

    dfs(root);

    printf("%d\n", max(f[root][0], f[root][1])); // 选择根结点和不选根结点中去最大值


    return 0;
}