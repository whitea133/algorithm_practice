// 状态压缩DP1：蒙德里安的梦想
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 12, M = 1 << N;

int n, m;
long long f[N][M]; // f[i][j] 表示第 i 列， j表示小方格伸出来的状况。比如32，就是 111111，即都伸出来。
// f[i][j] 的属性表示 所有满足f[i][j]方案的个数
bool st[M]; // st[i] = false 表示状态 i 可行，否则不可行

int main()
{
    while (cin >> n >> m, n || m) // n || m 表示输入为0，0时停止
    {
        memset(f, 0, sizeof f);

        for (int i = 0; i < 1 << n; i++) // 这里用 i 枚举所有状态，i 的 n 位二进制数上的每一位就是对应的状态
        {
            st[i] = true;
            int cnt = 0;
            for (int j = 0; j < n; j++) // 逐个对比每一位上数字，j 是右移的位数，从第0位开始。就是看每一行是否有横块伸出去
            {
                if (i >> j & 1) // 右移 j 位之后，取最后一位，如果当前位是1（有横块伸出去）
                {
                    if (cnt & 1) st[i] = false; // 前面连续0的长度cnt是奇数 → 非法！放不下竖直方块
                    cnt = 0; // 遇到1，连续0计数清零
                }
                else cnt++; // 当前位是0，连续0长度+1
            }
            if (cnt & 1) st[i] = false; // 循环跑完所有位之后，还要检查末尾那一段连续 0，如果长度是奇数，同样非法。
        }

        f[0][0] = 1;
        for (int i = 1; i <= m; i++) // 枚举每一列
            for (int j = 0; j < 1 << n; j++) // 枚举一下所有状态
                for (int k = 0; k < 1 << n; k++) // 枚举一下 i - 1 列的所有状态
                    if ((j & k) == 0 && st[j | k])
                        f[i][j] += f[i-1][k];

        cout << f[m][0] << endl;
    }

    return 0;
}