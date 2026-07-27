// 数据结构：栈(先进后出)
#include <iostream>
using namespace std;

const int N = 100010;

int stk[N], tt; // tt表示栈顶的下标。栈初始的时候，tt是 0 

// 初始化栈
void init_stack()
{
    tt = 0;
}

// 插入
void push_stack(int x)
{
    stk[++tt] = x;
}

// 弹出，同时取出栈顶元素
void pop_stack()
{
    tt--;
}

// 判断栈是否为空
bool stack_empty()
{
    if (tt > 0) return false;   // tt栈顶位置不为0，则不为空
    else return true;  // tt栈顶位置为0，则为栈空
}

// 获取栈顶元素
int stack_top()
{
    return stk[tt];
}

