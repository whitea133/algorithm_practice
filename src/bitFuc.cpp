// 位运算技巧
#include <iostream>
#include <string.h>
using namespace std;


// 位运算1:求n的第k位数字。n >> k & 1
void bitFuc_1()
{
    int n = 10;
    for (int k = 3; k >= 0; k--) cout << (n >> k & 1);
    cout << endl;
}

// 位运算2：返回n的最后一位1。lowbit(n) = n & -n
int lowbit(int x)
{
    return x & -x;
}

// 这里的bitFuc_2是一个实例。用来返回输入数字中1的个数
void bitFuc_2()
{
    int n;
    cin >> n;   // 输入5，即要输入的次数
    while (n--)
    {
        int x;
        cin >> x;   // 输入x受罪

        int res = 0;
        while (x) x -= lowbit(x), res++;    // 每次减去x的最后一位
        cout << res << ' ';

    }
}

int main()
{
    bitFuc_1();
    bitFuc_2();

    return 0;
}