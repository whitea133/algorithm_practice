// hahs表：开放寻址法，这个算法模版不会出现重复数字
#include <iostream>
#include <cstring>
using namespace std;

const int N = 200003, null = 0x3f3f3f3f; // 找一个不属于x范围之内的数，比如这里的0x3f3f3f3
// 上面找的那个数是一个约束，用来表示，如果当前find到的值是这个约定的数，则说明当前的坑位是没有人的

int h[N];

// 开发寻址法的find函数：如果找到了x，则返回x存储的位置；如果没找到x，则返回x应该要存储的位置
int find(int x)
{
    int k = (x % N + N) % N;

    while (h[k] != null && h[k] != x) // 当前的坑位上有人，并且不等于x的话
    {
        k++; /// 寻找下一个坑位
        if (k == N) k = 0;  // 如果k == N的话，则说明看完了最后一个坑位，则循环回去看第一个坑位
    }

    // 因为我们设置了两倍的坑位，因此上面的循环一定会停止
    return k;   // 如果找到了x，则k表示x所在的坑位。如果没找到x，则表示x要进入的坑位
}

int main()
{
    int n;
    scanf("%d", &n);

    memset(h, 0x3f, sizeof h);  // 每一个字节都填 3f，4个字节就是0x3f3f3f3f

    while (n--)
    {
        char op[2];
        int x;
        scanf("%s%d", op, &x);

        int k = find(x);
        if (op[0] == 'I') h[k] = x;// 插入操作
        else    // 查找操作
        {
            if (h[k] != null) puts("Yes");  // 不等于null，则说明占到了坑位
            else puts("No");
        }
    }

    return 0;
}