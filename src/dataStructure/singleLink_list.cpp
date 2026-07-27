// 单链表
#include <iostream>
using namespace std;

const int N = 100010;

// head 表示头节点指向的节点(初始为-1.即为空节点)
// e[i] 表示节点i的值
// ne[i] 表示节点i的next指针是多少。取 -1 则表示后面没有结点。
// idx 存储当前已经用到了哪（也就是下一个准备用的节点的下标）。
int head, e[N], ne[N], idx;

// 初始化操作
void init()
{
    head = -1;
    idx = 0;
}

// 头插法：将x插入到头节点
void add_to_head(int x)
{
    e[idx] = x; // 赋值
    ne[idx] = head; // 新节点的next改成和head指向同一个节点
    head = idx; // 更新head指向当前的 idx节点
    idx++; // idx+1，移到下一个可用节点的位置
}

// 值为x的节点插入到下标是k的节点（e[k]，ne[k]表示的节点）的后面
void add(int k, int x)
{
    e[idx] = x;
    ne[idx] = ne[k];
    ne[k] = idx;
    idx++;
}

// 将下标是k的点后面的点删掉
void remove(int k)
{
    ne[k] = ne[ne[k]];
}

// 将x插入到头节点后面
void add_to_head(int x)
{
    e[idx] = x;
    ne[idx] = head;
    head = idx;
    idx++;
}

int main()
{
    int m;
    cin >> m;

    init(); // 记得要初始化链表

    while (m--) // 询问操作都采用这种格式，多少次循环，就直接 m-- ，很方便
    {
        int k, x;
        char op;
        if (op == 'H')  // 在头节点插入
        {
            cin >> x;
            add_to_head(x);
        }
        else if (op == 'D')
        {
            cin >> k;
            if (!k) head = ne[head]; // 如果输入的k为0，则是删除头节点。
            remove(k - 1);
        }
        else
        {
            cin >> k >> x;
            add(k, x);
        }
    }

    for (int i = head; i != -1; i = ne[i]) cout << e[i] << ' ';
    cout << endl;

    return 0;   
}
