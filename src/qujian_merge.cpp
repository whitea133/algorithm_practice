// 区间合并算法(对于有交集的两个区间，可以合并为一个大的区间，取并集)
// 快速地把n个区间，有交集的合并。注意两个区间端点想叫的情况，也进行合并
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

typedef pair<int, int> PII; // 把存放两个int的数对类型简写为PII，方便书写。前面存储区间的左端点，后面存储区间的右端点。

const int N = 100010;

int n;
vector<PII> segs;

// 区间河滨模版
void merge(vector<PII> &segs)
{
    vector<PII> res;    // 合并后的区间结果

    sort(segs.begin(), segs.end()); // 第一步是先把所有区间排序
    // 注意：对于pair的排序，C++的sort会先以pair的左端点进行排序，再以右端点进行排序

    int st = -2e9, ed = -2e9;   // 初始化边界值
    for (auto seg : segs)
    {
        if (ed < seg.first) // 如果当前维护的区间ed，小于取出的区间的左端点，则没有交集
        {   // 因此当前维护的区间，就是其中的一个答案
            if (st != -2e9) res.push_back({st, ed});
            st = seg.first, ed= seg.second; // 更新维护的区间
        }
        else ed = max(ed, seg.second);  // 如果维护区间和取出的区间没有交集，则将维护区间的右端点取两个区间的最大值
    }

    // 把最后一个区间也要加入到答案里面去
    if (st != -2e9) res.push_back({st, ed});

    segs = res; // 将原区间更新为合并后的区间
}

int main()
{
    cin >> n;
    
    for (int i = 0; i < n; i++)
    {
        int l, r;
        cin >> l >> r;
        segs.push_back({l, r}); // 将区间的左右端点读入到segs中
    }

    merge(segs);    // 调用区间合并算法

    cout << segs.size() << endl;    // 输出区间合并后的区间数量

    return 0;
}
