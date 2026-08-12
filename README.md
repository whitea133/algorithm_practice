# algorithm_practice
算法模版练习

## 网页默写工具
项目里有一个本地网页，可以选择 `src` 目录下的代码模板，默写后进行逐行对比；如果配置了 DeepSeek API Key，还会返回大模型分析结果。

在项目根目录启动：

```bash
npm start
```

然后浏览器打开：

```text
http://127.0.0.1:3000
```

如果要启用 DeepSeek 分析，先复制环境变量示例文件：

```bash
cp web/.env.example web/.env
```

再把 `web/.env` 里的 `DEEPSEEK_API_KEY` 改成你的真实 Key。真实 `.env` 文件已经被 `.gitignore` 忽略，不要提交到 GitHub。

## 练习顺序
## 1. 基础算法
1. 快速排序 quick_sort
2. 归并排序 merge_sort
3. 二分搜索 bsearch
4. 浮点数二分搜索 float_bsearch
5. 高精度加法 bigAdd
6. 高精度减法 bigSub
7. 高精度乘法 bigMul
8. 高精度除法 bigDiv
   1. 注意上述四个高精度运算，均必须保证输入为非负整数
9.  前缀和算法 qianzhuihe
10. 二维前缀和算法 qianzhuihe_2d
11. 差分算法 chafen
12. 二维差分算法 chafen_2d
13. 双重指针算法 doublePtr / doublePtr_2
14. 位运算算法 bitFuc 

## 2. 数据结构
1. 单链表 singleLink_list
2. 双链表 doubleLink_list
3. 栈与队列
4. trie树
5. 并查集
6. 堆
7. hash表
8. C++ stl


## 3. kmp算法
kmp算法代码 在src目录下

## 4. 搜索与图论
1. DFS 深度优先搜索
2. BFS 宽度优先搜索
3. 树与图的存储
4. 树与图的深度优先遍历
5. 树与图的宽度优先遍历
6. 拓扑排序

# 输入输出操作tips
对于要连续输入的数据，假设要输入n个数，则连续读入的代码如下：
```
cin >> n;

for (int i = 0; i < n; i++)
{
   读入到具体的数组(可以是a[N]， 也可以是vector)
   a[N]建议用scanf读入
   vector可以用int x, cin >> x, vector.push_back(x)
   scanf比cin、cout快很多
   实际上，当输入数据量超过10万(1e5)的时候(这里数据量是指scanf这种输入操作的次数)，就推荐用scanf了，用cin很慢
}

```

对于查询、循环次数，假设输入为m，即m次查询。
则处理查询次数的代码如下：
```
cin >> m;
while (m--)
{
   具体处理查询，调用算法的代码
}
```

## 补充tips：什么时候字符数组不使用第0位，从1开始。
1. 只要公式有 x-1、区间计算、前缀哈希、堆 → 全部下标 1 起步，0 号闲置做初始值。比如递推公式，常常出现 [i- 1]，因此下标从1开始,就不用处理 i - 1 < 0的问题
2. 普通字符串读取、排序、遍历数组不涉及区间公式 → 0 起步
字符串两种写法对比
```
// 写法1：哈希专用，从1开始（推荐做题）
scanf("%s", str + 1); 

// 写法2：普通字符串，从0开始
scanf("%s", str); 
```