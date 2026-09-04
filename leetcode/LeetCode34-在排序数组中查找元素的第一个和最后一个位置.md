# LeetCode 34. 在排序数组中查找元素的第一个和最后一个位置

## 题目

给你一个按照**非递减顺序**排列的整数数组 `nums`，和一个目标值 `target`。请你找出给定目标值在数组中的开始位置和结束位置。

如果数组中不存在目标值 `target`，返回 `[-1, -1]`。

**要求**：时间复杂度为 **O(log n)**。

---

## 核心思路：两次二分查找

因为数组有序且要 O(log n)，必然用二分。但普通二分只能找到任意一个等于 target 的位置，要找**左右边界**需要分别用两种二分模板：

| 查找目标 | 模板特征 | 含义 |
|---------|---------|------|
| 左边界（第一个 >= target） | `mid = (l + r) >> 1`，`nums[mid] >= target` 时 `r = mid` | 找到第一个满足条件的位置 |
| 右边界（最后一个 <= target） | `mid = (l + r + 1) >> 1`，`nums[mid] <= target` 时 `l = mid` | 找到最后一个满足条件的位置 |

> 类比：左边界模板是"靠左挤"，右边界模板是"靠右挤"。

---

## AcWing 二分模板详解

### 模板一：找左边界（第一个 >= target）

```cpp
int l = 0, r = nums.size() - 1;
while (l < r) {
    int mid = (l + r) >> 1;       // 向下取整
    if (nums[mid] >= target) r = mid;  // 满足条件，右边界左移
    else l = mid + 1;                  // 不满足，左边界右移
}
// 循环结束时 l == r，指向第一个 >= target 的位置
```

**为什么 `mid` 向下取整？**
当 `l` 和 `r` 相邻时（如 `l=2, r=3`），`mid = (2+3)>>1 = 2`。如果满足条件 `r=mid=2`，循环结束；如果不满足 `l=mid+1=3`，循环结束。**不会死循环**。

### 模板二：找右边界（最后一个 <= target）

```cpp
int l = 0, r = nums.size() - 1;
while (l < r) {
    int mid = (l + r + 1) >> 1;   // 向上取整（关键！）
    if (nums[mid] <= target) l = mid;  // 满足条件，左边界右移
    else r = mid - 1;                  // 不满足，右边界左移
}
// 循环结束时 l == r，指向最后一个 <= target 的位置
```

**为什么 `mid` 要 `+1` 向上取整？**
当 `l` 和 `r` 相邻时（如 `l=2, r=3`），如果不加 1，`mid = (2+3)>>1 = 2`。若满足条件 `l=mid=2`，则 `l` 永远是 2，**死循环**。加 1 后 `mid=3`，满足条件 `l=3`，循环结束。

> 记忆口诀：**`l = mid` 时 mid 必须向上取整（+1）；`r = mid` 时 mid 向下取整（不加）。**

---

## 我的代码（AC）

```cpp
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> result;

        // 1. 判空：空数组直接返回 [-1, -1]
        if (nums.size() == 0) {
            result.push_back(-1);
            result.push_back(-1);
            return result;
        }

        // 2. 第一次二分：找左边界（第一个 >= target 的位置）
        int l = 0, r = nums.size() - 1;
        while (l < r) {
            int mid = (l + r) >> 1;
            if (nums[mid] >= target) r = mid;
            else l = mid + 1;
        }

        // 3. 判断 target 是否存在：左边界位置的值不等于 target 说明不存在
        if (nums[l] != target) {
            result.push_back(-1);
            result.push_back(-1);
            return result;
        }

        // 4. 加入左边界
        result.push_back(l);

        // 5. 第二次二分：找右边界（最后一个 <= target 的位置）
        l = 0, r = nums.size() - 1;
        while (l < r) {
            int mid = (l + r + 1) >> 1;
            if (nums[mid] <= target) l = mid;
            else r = mid - 1;
        }

        // 6. 加入右边界（此时 l == r）
        result.push_back(l);

        return result;
    }
};
```

---

## 踩坑记录

### 坑 1：空数组访问越界（UBSan 报错）

**错误信息**：
```
runtime error: reference binding to null pointer of type 'int' (stl_vector.h)
```

**原因**：`nums` 为空时，`nums.size() - 1` 中 `size()` 返回 `size_t`（无符号），`0 - 1` 下溢成巨大的数 `4294967295`，导致 `r` 越界；或者直接访问 `nums[0]` / `nums[l]` 时越界。

**解决**：函数开头先判空：
```cpp
if (nums.empty()) return {-1, -1};
```

### 坑 2：左右边界添加顺序弄反

**问题**：第一次二分找到的是**左边界**，第二次找到的是**右边界**。如果 `push_back` 顺序写反（先 push 右边界再 push 左边界），返回结果就是 `[右, 左]`，不符合题目要求的 `[开始位置, 结束位置]`。

**正确顺序**：
```cpp
result.push_back(l);  // 先加左边界（第一次二分的结果）
// ... 第二次二分 ...
result.push_back(l);  // 再加右边界（第二次二分的结果）
```

> 注意：两次二分都用了变量 `l`，第二次会覆盖第一次的值。所以**必须在第二次二分之前把左边界 push 进去**，否则左边界就丢了！

### 坑 3：右边界模板忘记 `+1` 导致死循环

```cpp
int mid = (l + r) >> 1;  // 错误！右边界模板必须 +1
if (nums[mid] <= target) l = mid;  // l 和 r 相邻时死循环
```

---

## 复杂度分析

- **时间复杂度**：O(log n)，两次二分，每次 O(log n)
- **空间复杂度**：O(1)，只使用常数额外空间

---

## 模板选择速查表

| 需求 | 条件判断 | 更新方式 | mid 计算 |
|------|---------|---------|---------|
| 第一个满足条件 | `nums[mid] >= target` | `r = mid` / `l = mid + 1` | `(l + r) >> 1` |
| 最后一个满足条件 | `nums[mid] <= target` | `l = mid` / `r = mid - 1` | `(l + r + 1) >> 1` |

**一句话记忆**：往左找用 `r=mid`，mid 不加 1；往右找用 `l=mid`，mid 必须加 1。
