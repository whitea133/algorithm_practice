# LeetCode 704 二分查找 终极复盘笔记（AcWing模板版）

## 一、题目核心要求

给定一个**有序无重复数组**`nums` 和目标值 `target`：

- 找到 target，返回对应下标

- 找不到 target，返回 `-1`

核心适配：LeetCode 为**函数式OJ**，只需写逻辑，无需 `main`、输入输出

## 二、关键前置认知（新手最大误区）

### 1\. vector 下标与迭代器区分

- `nums.begin() / nums.end()`：迭代器（不是数字下标）

- **首下标固定为 0**

- **尾下标固定为 nums\.size\(\) \- 1**（有效最后一位）

- `nums.end()`：最后一位的后一位（越界位置，不可访问）

### 2\. while\(l \< r\) 循环核心定理（必背）

AcWing 区间模板专属规则：

- 循环条件：`while (l < r)`

- 退出循环**必然 l == r**（无 l \> r 情况）

- 原理：两套固定分支只会缩小区间，永远保证 `l ≤ r`，联立退出条件 `l ≥ r`，最终只能相等

- 结论：循环结束后 `nums[l]` 和 `nums[r]` 完全等价

## 三、AcWing 两套可AC模板（本题通用）

704 无重复元素，**左边界、右边界模板均可通过**，底层语义不同

### 模板一：左边界模板（推荐找「第一个满足条件」）

#### 核心逻辑

- 取值：`mid = (l + r) >> 1`（向下取整）

- 条件：`nums[mid] >= target` 收缩右边界（包含等于、大于两种情况）

- 结果含义：找到 **第一个 ≥ target 的位置**

- 必须后置校验：判断该位置是否等于 target，否则返回 \-1

#### 完整AC代码

```cpp
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int l = 0, r = nums.size() - 1;
        while (l < r)
        {
            int mid = (l + r) >> 1;
            if (nums[mid] >= target) r = mid;
            else l = mid + 1;
        }
        // 最终校验：无匹配返回-1
        return nums[l] == target ? l : -1;
    }
};
```

#### 致命易错点（为什么不能写 ==）

禁止将条件写为 `nums[mid] == target`！

- `==` 仅匹配相等情况，**漏掉 mid \> target** 的场景

- 大于 target 时会误走 `l = mid + 1`，丢失正确区间，导致答案错误

- `>=` 同时覆盖「等于、大于」，是完整逻辑

### 模板二：右边界模板（推荐找「最后一个满足条件」）

#### 核心逻辑

- 取值：`mid = (l + r + 1) >> 1`（**必须\+1，向上取整，防死循环**）

- 条件：`nums[mid] <= target` 收缩左边界

- 结果含义：找到 **最后一个 ≤ target 的位置**

- 同样需要后置校验

#### 完整AC代码

```cpp
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int l = 0, r = nums.size() - 1;
        while (l < r)
        {
            int mid = (l + r + 1) >> 1;
            if (nums[mid] <= target) l = mid;
            else r = mid - 1;
        }
        return nums[l] == target ? l : -1;
    }
};
```

#### 致命易错点（必须\+1）

右边界模板 **mid 必须 \+1**，否则会死循环：

例：`nums=[1,5], target=5`，无\+1时区间无法收缩，卡死 `l=0, r=1`

## 四、两套模板核心对比表（必记）

|模板类型|mid 计算方式|判断条件|区间更新|最终含义|
|---|---|---|---|---|
|左边界|`(l+r)>>1`|`nums[mid] >= target`|`r=mid`|第一个 ≥ target|
|右边界|`(l+r+1)>>1`|`nums[mid] <= target`|`l=mid`|最后一个 ≤ target|

## 五、核心通用规则（刷题万能口诀）

1. `while(l < r)` 结束必 `l==r`，一定需要**最后一次校验**

2. 左模板看 `>=`，向下取整；右模板看 `<=`，向上取整

3. 绝对不能单用 `==` 判断，逻辑残缺必错

4. 右模板 mid 必须 `+1`，杜绝死循环

## 六、拓展：与代码随想录模板区别

- 代码随想录：`while(l <= r)`，结束 `l > r`，找到直接return，无需后置校验，适合纯查找

- AcWing模板：适合**找左右边界**（LeetCode 34题），通用性更强

> (Note: May contain AI-generated content.)
