#include <iostream>
using namespace std;

const int N = 1e5 + 10;

int son[N][26], cnt[N], idx; 
// 假设题目的字符串只能是26个字母，因此每个节点最多26个子结点
// cnt存的是以当前这个节点为结尾的单词有多少个,cnt即count
// idx是结点编号，存的是当前用到的是哪个下标，初始为0。下标是0的点，既是根结点，又是空结点(即这个结点没有子结点)
char str[N];

// 插入字符串操作
void insert(char str[])
{
    int p = 0;  // 从根结点开始
    for (int i = 0; str[i]; i++)    // 用 str[i]来判断是不是走到结尾了
    {
        int u = str[i] - 'a';   // 把字母的编号取出来，映射到 0 ~ 25
        if (!son[p][u]) son[p][u] = ++idx;  // 如果p这个结点没有u编号这个字母，则创建该字母，新节点的编号为idx+1
        p = son[p][u];  // 更新 p 为子结点
    }

    // 结束的时候，p 就是结尾的点
    cnt[p]++;   // 表示以 p 结点为结尾的字符串数量+1
}

// 查询操作，返回字符串出现了多少次
int query(char str[])
{
    int p = 0;
    for (int i = 0; str[i]; i++)
    {
        int u = str[i] - 'a';
        if (!son[p][u]) return 0;
        p = son[p][u];
    }

    return cnt[p];
}

int main()
{
    int n;
    scanf("%d", &n);
    while (n--)
    {
        char op[2]; // 操作的类型，[2] 是因为后面有 '\0' 空 符号
        scanf("%s%s", op, str); // 读入操作类型和对应的字符串
        if (op[0] == 'I') insert(str);
        else printf("%d\n", query(str));
    }

    return 0;
}