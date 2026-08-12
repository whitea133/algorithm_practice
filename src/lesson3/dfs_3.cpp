// dsf: n皇后问题 代码2(枚举每一行的棋子是否可以放皇后, 一行枚举完之, 再枚举下一行)
#include <iostream>
using namespace std;

const int N = 20;

int n;
char g[N][N];
bool row[N], col[N], dg[N], udg[N];

void dfs(int x, int y, int s) // 此思路的枚举，需要x，y 指定棋子的位置，s 表示当前已经摆了几个棋子了
{
    if (y == n) y = 0, x++; // 如果一行的棋子枚举完了。则换下一行
    
    if (x == n)
    {
        if (s == n) // 如果 s = n, 则说明找到了一组解, 把这一组解输出出来
        {
            for (int i = 0; i < n; i++) puts(g[i]);
            puts("");
        }
        return;
    }

    // 如果当前的位置不放皇后
    dfs(x, y + 1, s); // 则看下一列的棋子是否放皇后

    // 如果当前位置放皇后
    if (!row[x] && !col[y] && !dg[x+y] && !udg[x-y+n]) // 判断是否满足放queen的条件
    {
        g[x][y] = 'Q';
        row[x] = col[y] = dg[x+y] = udg[x-y+n] = true;
        dfs(x, y+1, s+1);
        // 恢复现场
        row[x] = col[y] = dg[x+y] = udg[x-y+n] = false; 
        g[x][y] = '.';
    }

}