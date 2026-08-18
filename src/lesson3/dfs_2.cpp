// dsf: n皇后问题 代码1
#include <iostream>
using namespace std;

const int N = 20;

int n;
char g[N][N]; // 找到的一组方案，用二维数组 g 来记
bool col[N], dg[N], udg[N]; // dg是正对角线，udg是反对角线

void dfs(int u)
{
    if (u == n)
    {
        for (int i = 0; i < n; i++) puts(g[i]); // 循环输出每一行的结果
        puts("");
        return;
    }

    for (int i = 0; i < n; i++) // 迭代每一列
    {
        /*
            记忆方法
            dg: 列号u + 行号i = 定值
            udg: 列号u − 行号i = 定值。 但是有负数，要加 n
        */
        if (!col[i] && !dg[u+i] && !udg[n-u+i]) // 这里的对角线的运算，要利用一点数学技巧
        {
            g[u][i] = 'Q';
            col[i] = dg[u+i] = udg[n-u+i] = true; // 表明这些线上都不能再放置新的棋子了
            dfs(u+1);
            col[i] = dg[u+i] = udg[n-u+i] = false; // 递归后, 回溯, 恢复原来的状态
            g[u][i] = '.';
        }
    }
    
}

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            g[i][j] = '.'; 
    }

    dfs(0);

    return 0;
}