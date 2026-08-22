// 线性DP: 数字三角形问题
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 510, INF = 1e9;

int n;
int a[N][N];
int f[N][N]; // 三角形是二维的，所以 f 也是二维。f[i][j] 表示从根结点 到 (i,j)点 的最长距离

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= i; j++) // 第 i 行 有 i 个数字
            scanf("%d", &a[i][j]);

    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= i + 1; j++) // 注意这里 j 要从 0 到 i + 1，一个左边界的左上角吗，另一个是右边界的右上角
            f[i][j] = -INF; // 将距离都初始化为负无穷
    
    f[1][1] = a[1][1]; // 根结点要单独初始化
    for (int i = 2; i <= n; i++) // 从第二行开始计算
        for (int j = 1; j <= i; j++)
            f[i][j] = max(f[i-1][j-1] + a[i][j], f[i-1][j] + a[i][j]);
    
    int res = -INF;
    for (int i = 1; i <= n; i++) res = max(res, f[n][i]); // 枚举一下最厚一层的每个f[i][j]，找出最长的距离

    printf("%d\n", res);

    return 0;
}

