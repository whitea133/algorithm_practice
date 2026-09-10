# set和map两者最大的使用区别

- 只需要表示key（只判断存在，无附属信息），就用map。

- 既需要用key，有需要用value，就用map

对于multi，就是可以有重复元素。

对于unordered,，就是基于hash表实现的结构，查找为O(1)，但是不能排序。

还有就是**set和map的key都不能重复**，但是**map的value是可以重复的**。

## 注意事项

1. `set` / `unordered_set`：**禁止 `st[i]` 下标写法**，编译直接报错。set 拿元素只能用迭代器
2. `map/unordered_map` 的`mp[key]`：括号内是**key，不是位置下标**。
3. `vector` 的`vec[idx]`：括号内是**位置下标**。