// 多重背包问题的优化: 通过二进制思想
// 将物品数量按二进制数量分组，将数量m的物品，变成新的数量为logm的新物品，
// 新物品是聚合出来的(由一个一个旧物品拼接而成), 按1, 2, 4, 8的二进制比例分组聚合成新物品，就变成 0 - 1背包问题了

#include <iostream>
#include <algorithm>
using namespace std;

const int N = 25000; // 物品的最多数量 nlogs, n 是多少个不同的物品, s是第 i 个物品的数量。就是将 n 个物品 变为 nlogs个新物品，数量都为1

int n, m;
int v[N], w[N];
int f[N];

int main()
{
    cin >> n >> m;
    
    int cnt = 0; // cnt 是构造后0-1背包的新物品的编号
    for (int i = 1; i <= n; i++)
    {
        int a, b, s;
        cin >> a >> b >> s;
        int k = 1; // 从 1 开始聚合
        // 下面是构造新物品的过程
        while (k <= s)
        {
            cnt++;
            v[cnt] = a * k;
            w[cnt] = b * k;
            s -= k; 
            k *= 2;
        }

        if (s > 0)
        {
            cnt++;
            v[cnt] = a * s;
            w[cnt] = b * s;
        }
    }

    n = cnt; // n 是新构造的0-1背包的物品数量
    // 做一遍 0 - 1 背包问题即可
    for (int i = 1; i <= n; i++)
        for (int j = m; j >= v[i]; j--)
            f[j] = max(f[j], f[j - v[i]] + w[i]);


    cout << f[m] << endl;
    
    return 0;
}
