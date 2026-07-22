// 高精度除法
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// A / b, 商是C，余数是 r。
vector<int> div(vector<int> &A, int b, int &r)  // r 是引用
{
    vector<int> C; // 商
    r = 0;
    for (int i = A.size() - 1; i >= 0; i--)
    {
        r = r * 10 + A[i];
        C.push_back(r / b);
        r %= b;
    }

    reverse(C.begin(), C.end());    // 调整 C 的结构，保持 i=0 存低位
    while (C.size() > 1 && C.back() == 0) C.pop_back(); // 去掉前导0

    return C;
}

int main()
{
    string a;
    int b;
    cin >> a >> b;

    vector<int> A;
    for (int i = a.size() - 1; i >= 0; i--) A.push_back(a[i] - '0');

    int r;  // 余数r
    auto C = div(A, b, r);

    for (int i = C.size() - 1; i >= 0; i--) printf("%d", C[i]);
    cout << endl << r << endl;

    return 0;
}

