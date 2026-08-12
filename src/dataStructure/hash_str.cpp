#include <iostream>
using namespace std;

typedef unsigned long long ULL; //  Q = 2^64 是经验值

const int N = 100010, P = 131;  // P进制, P = 131 是经验值

int n, m;
char str[N];
ULL h[N], p[N]; // h[0] = 0,h[i] 代表：字符串前 i 个字符 str[1] ~ str[i] 换算成的 P 进制哈希值。

ULL get(int l, int r)
{
    return h[r] - h[l - 1] * p[r - l + 1];  // 套用公式
}

int main()
{
    scanf("%d%d%s", &n, &m, str + 1); // 字符串从str下标为1开始

    p[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        p[i] = p[i - 1] * P;
        h[i] = h[i - 1] * P + str[i]; // str[i] 是字符的ascii码十进制数值，比如'a' -> 97
    }

    while (m--)
    {
        int l1, r1, l2, r2;
        scanf("%d%d%d%d", &l1, &r1, &l2, &r2);
        
        if (get(l1, r1) == get(l2, r2)) puts("Yes");
        else puts("No");
    }

    return 0;
}