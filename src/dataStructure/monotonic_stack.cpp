// 单调栈
#include <iostream>
using namespace std;

const int N = 100010;

int n;
int stk[N], tt;

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        while (tt && stk[tt] >= x) tt--; // 如果栈是不空的，且栈顶元素是大于等于我们当前这个数的，则该数不需要被用到tt--
        if (tt) cout << stk[tt] << ' ';    // 如果栈不空的，则找到了该元素
        else cout << -1 << ' ';
         
        stk[++tt] = x;  // 栈中加入新元素
    }

    return 0;
}