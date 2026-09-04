# LeetCode 367. 有效的完全平方数

## 题目

- 题目链接：https://leetcode.cn/problems/valid-perfect-square/
- 题意：给你一个正整数 num，如果 num 是一个完全平方数则返回 true，否则返回 false。不能使用内置库函数（如 sqrt）。
- 数据范围：$1 \le num \le 2^{31}-1$

---

## AC 代码

```cpp
class Solution {
public:
    bool isPerfectSquare(int num) {
        int l = 0, r = num;
        while (l < r) {
            int mid = (l + r + 1ll) >> 1;
            if (mid <= num / mid) l = mid;   // 找最大的 mid 满足 mid*mid <= num
            else r = mid - 1;
        }
        // l == floor(sqrt(num))，验证是否正好等于
        return (long long)l * l == num;
      // 或者是 return l != 0 && l == num / l && num % l == 0
    }
};
```

---

## 算法思路：一次二分 + 平方验证

### 核心思想

这道题本质上是 **LeetCode 69（x 的平方根）的延伸**：

1. 先用二分找到 `floor(sqrt(num))`——即最大的整数 mid 满足 `mid * mid <= num`
2. 再验证这个 mid 的平方是否**正好等于** num

如果正好等于，说明 num 是完全平方数；否则不是。

### 为什么一次二分就够了？

不需要像 LeetCode 34 那样找左右边界。因为：
- 如果 num 是完全平方数，`floor(sqrt(num))` 就是它的平方根，平方后等于 num
- 如果 num 不是完全平方数，`floor(sqrt(num))` 平方后一定小于 num

一次二分 + 一次验证，逻辑清晰且不会出错。

### 二分过程（找右边界模板）

使用 AcWing **找最大满足条件**的模板（上取整）：

```cpp
int mid = (l + r + 1ll) >> 1;   // 上取整，防死循环
if (mid <= num / mid) l = mid;  // mid 可能是答案，往右找
else r = mid - 1;               // mid 太大，往左找
```

条件 `mid <= num / mid` 等价于 `mid * mid <= num`，但用除法避免了乘法溢出。

### 验证阶段：两种等价写法

二分结束后 `l = floor(sqrt(num))`，需要验证 `l * l == num`。有两种等价写法：

#### 写法一：直接乘法（推荐，直观）

```cpp
return (long long)l * l == num;
```

- 用 `(long long)` 强制转换，防止 `l * l` 溢出 int
- 例如 num = 2147483647 时，l = 46340，`46340 * 46340 = 2147395600`，在 int 范围内，但更大的数可能溢出，统一用 long long 更安全

#### 写法二：除法 + 取模（全程 int，不溢出）

```cpp
return l != 0 && l == num / l && num % l == 0;
```

**条件拆解**：

| 条件 | 含义 |
|------|------|
| `num % l == 0` | num 能被 l 整除，即 num = k × l，k 是整数 |
| `l == num / l` | 商 k 等于 l |

两个同时满足 → `num = l × l` → 完全平方数。

**为什么需要两个条件，缺一不可**：

因为 l 是 `floor(sqrt(num))`，所以 `l² <= num < (l+1)²`。

- **num 是完全平方数（num = l²）**：`num/l = l`，`num%l = 0`，两个条件都满足 ✓
- **num 不是完全平方数**：num = l² + r，0 < r < 2l+1
  - 若 r < l（如 num=5, l=2, r=1）：`num/l = l` 但 `num%l = r ≠ 0` → 被 `num%l == 0` 拦截
  - 若 r >= l（如 num=8, l=2, r=4）：`num/l = l+1 ≠ l` → 被 `l == num/l` 拦截

**举例验证**：

| num | l=floor(sqrt) | num/l | num%l | 结果 |
|-----|--------------|-------|-------|------|
| 5 | 2 | 2 | 1 | false（有余数） |
| 8 | 2 | 4 | 0 | false（商不等） |
| 9 | 3 | 3 | 0 | true |
| 10 | 3 | 3 | 1 | false（有余数） |
| 15 | 3 | 5 | 0 | false（商不等） |
| 16 | 4 | 4 | 0 | true |

> `l != 0` 是防御性判断，本题 num >= 1，二分结束后 l 至少为 1，可省略。

---

## 踩坑记录

### 坑 1：两次二分找左右边界（错误思路）

**错误写法**：先找第一个 `mid >= num/mid`，再找最后一个 `mid <= num/mid`，然后比较两者是否相等。

**为什么错**：整数除法截断导致两个条件**不互补**。

以 num=5 为例：
- `5 / 2 = 2`（整数除法截断）
- `mid >= num/mid` → `2 >= 2` → true
- `mid <= num/mid` → `2 <= 2` → true

两个条件同时为真！导致 left = right = 2，错误返回 true，但 5 不是完全平方数。

> 关键教训：`mid >= num/mid` 不等价于 `mid*mid >= num`。整数除法会丢失信息，不能用来做精确的边界判定。

### 坑 2：mid == 0 时直接 return true

```cpp
if (mid == 0) return true;  // ❌ 逻辑错误
```

mid=0 时直接返回 true 是不对的，只是 num=1 时碰巧通过。实际上使用上取整模板时，只要进入循环体 mid 永远 >= 1，不会触发除零，不需要这个特判。

### 坑 3：验证时乘法溢出

```cpp
return l * l == num;  // ❌ l 较大时可能溢出 int
```

必须转成 long long：
```cpp
return (long long)l * l == num;
```

---

## 关键测试用例

| 输入 | floor(sqrt) | 平方 | 输出 |
|------|------------|------|------|
| 1 | 1 | 1 | true |
| 14 | 3 | 9 | false |
| 16 | 4 | 16 | true |
| 25 | 5 | 25 | true |
| 2147483647 | 46340 | 2147395600 | false |

---

## 与 LeetCode 69 的关系

| 题目 | 目标 | 输出 |
|------|------|------|
| LeetCode 69 | 求 x 的平方根整数部分 | 返回 floor(sqrt(x)) |
| LeetCode 367 | 判断是否为完全平方数 | 先求 floor(sqrt(num))，再验证平方是否等于 num |

**LeetCode 367 = LeetCode 69 + 一步验证**。掌握了 69 的二分模板，这道题只需要加一行验证即可。

---

## 复杂度分析

- **时间复杂度**：O(log num)，一次二分
- **空间复杂度**：O(1)
