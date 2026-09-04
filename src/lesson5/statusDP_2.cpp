// 状态压缩2: 最短 Hamilton 路径
// Hamilton 路径：从起点到第 n 个点，所有的点只经过一次的路径
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int N = 20, M = 1 << N;

int n;
int w[N][N]; // w[i][j] 表示两点之间的距离
int f[M][N];
// f[i][j] 从0走到j，走过的所有点存在 i 当中，这样的路径。(每个点只走过一次)。f[i][j] 的属性是集合中的最小值
// i 是表示状态的二进制数，i = 1110011 表示第一二个点走过了，第三四个点没走，第伍六七点点走过了


int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> w[i][j];

    memset(f, 0x3f, sizeof f);
    // 初始状态，从 0 走到 0。则 i 应该为 ....01，即第一个点是走过的
    f[1][0] = 0; 
    for (int i = 0; i < 1 << n; i++)
        for (int j = 0; j < n; j++) // 枚举所有走到的终点
            if (i >> j & 1) // 必须保证走过 j 这个点才有意义，不过没有走过j，则不进行后面的操作
            {
                for (int k = 0; k < n; k++) // 枚举 j 从 哪一个 k 点转移过来
                    if ((i - (1 << j)) >> k & 1) // i 除去 j 这个点后到路径，必须是包含 k这个点的
                        f[i][j] = min(f[i][j], f[i - (1 << j)][k] + w[k][j]);
            }

    
    cout << f[(1 << n) - 1][n-1] << endl; // (1 << n) - 1表示有 n 个 1。然后 n-1 是最终落脚到 n - 1这个点。
    // n - 1的点是选定好的，输入距离的时候要输入正确。
    
    return 0;
}