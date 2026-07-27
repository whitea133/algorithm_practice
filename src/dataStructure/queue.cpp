// 数据结构：队列(先进先出)
#include <iostream>
using namespace std;

const int N = 100010;
// hh是队头，tt是队尾。在队尾插入元素，在队头弹出元素
int q[N], hh, tt;   // 初始的时候，tt是 -1。这个看习惯的，acwing是栈初始为0，队列初始为-1

void init_queue()
{
    tt = -1;
}

// 插入
void push_queue(int x)
{
    q[++tt] = x;    // 加入新元素后，队尾指针要 +1
}

// 弹出
void pop_queue()
{
    hh++;   // 用横轴的数组来模拟队列，那么hh队头指针往后一位（即向右走），就相当于弹出一个元素了（舍去左边的）
}

// 判断队列是否为空
bool queue_empty()
{
    if (hh <= tt) return false; // 如果 hh 队头指针式小于 tt队尾指针的话，则说明不是空的
    else return true;
}

// 取出队头元素
int queue_top()
{
    return q[hh];
}

// 取出队尾元素
int queue_tail()
{
    return q[tt];
}

