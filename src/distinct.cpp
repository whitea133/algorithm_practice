// 离散化
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef pair<int, int> PII;

const int N = 300010;

int n, m;
int a[N], s[N]; // a数组存的是数，s数组存的是和

vector<int> alls;   // 一开始存放所有原始数轴坐标（映射前的大数）,映射后的结果是下标
vector<PII> add, query;


int find(int x) // 二分查找（在alls中），就是求一下 x 这个值离散化后的结果
{
    int l = 0, r = alls.size() - 1;
    while (l < r)
    {
        int mid = (l + r) >> 1;
        if (alls[mid] >= x) r = mid;
        else l = mid + 1;
    }

    return r + 1;   // 保证离散映射后，是从1开始的，因此要加1
}

int main()
{
    cin >> n >> m;
    for (int i = 0; i < n; i++) // 插入操作，在下标为x的位置插上c
    {
        int x, c;
        cin >> x >> c;
        add.push_back({x, c}); 

        alls.push_back(x);  // 把x加入到要离散化的数组alls里面
    }

    for (int i = 0; i < m; i++) // 读入所有的左右区间
    {
        int l, r;
        cin >> l >> r;  // l和r都是要离散化的，加入到query里面去
        query.push_back({l, r});
        alls.push_back(l);  // 同时也要加入到alls里面
        alls.push_back(r);  // 这样x，l，r这三个输入的下标，都加入到了要离散化的数组alls里面
    }

    // 给alls去重（这两个代码要背）
    sort(alls.begin(), alls.end()); // 第一步是先排序
    alls.erase(unique(alls.begin(), alls.end()), alls.end());   // 第二步是吧重复元素去掉

    // 处理插入操作（利用add数组记录的操作）
    for (auto item : add) // 从头到尾，挨个取出 add 里面的每一对元素，临时放进变量 item。auto是自动推断类型
    {
        int x = find(item.first);   // .first表示add
        a[x] += item.second;
    }

    // 预处理前缀和
    for (int i = 1; i <= alls.size(); i++) s[i] = s[i-1] + a[i];

    // 处理询问操作（利用query数组记录的操作）
    for (auto item : query)
    {
        int l = find(item.first), r = find(item.second);
        cout << s[r] - s[l-1] << endl;
    }

    return 0;
}

 
