// 双指针算法。可以将两层循环O(n^2)变为O(n)
#include <iostream>
#include <string> // 用来处理字母
using namespace std;

bool check(int i, int j) {return true;};

void moban()    // 双指针算法的通用思想模版
{
    int i, j;
    while (j < i && check(i, j)) j++; // j 是小于 i 的一个指针，一般用来作左边界

    // 每道题的具体逻辑

}

// 双指针算法的一个实例。比如：读入一整行字符串，按空格分割，把每个单词单独一行输出
int main()
{
    string str;
    getline(cin, str);
    int n = str.size();


    for (int i = 0; i < n; i++)
    {
        int j = i;
        while (j < n && str[j] != ' ') j++;

        // 这道题的具体逻辑
        for (int k = i; k < j; k++) cout << str[k];
        cout << endl;

        i = j;
    }

    return 0;

}
