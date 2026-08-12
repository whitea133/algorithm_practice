// dfs 排列数字问题: 给定一个数字 n, 将数字 1 ～ n 排成一排，输出所有排列方案
#include <iostream>
using namespace std;

const int N = 10;
int n;
int path[N]; // path用来记录路径
bool st[N]; // st数组用来记录哪些数被用过了，比如 st[1] = true 就说明数字1被用用过了

void dfs(int u)
{
    // 先写搜索停止条件
    if (u == n) // 如果搜索的次数已经到了n，则说明已经搜索到了一个叶子结， 即1次搜索结束
    {
        for (int i = 0; i < n; i++) printf("%d ", path[i]); // 搜索结束后，输出一下当前的完整搜索了路径
        puts("");
        return;
    }

    for (int i = 1; i <= n; i++) // i = 1开始，是因为可填的数字是 1～n
    {
        if (!st[i])
        {
            path[u] = i;
            st[i] = true;
            dfs(u+1); // 递归下一层
            // 恢复现场
            st[i] = false; // 这里不用恢复 path[u] = 0， 因为后面迟早要覆盖，当然恢复也没关系
        }
    }

}

int main()
{
    cin >> n;

    dfs(0); // 从根结点开始搜索
}