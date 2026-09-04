# LeetCode 69. x 的平方根

## 题目

- 题目链接：https://leetcode.cn/problems/sqrtx/
- 题意：给非负整数 x，返回算术平方根的整数部分，舍弃小数；禁止调用内置指数函数。
- 数据范围：$0 \le x \le 2^{31}-1$

---

## AC 代码

```cpp
class Solution {
public:
    int mySqrt(int x) {
        int l = 0, r = x; // 这个 r = x 的技巧一定要学会
        while (l < r)
        {
            int mid = (l + r + 1ll) >> 1;
            if (mid <= x / mid) l = mid;
            else r = mid - 1;
        }
        return l;
    }
};
```

---

## 算法思想：整数二分（找右边界）

**目标**：找出最大的整数 mid，满足 $mid^2 \le x$

- **条件成立** `mid <= x / mid`：mid 符合条件，答案在 mid 及其右侧，执行 `l = mid`
- **条件不成立**：mid 数值过大，答案在左侧，执行 `r = mid - 1`

因为更新逻辑为 `l = mid`，mid 必须上取整，防止二分死循环：`mid = (l + r + 1) / 2`

### AcWing 整数二分模板：寻找满足条件的最大值

```cpp
while(l < r){
    int mid = (l + r + 1ll) >> 1;
    if(check(mid)) l = mid;
    else r = mid - 1;
}
// 循环结束 l == r，即为答案
```

---

## 三大高频踩坑点

### 坑 1：l + r int 整型溢出

**错误写法**：

```cpp
int mid = (l + r + 1) >> 1;
```

当 l、r 接近 INT_MAX(2147483647)，`l + r + 1` 直接超出 32 位有符号 int 上限。

C++ 中有符号整数溢出属于未定义行为。LeetCode 开启 UBSan 会直接报 runtime error；AcWing 普通 OJ 不会报错，但计算结果错乱。

**修复**：加上 `1ll`，把表达式提升为 long long 做运算，计算结束再转回 int。

```cpp
int mid = (l + r + 1ll) >> 1;
```

### 坑 2：乘法溢出 mid * mid <= x

```cpp
if(mid * mid <= x) // ❌危险，mid较大时乘积爆int
```

示例：mid = 46341，`mid * mid` 直接超过 int 上限，溢出变成负数，判断逻辑出错。

**替换为除法形式** `mid <= x / mid`，整数场景等价，规避乘法溢出。

mid 不会等于 0，不会触发除零错误。

### 坑 3：死循环风险

更新分支写 `l = mid`，mid 必须使用上取整。

如果误用下取整 `(l + r) >> 1`，当 `l = r - 1` 会陷入死循环。

---

## 关键测试用例

| 输入 | 输出 |
|------|------|
| 4 | 2 |
| 8 | 2 |
| 9 | 3 |
| 0 | 0 |
| 2147483647 | 46340 |

---

## 整数二分两套模板速查

> ⚠️ 大数范围下，加法务必带上 `1ll` 防止溢出

### 模板 1：找最大满足条件（本题使用，上取整）

```cpp
int l = 0, r = n;
while(l < r){
    int mid = (l + r + 1ll) >> 1;
    if(check(mid)) l = mid;
    else r = mid - 1;
}
// l == r 得到答案
```

### 模板 2：找最小满足条件（LeetCode34 找左边界，下取整）

```cpp
int l = 0, r = n;
while(l < r){
    int mid = (l + r) >> 1;
    if(check(mid)) r = mid;
    else l = mid + 1;
}
```
