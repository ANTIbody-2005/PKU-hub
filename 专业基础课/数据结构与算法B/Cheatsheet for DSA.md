# Cheatsheet for DSA 2025 Spring

生命科学学院 王瞿骋 2300012260



# 一. 算法



## 1. 二分查找

手搓模版

```python
left, right = 0, float('inf')

# 低于阈值可以，高于阈值不行
while left < right :
    mid = ( left + right + 1 ) // 2
    if check(mid):
        left = mid
    else:
        right = mid - 1
print(left)

# 高于阈值可以，低于阈值不行
while left < right :
    mid = ( left + right ) // 2
    if check(mid):
        right = mid
    else:
        left = mid + 1
print(left)
```



现成模块

```python
# 要求lst是有序数组
import bisect
bisect.bisect_left(lst,x)
# 使用bisect_left查找插入点，若x∈lst，返回最左侧x的索引；否则返回最左侧的使x若插入后能位于其左侧的元素的当前索引。
bisect.bisect_right(lst,x)
# 使用bisect_right查找插入点，若x∈lst，返回最右侧x的索引；否则返回最右侧的使x若插入后能位于其右侧的元素的当前索引。
bisect.insort(lst,x)
# 使用insort插入元素，返回插入后的lst
```



## 2. 排序

### (1)快速排序

主体模版

```python
def sort(nums: list[int], left: int, right: int):    #sort(nums, 0, len(nums)-1)
    if left >= right:
        return
    # ****** 前序位置 ******
    # 对 nums[left..right] 进行切分，将 nums[p] 排好序
    # 使得 nums[left..p-1] <= nums[p] < nums[p+1..right]
    p = partition(nums, left, right)

    # 去左右子数组进行切分
    sort(nums, left, p - 1)
    sort(nums, p + 1, right)
```

子问题实现

```python
def partition(nums, left, right):
    base = nums[left]
    while left < right :
        while left < right and nums[right] >= base :
            right -= 1
        nums[left] = nums[right]
        while left < right and nums[left] <= base :
            left += 1
        nums[right] = nums[left]
    nums[left] = base
    return left
```



### (2)归并排序

主体模版

```python
def sort(nums: list[int], left: int, right: int) -> None:    #sort(nums, 0, len(nums)-1)
    if left == right:
        return
    mid = (left + right) // 2
    # 利用定义，排序 nums[left..mid]
    sort(nums, left, mid)
    # 利用定义，排序 nums[mid+1..hi]
    sort(nums, mid + 1, right)

    # ****** 后序位置 ******
    # 此时两部分子数组已经被排好序
    # 合并两个有序数组，使 nums[left..hi] 有序
    merge(nums, left, mid, right)
```

子问题实现

```python
def merge(nums, left, mid, right):
    l = nums[left:mid+1]
    r = nums[mid+1:right+1]
    i = j = 0               #i,j分别为l,r的指针
    k = left                #k为排序后数组指针
    while i < len(l) and j < len(r):
        if l[i] <= r[j]:
            nums[k] = l[i]
            i += 1
            k +=1
        else:               # 每一次该情况对应一个逆序对(i<j但nums[i]>nums[j]) 
            nums[k] = r[j]
            j += 1
            k += 1
    while i < len(l):
        nums[k] = l[i]
        i += 1
        k += 1
    while j < len(r):
        nums[k] = r[j]
        j += 1
        k += 1
```



## 3. KMP算法

**Knuth-Morris-Pratt 算法**（简称 **KMP 算法**）是一种字符串查找算法。该算法通过观察到这样一个关键点来**查找主文本字符串 `S` 中是否存在一个“单词”或子字符串 `W`**：当发生字符不匹配时，单词 `W` 本身已经包含了足够的信息，可以确定下一次可能的匹配位置，从而跳过对先前已匹配字符的重复检查。

- 该算法会在模式串中寻找被称为 **LPS**（Longest Prefix which is also Suffix，**最长前缀后缀**，对模式串 `pattern` 的每个前缀子串，记录它的“最长相等前后缀”的长度）的重复子串，并将这些 LPS 信息存储在一个数组中
- 基于dp和双指针

```python
# 计算LPS表
def compute_lps(pattern):
    m = len(pattern)
    lps = [0] * m  # 初始化lps数组
    length = 0  # 当前最长前后缀长度
    for i in range(1, m):  # 注意i从1开始，lps[0]永远是0
        while length > 0 and pattern[i] != pattern[length]:  # 前后缀不能延伸，回退到上一个有效前后缀长度
            length = lps[length - 1]  
        if pattern[i] == pattern[length]:  #前后缀能延伸，将现有 length + 1
            length += 1
        lps[i] = length  # 记录 i 位的最长前后缀长度
    return lps

def kmp_search(text, pattern):
    n = len(text)
    m = len(pattern)
    if m == 0:
        return 0
    lps = compute_lps(pattern)
    matches = []

    # 在 text 中查找 pattern
    j = 0  # 模式串指针
    for i in range(n):  # 主串指针
        while j > 0 and text[i] != pattern[j]:  # 匹配部分不能延伸，模式串指针回退
            j = lps[j - 1]  
        if text[i] == pattern[j]:  # 匹配部分能延伸，模式串指针 + 1
            j += 1
        if j == m:  # 匹配部分长度 = 模式串长度，匹配成功，记录该匹配开头在主串的位置
            matches.append(i - j + 1)  
            j = lps[j - 1]  # 查找下一个匹配
    return matches


text = "ABABABABCABABABABCABABABABC"  #主串
pattern = "ABABCABAB"                 #模式串
index = kmp_search(text, pattern)
print("pos matched：", index)
# pos matched： [4, 13]

```



**LPS数组的周期性质**

对于某一字符串 `S[1∼i]`，在它的 `lps[i]` 的候选值中，若存在某一 `lps[i]` 使得：`i mod ( i − lps[i] ) = 0`

那么：

- `S [1:i−lps[i]]` 是 `S[1:i]` 的**最小循环元**（最小周期子串）；
- `K = i/(i-lps[i])`是这个循环元在 `S[1∼i]` 中出现的次数。

注意这个i是从1开始的，写代码通常从0开始



## 4. 素数筛——欧拉筛

```python
n = 1000  # 寻找n以内的素数
prime = []
is_prime = [1]*(n+1)
is_prime[1] = 0
for i in range(2, n+1):
	if is_prime[i]:
		prime.append(i)
	for j in prime:
		if i * j > n:
			break
		is_prime[i * j] = 0
		if i % j == 0:
			break
```



## 5. 牛顿法方程求解

**04140:方程求解**

求下面方程的根：`f(x) = x3- 5x2+ 10x - 80 = 0`，精确到小数点后9位。

```python
def f(a):
    return a**3-5*a**2+10*a-80
def f1(a):    # f(x)的导函数
    return 3*a**2-10*a+10

x=6.0
pre_x=0.0
while round(x-pre_x, 10):  #精度控制，或者循环足够次数即可
    pre_x = x
    x = x - f(x)/f1(x)
print("%.9f" %x)
```



## 6. 双指针

**11.盛最多水的容器**    https://leetcode.cn/problems/container-with-most-water/

给定一个长度为 `n` 的整数数组 `height` 。有 `n` 条垂线，第 `i` 条线的两个端点是 `(i, 0)` 和 `(i, height[i])` 。

找出其中的两条线，使得它们与 `x` 轴共同构成的容器可以容纳最多的水。

返回容器可以储存的最大水量。

```python
class Solution:
    def maxArea(self, height: List[int]) -> int:
        ans=0
        left, right = 0,len(height) - 1
        while left < right:
            ans=max(ans, (right- left) * min(height[left], height[right]))
            # 哪边低移动哪边指针
            if height[left] <= height[right]:
                left += 1
            else:
                right -= 1
        return ans
```



## 7. 差分数组

差分数组/区间重叠/扫描线算法（sweep line）

差分数组是一种辅助数据结构，用于高效处理数组的**区间更新操作**。

给定原数组 `A[0..n-1]`，其差分数组 `D[0..n]` 定义为：

- `D[0] = A[0]`
- `D[i] = A[i] - A[i-1]`（对于 `1 ≤ i < n`）
- `D[n] = 0`（哨兵值）

**区间更新高效性**：

对原数组区间 `[l, r]` 增加常数 `c` 只需修改差分数组两个值：

```python
D[l] += c
D[r+1] -= c  # 若 r+1 超出范围则忽略
```

时间复杂度：O(1)（相比直接修改原数组的 O(n)）

**前缀和还原**：

对差分数组求前缀和即可得到原数组：

```python
A[0] = D[0]
A[i] = A[i-1] + D[i]  # 对于 i > 0
```



**3362.零数组变换 III**

给你一个长度为 `n` 的整数数组 `nums` 和一个二维数组 `queries` ，其中 `queries[i] = [li, ri]` 。

每一个 `queries[i]` 表示对于 `nums` 的以下操作：

- 将 `nums` 中下标在范围 `[li, ri]` 之间的每一个元素 最多 减少 1 。
- 坐标范围内每一个元素减少的值相互 独立 。

零数组 指的是一个数组里所有元素都等于 0 。

请你返回 最多 可以从 `queries` 中删除多少个元素，使得 `queries` 中剩下的元素仍然能将 `nums` 变为一个 零数组 。如果无法将 `nums` 变为一个 零数组 ，返回 -1 。

```python
class Solution:
    def maxRemoval(self, nums: List[int], queries: List[List[int]]) -> int:
        ans = len(queries)
        n = len(nums)
        index_q = [[] for _ in range(n)]
        for l, r in queries:
            index_q[l].append(r)
        in_use = []
        pre = [0] * (n + 1)
        presum = [0] * n
        for i in range(n):
            presum[i] = presum[i - 1] + pre[i]
            for r in index_q[i]:
                heappush(in_use, -r)
            # print(presum,pre,in_use)
            while in_use and presum[i] < nums[i]:
                r = -heappop(in_use)
                if r < i:
                    return -1
                presum[i] += 1
                pre[r + 1] -= 1
                ans -= 1
            if presum[i] < nums[i]:
                return -1
        return ans

```



## 8. 全排列

现成模块

```python
from itertools import permutations,combinations
l = [1,2,3]
print(list(permutations(l))) # 输出：[(1, 2, 3), (1, 3, 2), (2, 1, 3), (2, 3, 1), (3, 1, 2), (3, 2, 1)]
print(list(combinations(l,2))) # 输出：[(1, 2), (1, 3), (2, 3)]
```



## 9. Tricks

**zip** 拆分多个数据结构，按相同索引重组成元组，长度为其中最短数据结构的长度

```python
a=[1,2,3]
b=['a','b','c']
print(list(zip(a,b)))   # Output: [(1, 'a'), (2, 'b'), (3, 'c')]
```



**enumerate**  返回索引和元素本身的数组

```python
a=['a','b','c']
print(list(enumerate(a)))   # Output: [(0, 'a'), (1, 'b'), (2, 'c')]
```



**\* **   将数据结构解包成多个参数传递到函数中（不能用于赋值，只能作为参数传递）

```python
def f(x, y, z):
    return x * y * z
a=[1, 2, 3]
print(*a)      # Output: 1 2 3
print(f(*a))   # Output: 6
```



**lru_cache**

```python
from functools import lru_cache
@lru_cache(maxsize=None, typed=False)
def f():
    return
```



**setrecurtionlimit**

```python
import sys
# 查看当前递归限制
print("当前递归限制:", sys.getrecursionlimit())
# 设置新的递归限制
sys.setrecursionlimit(2000)
```



**浮点位数控制**（四舍五入）

```python
# 保留5位
print(round(x,5))
print("%.5f" %x)
```



# 二. 数据结构



## 1. 栈

### (1)括号表达式展开

- 求出括号内的值后，将其压入栈

**20140:今日化学论文**

把连续的x个字符串s记为[xs]，输入由小写英文字母、数字和[]组成的字符串，输出原始的字符串。 样例：输入`[2b[3a]c]`，输出`baaacbaaac`

```python
s = input()
stack = []
for i in range(len(s)):
    stack.append(s[i])
    if stack[-1] == '[':
        stack.pop()
        helpstack = [] # 利用辅助栈求括号内的原始字符串，记得每次用前要清空
        while stack[-1] != '[':
            helpstack.append(stack.pop())
        stack.pop()
        numstr = ''
        while helpstack[-1] in '0123456789':
            numstr += str(helpstack.pop())
        helpstack = helpstack*int(numstr)
        while helpstack != []:
            stack.append(helpstack.pop())
print(''.join(stack))
```



### (2)算数表达式

- **前缀**表达式（波兰式），如`(- (+ 3 (* 2 4)) 1)`，Lisp语言就是使用的这种表示方法
- **中缀**表达式，如`3+2*4-1`，最适合人阅读的表示方法
- **后缀**表达式（逆波兰式），如`3 2 4 * + 1 -`，计算机处理起来比较方便

计算**后缀表达式**很简单，只需要维护一个**栈**，让数字依次进栈，遇到运算符时，就弹出栈顶两个元素，将计算结果入栈（和括号表达式展开类似）

表达式树和三种算数表达式：见[表达式树](#(4) 表达式树 (解析树))



### (3)中缀表达式转后/前缀表达式——调度场算法

核心：**栈顶**的运算符可以被弹出的条件是其**优先级不低于新读入的运算符**。当然，当表达式结束时，也要把栈里剩余的运算符依次弹出。

注意后缀表达式不会出现括号。

- 初始化运算符栈（stack）和输出栈（ans）为空
- 从左到右遍历中缀表达式的每个符号
  - 如果是数字，则将其加入ans
  - 如果是'('，则将其推入运算符栈
  - 如果是运算符：
    - 如果stack为空，直接将当前运算符推入stack
    - 如果运算符的优先级大于stack[-1]，或者stack[-1]=='('，则将当前运算符推入stack（先用字典定义优先级：pre={'+':1,'-':1,'*':2,'/':2},可以将 '(' 的优先级视为0)
    - 否则，将stack.pop()添加到ans中，直到满足上述条件（或者stack为空），再将当前运算符推入stack
  - 如果是')'，则将stack.pop()添加到ans中，直到遇到'('，将'('弹出但不添加到ans中
- 如果还有剩余的运算符在stack中，将它们依次弹出并添加到ans中
- ans中的元素就是转换后的后缀表达式

```python
pre={'(':0,'+':1,'-':1,'*':2,'/':2}
def in_to_post(lst):    # lst: 中缀表达式
	stack=[]
	ans=[]
	for i in lst:
    	if i.isdigit():
        	ans.append(i)
    	elif i=='(':
        	stack.append(i)
    	elif i==')':
        	while stack[-1]!='(':
            	ans.append(stack.pop())
        	stack.pop()
    	else:
        	while stack and pre[i]<=pre[stack[-1]]:
            	ans.append(stack.pop())
        	stack.append(i)
	while stack:
    	ans.append(stack.pop())
    return ans
```



中缀表达式转换到前缀表达的方法和转换到后缀表达式过程一致，细节上有所变化

- 初始化运算符栈（stack）和输出栈（ans）为空

- **从右到左**遍历中缀表达式的每个符号

  - 如果是数字，则将其加入ans
  - 如果是**')'**，则将其推入运算符栈
  - 如果是运算符：
    - 如果stack为空，直接将当前运算符推入stack
    - 如果运算符的优先级大于stack[-1]，或者stack[-1]==**')'**，则将当前运算符推入stack（先用字典定义优先级：pre={'+':1,'-':1,'*':2,'/':2},可以将 **')'** 的优先级视为0)
    - 否则，将stack.pop()添加到ans中，直到满足上述条件（或者stack为空），再将当前运算符推入stack
  - 如果是**'('**，则将stack.pop()添加到ans中，直到遇到**')'**，将')'弹出但不添加到ans中

- 如果还有剩余的运算符在stack中，将它们依次弹出并添加到ans中

- ans**逆序输出**就是转换后的前缀表达式

  

### (4)前/后缀表达式转中缀表达式——建立表达式二叉树再中序遍历

见[表达式树](#(4) 表达式树 (解析树))



### (5)单调栈 (Monotone Stack)

- 栈内元素保持单调递增/递减的顺序
- 主要用途是寻找序列中某个元素左侧/右侧第一个比它大/小的元素

**28203: 下一个更大元素**

给出项数为n的整数数列a1...an，定义函数f(i)代表数列中第i个元素之后第一个大于ai的元素的下标；若不存在，则f(i)=0；试求出f(1)...f(n)

- 构建单调递减栈

```python
n = int(input())
a = list(map(int,input().split()))
stack = []
for i in range(n):
    while stack and a[stack[-1]] < a[i]: # 注意pop前要检查栈是否非空
        a[stack.pop()] = i + 1 # 原地修改，较为简洁
    stack.append(i) # stack存元素下标而非元素本身
for x in stack:
    a[x] = 0
print(*a)
```



**84. 柱状图中的最大矩形**       [84. 柱状图中最大的矩形 - 力扣（LeetCode）](https://leetcode.cn/problems/largest-rectangle-in-histogram/description/)

给定 *n* 个非负整数，用来表示柱状图中各个柱子的高度。每个柱子彼此相邻，且宽度为 1 。

求在该柱状图中，能够勾勒出来的矩形的最大面积。

- 相当于寻找**下一个更小元素**，构建单调递增栈

```python
def largestRectangleArea(heights):
    heights.append(0)
    stack = [-1]
    ans = 0
    for i in range(len(heights)):
        while len(stack) > 1 and heights[i] < heights[stack[-1]]:
            x = stack.pop()
            ans = max(ans, heights[x] * (i - stack[-1] - 1))
        stack.append(i)
    return ans
```



### (6)栈dfs

**04077:出栈序列统计**

输出1-n可能的出栈序列

```python
n=int(input())
ans=[]
def dfs(stack,cur,num):
    global n
    if len(cur)==n:
        ans.append(cur)
        return
    if num:
        dfs(stack+[num[0]],cur,num[1:])
    if stack:
        dfs(stack[:-1],cur+[stack[-1]],num)
dfs([],[],range(1,n+1))
ans.reverse()         #栈dfs下结果是倒序
print(ans)
```



#### 卡特兰数（Catalan Number）

- 对于给定的 **n 个元素的合法的出栈序列总数**等于第 n 个卡特兰数

卡特兰数递推计算：

`f(0) = 1, f(1) = 1, f(n) = f(0) * f(n-1) + f(1) * f(n-2) + ... + f(n-1) * f(0)`

```python
def catalan_iterative(n):
    catalan = [0] * (n + 1)
    catalan[0] = 1  # 初始值

    for i in range(1, n + 1):  # 计算catalan[i]
        for j in range(i):    # 分割点j
            catalan[i] += catalan[j] * catalan[i - j - 1]
    return catalan[n]

# 示例：计算第5个卡特兰数
print(catalan_iterative(5))  # 输出 42
```





## 2. 链表

### (1)常见问题

反转链表

检测环

删除元素



## 3. 树

### (1) 相关概念

- **节点的度（Degree）**：一个节点含有的子树数量
- **叶节点（Leaf Node）**：度为0的节点，即没有子节点的节点
- **根节点（Root Node）**：没有父节点的节点
- **路径（Path）**：从一个节点到另一个节点的节点序列
- **层（Level）**：根节点定义为第1层，其子节点为第2层，以此类推
- **深度（Depth）**：从根节点到指定节点的唯一路径的长度
- **高度（Height）**：从指定节点到叶节点的最长路径的长度



**特殊二叉树**

- **斜树**：所有的结点都只有左子树的二叉树叫左斜树。所有结点都是只有右子树的二叉树叫右斜树
- **完全二叉树**：高度为h、有n个结点的二叉树，当且仅当其每个结点都与高度为h的满二叉树中编号为1~n的结点一一对应时，称为完全二叉树；完全二叉树可以用数组（从1到n）来表示，下标为 i 的节点的父节点为i//2，左子节点为2*i，右子节点为2\*i+1**
- **二叉搜索树/二叉查找树/二叉排序树（BST）**：左子树上所有结点的值均小于根结点的值;右子树上的所有结点的值均大于根结点的值;左子树和右子树又各是一棵二叉搜索树
- **平衡二叉树（BBT）**：一种特殊的二叉搜索树，其中任意节点的左右子树高度差不超过1，AVL树是其中一种
- **[Huffman编码树](#(6) Huffman编码树)**：是一种最优前缀编码树，用于数据压缩；它根据字符出现的频率构建二叉树，使得出现频率高的字符拥有较短的编码，频率低的字符拥有较长的编码
- **[二叉堆](#(7) 二叉堆) (Binary Heap)**：一种特殊的完全二叉树数据结构，用于高效地实现**优先队列**。二叉堆可以分为两种类型：最小堆(Min Heap)和最大堆(Max Heap)



### (2) 前/中/后/层序遍历

前/中/后序遍历

```python
def preorder(root):
    if not root:
        return []
    return [root.val] + preorder(root.left) + preorder(root.right)

def inorder(root):
    if not root:
        return []
    return inorder(root.left) + [root.val] + inorder(root.right)

def postorder(root):
    if not root:
        return []
    return postorder(root.left) + postorder(root.right) + [root.val]
```

层序遍历

```python
from collections import deque

def levelorder(root):
    if not root:
        return []
    queue = deque([root])
    res = []
    while queue:
        node = queue.popleft()
        res.append(node.val)
        if node.left:
            queue.append(node.left)
        if node.right:
            queue.append(node.right)
    return res
```



### (3) 由前/后序遍历和中序遍历结果确定二叉树

中序遍历序列中，根节点的位置不确定（它在序列中间，但具体位置取决于左子树大小），而前序或后序遍历序列只给出根节点（前序的第一个元素或后序的最后一个元素），但无法直接划分左右子树。

- 前/后序遍历的第一个/最后一个节点总是根节点，在中序遍历中找到根节点，其左边为左子树，右边为右子树
- 由于同一棵树的不同遍历长度相同，根据中序变量中左右子树的长度在前/后序遍历中划分出左右子树
- 现在得到了子树的前/后序遍历和中序遍历，按前面步骤**递归**直到子树只有一个节点，即为叶节点

```python
def build_tree(preorder, inorder):
    if not preorder:
        return None
    root_val = preorder[0]
    root = TreeNode(root_val)
    mid = inorder.index(root_val)  # 也可以改用 mid = bisect.bisect_left(inorder,root_val)
    root.left = build_tree(preorder[1:mid + 1], inorder[:mid])
    root.right = build_tree(preorder[mid+1:], inorder[mid+1:])
    return root
```



### (4) 表达式树 (解析树)

是一类特殊的**二叉树**。以基本运算对象作为**叶节点**中的数据；以**运算符**作为**非叶节点**中的数据，其两棵子树是它的运算对象，子树可以是基本运算对象，也可以是复杂表达式。

- 表达式树的先根遍历：前缀表达式
- 表达式树的中根遍历：中缀表达式
- 表达式树的后根遍历：后缀表达式

- **前缀和后缀表达式可以唯一确定表达式树**，因为操作符的元数（如二元操作符需要两个操作数）定义了子树的结构，序列可以递归解析
- **中缀表达式通常不能唯一确定表达式树**，因为它依赖于运算符优先级和括号来消除歧义（如 A + B * C 可能有不同解释）



根据后缀表达式建立表达式树，算法如下：

1. 依次读取表达式；
2. 如果是操作数，则将该操作数压入栈中；

3. 如果是操作符，则弹出栈中的两个操作数，第一个弹出的操作数作为右孩子，第二个弹出的操作数作为左孩子；然后再将该操作符（现在是一个树的根节点）压入栈中。

```python
class TreeNode:
    def __init__(self, val):
        self.val = val
        self.left = None
        self.right = None
        self.level = 2    #如果表达式树还要输出成中缀表达式

pre={'(':0,'+':1,'-':1,'*':2,'/':2}
def post_to_tree(lst):  # lst: 后缀表达式
	stack=[]
	for i in lst:
    	if i.isdigit():
        	node=TreeNode(i)
        	stack.append(node)
    	else:
        	node=TreeNode(i)
        	node.right=stack.pop()
        	node.left=stack.pop()
            node.level=pre[i]    #如果表达式树还要输出成中缀表达式
        	stack.append(node)
    	return stack.pop()
```



根据表达式树输出前/后缀表达式，直接对其进行前/后序遍历即可；输出中缀表达式，在中序遍历的基础上还要考虑括号

```python
def tree_to_in(root):
    if not root:
        return []
    left = tree_to_in(root.left)
    right = tree_to_in(root.right)
    if root.left and root.left.level < root.level:
        left = ['('] + left + [')']
    if root.right and root.right.level < root.level:
        right=['('] + right + [')']
    return left + [root.val] + right
```



### (5) 二叉搜索树

左子树上所有结点的值均小于根结点的值;右子树上的所有结点的值均大于根结点的值;左子树和右子树又各是一棵二叉搜索树



**寻找二叉搜索树中第k小的元素**

基础方法(中序遍历)

```python
def kthSmallest(root, k):
    def inorder(node):
        return inorder(node.left) + [node.val] + inorder(node.right) if node else []
    return inorder(root)[k-1]
```

迭代中序遍历(最优解)

```python
def kthSmallest(root, k):
    stack = []
    curr = root
    
    while stack or curr:
        # 遍历到最左节点
        while curr:
            stack.append(curr)
            curr = curr.left
        
        # 处理当前节点
        curr = stack.pop()
        k -= 1
        if k == 0:
            return curr.val
        
        # 转向右子树
        curr = curr.right
```



**已知二叉搜索树前序遍历求后序遍历**

- 类似于已知前序中序建树



### (6) Huffman编码树

Huffman编码树是一种**最优前缀编码树**，用于数据压缩；它根据字符出现的频率构建二叉树，使得出现频率高的字符拥有较短的编码，频率低的字符拥有较长的编码

**22161: 哈夫曼编码树**

根据字符使用频率(权值)生成一棵唯一的哈夫曼编码树。生成树时需要遵循以下规则以确保唯一性：

选取最小的两个节点合并时，节点比大小的规则是:

1) 权值小的节点算小。权值相同的两个节点，字符集里最小字符小的，算小;例如 （{'c','k'},12) 和 ({'b','z'},12)，后者小。

2) 合并两个节点时，小的节点必须作为左子节点
3) 连接左子节点的边代表0,连接右子节点的边代表1

然后对输入的串进行编码或解码

```python
import heapq

class TreeNode:
    def __init__(self, char, freq):
        self.char = char    # 字符（叶子节点）
        self.freq = freq    # 频率
        self.left = None     # 左子节点
        self.right = None    # 右子节点
    
    # 定义比较规则（用于堆排序）
    def __lt__(self, other):
        return self.freq < other.freq
    
# 构建Huffman树
def build_huffman_tree(freq_dict):
    heap = []
    # 创建叶子节点并入堆
    for char, freq in freq_dict.items():
        heapq.heappush(heap, Node(char, freq))
        
    while len(heap) > 1:
        # 取出两个最小频率节点
        left = heapq.heappop(heap)
        right = heapq.heappop(heap)
        # 创建新节点（内部节点，char=None）
        merged = Node(None, left.freq + right.freq)
        merged.left = left
        merged.right = right
        # 新节点入堆
        heapq.heappush(heap, merged)
    
    return heapq.heappop(heap)  # 返回根节点

# 生成Huffman编码表
def generate_codes(root, current_code="", codes={}):
    if root is None:
        return
    
    # 叶子节点：存储字符编码
    if root.char is not None:
        codes[root.char] = current_code
        return codes
    
    # 递归遍历左子树（添加'0'）
    generate_codes(root.left, current_code + "0", codes)
    # 递归遍历右子树（添加'1'）
    generate_codes(root.right, current_code + "1", codes)
    
    return codes

# Huffman编码
def huffman_encode(text):
    if not text:
        return "", None
    
    # 统计字符频率
    freq_dict = defaultdict(int)
    for char in text:
        freq_dict[char] += 1
    
    # 构建Huffman树
    root = build_huffman_tree(freq_dict)
    # 生成编码表
    codes = generate_codes(root)  
    # 编码文本
    encoded_text = ''.join(codes[char] for char in text)
    
    return encoded_text, root

# Huffman解码
def huffman_decode(encoded_text, root):
    if not encoded_text:
        return ""
    
    decoded_text = ''
    current_node = root
    
    for bit in encoded_text:
        # 根据比特走向左/右子树
        if bit == '0':
            current_node = current_node.left
        else:
            current_node = current_node.right
        
        # 到达叶子节点
        if current_node.char is not None:
            decoded_text += current_node.char
            current_node = root  # 重置回根节点
    
    return decoded_text

# 频率字典示例
freq_dict = {'g':4, 'd':8, 'c':10, 'f':5, 'n':1}
```



### (7) 二叉堆

一种特殊的**完全二叉树**数据结构，用于高效地实现**优先队列**。二叉堆可以分为两种类型：最小堆(Min Heap)和最大堆(Max Heap)

- 最大堆：每个父节点的值 ≥ 其子节点的值
- 最小堆：每个父节点的值 ≤ 其子节点的值

极值访问：时间复杂度O(1)

插入/删除：时间复杂度O(log n)

查询任意元素：时间复杂度O(n)



实现二叉堆：由于是完全二叉树，通常用数组（0到n-1）来存储，此时父节点为(i-1)//2，左右子节点为2*i+1，2\*i+2

```python
# 实现一个最小堆
class MinHeap:
    def __init__(self):
        self.heap = []
	
    # 插入操作，插入到队尾然后上浮
    def insert(self, val):
        self.heap.append(val)
        self.heapify_up(len(self.heap)-1)
	
    # 上浮操作，与父节点比较，若小于父节点（最小堆）则交换，重复直到满足堆性质
    def heapify_up(self,i):
        if self.heap[(i-1)//2] <= self.heap[i] or i==0:
            return
        self.heap[(i-1)//2], self.heap[i] = self.heap[i], self.heap[(i-1)//2]
        self.heapify_up((i-1)//2)

    # 弹出最小值(堆顶)操作，如果仅查询直接使用self.heap[0]即可
    def extract_min(self):
        if len(self.heap) == 0:
            return None
        min_val = self.heap[0]
        
        # 交换队顶和末尾，然后弹出末尾，通过堆顶下沉来维护堆性质
        self.heap[0] = self.heap[-1]
        self.heap.pop()
        self.heapify_down(0)
        return min_val

    # 下沉操作
    def heapify_down(self,i):
        n = len(self.heap)
        
     	# 寻找子节点中较小的一个，如果没有子节点则退出
        if 2*i+1 >= n:
            return
        smallest = 2*i+1
        if 2*i+2 < n and self.heap[2*i+2] < self.heap[smallest]:
            smallest = 2*i+2
        
        # 如果父节点大于子节点，交换并重复直到满足堆性质
        if self.heap[i] > self.heap[smallest]:
            self.heap[i], self.heap[smallest] = self.heap[smallest], self.heap[i]
            self.heapify_down(smallest)
            
# 堆化
def heapify(arr):
    heap = MinHeap()
    heap.heap = arr.copy()
    # 从最后一个非叶子节点开始下沉
    for i in range(len(arr)//2-1, -1, -1):
        heap.heapify_down(i)
    return heap
```



### (8) 前缀树 (Trie)

前缀树（Trie），又称**字典树**或**单词查找树**，是一种基于树形结构的高效字符串处理数据结构;它通过共享字符串的公共前缀，减少存储空间并加速检索操作

- 根节点不存储字符，其余每个节点代表一个字符
- 从根节点到某节点的路径构成一个字符串（如 `a → b → c` 对应 `abc`）
- 子节点字符唯一，避免重复存储公共前缀

- **插入/查找**：`O(m)`（`m` 为字符串长度）
- **前缀匹配**：`O(p)`（`p` 为前缀长度）



#### **基本操作**

1. **插入（Insert）**
    逐字符遍历字符串，若子节点不存在则创建，最终标记结尾节点
2. **查找（Search）**
    逐字符匹配路径，若中途断开则返回失败，否则检查是否为完整字符串
3. **前缀匹配（Prefix Match）**
    检查是否存在以特定前缀开头的字符串（如自动补全功能）



## 4. 图

### (1) 最短路径算法

#### Floyd-Warshall算法

求解**所有节点对最短路径**的动态规划算法，可处理**负权边**（无负权环）。

- 计算所有节点对的最短路径
- 时间复杂度：O(V³)
- 空间复杂度：O(V²)
- 可处理负权边（无负权环）

```python
def floyd_warshall(graph):  # graph为二维数组形式的邻接表，不对称
	# 初始化距离矩阵
    n = len(graph)
	dist = [[float('inf')]*n for _ in range(n)]
	for i in range(n):
		dist[i][i] = 0
	for i in range(n):
		for j in range(n):
			if graph[i][j] != 0:
			dist[i][j] = graph[i][j]

	# 动态规划更新最短路径
	for k in range(n):  # 插入第k个点使之可作为途经点
		for i in range(n):
			for j in range(n):
				dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])  # 状态转移方程
	return dist
```



#### Dijkstra 算法

求解**单源最短路径**的贪心算法，适用于**非负权图**。从源点开始，逐步扩展到距离最近的节点。

- 仅适用于非负权重的图
- 时间复杂度：O((V+E)logV)（优先队列实现）
- 空间复杂度：O(V)
- 无法处理负权环

```python
import heapq

def dijkstra(graph, start):
    # 初始化距离字典
    dist = {node: float('inf') for node in graph}
    dist[start] = 0
    # 优先队列 (距离, 节点)
    heap = [(0, start)]
    
    while heap:
        cur_dist, cur_node = heapq.heappop(heap)
        # 跳过已处理的节点
        if cur_dist > dist[cur_node]:
            continue   
        # 遍历邻居
        for neighbor, weight in graph[cur_node].items():
            distance = cur_dist + weight
            # 找到更短路径
            if distance < dist[neighbor]:
                dist[neighbor] = distance
                heapq.heappush(heap, (distance, neighbor))
    return dist

# 示例图 (邻接表表示)
graph = {
    'A': {'B': 2, 'C': 5},
    'B': {'A': 2, 'D': 3, 'E': 1},
    'C': {'A': 5, 'F': 3},
    'D': {'B': 3},
    'E': {'B': 1, 'F': 4},
    'F': {'C': 3, 'E': 4}
}
```



#### Bellman-Ford 算法

求解**单源最短路径**的动态规划算法，可处理**负权边**，并能检测**负权环**。

- 可处理负权重的图
- 时间复杂度：O(VE)（V为顶点数，E为边数）
- 空间复杂度：O(V)
- 可检测负权环

```python
def bellman_ford(graph, start):
    # 初始化距离
    dist = {node: float('inf') for node in graph}
    dist[start] = 0
    
    # 松弛操作：执行V-1轮
    for _ in range(len(graph) - 1):
        for u in graph:
            for v, weight in graph[u].items():
                if dist[u] + weight < dist[v]:
                    dist[v] = dist[u] + weight
    # 检查负权环：再执行一轮
    for u in graph:
        for v, weight in graph[u].items():
            if dist[u] + weight < dist[v]:
                raise ValueError("图中存在负权环！")
    return dist

# 示例图 (含负权边)
graph = {
    'A': {'B': -1, 'C': 4},
    'B': {'C': 3, 'D': 2, 'E': 2},
    'C': {},
    'D': {'B': 1, 'C': 5},
    'E': {'D': -3}
}
```



#### SPFA算法

SPFA 是 Bellman-Ford 算法的队列优化版本，用于求解**单源最短路径问题**。它使用队列管理待松弛节点，只处理距离发生变化的节点，显著提高了效率。

- 平均时间复杂度 O(E)，远优于 Bellman-Ford 的 O(VE)
- 支持负权边并能检测负权环
- 在稀疏图上表现优异
- 仅需队列和基础数据结构
- 只处理实际需要更新的节点

```python
from collections import deque

def spfa(graph, start):
    # 初始化距离
    dist = {node: float('inf') for node in graph}
    dist[start] = 0
    
    # 使用队列代替多轮松弛
    queue = deque([start])
    # 记录节点入队次数 (用于负权环检测)
    enqueue_count = {node: 0 for node in graph}
    enqueue_count[start] = 1
    # 标记节点是否在队列中
    in_queue = {node: False for node in graph}
    in_queue[start] = True

    while queue:
        u = queue.popleft()
        in_queue[u] = False
        for v, weight in graph[u].items():
            if dist[u] + weight < dist[v]:
                dist[v] = dist[u] + weight
                # 如果节点v不在队列中，则加入队列
                if not in_queue[v]:
                    queue.append(v)
                    in_queue[v] = True
                    enqueue_count[v] += 1
                    # 负权环检测：入队次数超过节点数
                    if enqueue_count[v] > len(graph):
                        return None  # 存在负权环
    return dist

# 示例图 (含负权边)
graph = {
    'A': {'B': -1, 'C': 4},
    'B': {'C': 3, 'D': 2, 'E': 2},
    'C': {},
    'D': {'B': 1, 'C': 5},
    'E': {'D': -3}
}
```



### (2) 并查集

- 实质上也是树，元素的parent为其**父节点**，find所得元素为其所在集合（树）的**根节点**
- 有几个互不重合的集合，就有几棵独立的树

```python
parent = list(range(n+1))

# 带路径压缩的查询
def find(x):
    if parent[x] != x:
        parent[x] = find(parent[x])
    return parent[x]

for i, j in connect:  # connect为已知同属一集合的元素
    fi, fj = find(i), find(j)
    if fi != fj:
        parent[fj] = fi
```



#### 无向图判环

通过维护连通分量的集合，若某条边的两个顶点已属于同一集合，则说明添加该边会形成环。

1. 初始化每个顶点为独立集合
2. 遍历所有边：
   - 若边的两个顶点属于不同集合，合并它们
   - 若属于同一集合，说明存在环
3. 若所有边处理完后均未发现环，则图无环

```python
def find(parent, x):
    if parent[x] != x:
        parent[x] = find(parent, parent[x])  # 路径压缩
    return parent[x]

def union(parent, x, y):
    root_x = find(parent, x)
    root_y = find(parent, y)
    if root_x == root_y:
        return False  # 已在同一集合，添加边会形成环
    parent[root_y] = root_x
    return True

def has_cycle(graph, n):
    parent = list(range(n))
    for u, v in graph:
        if not union(parent, u, v):
            return True  # 存在环
    return False
```



### (3) 最小生成树 (MST)

#### Prim算法

Prim 算法是一种**贪心算法**，它从一个顶点开始，逐步扩展树，每次添加与当前树相连且权重最小的边（类似Dijkstra）

- 时间复杂度：O(E log V)（使用优先队列）
- 空间复杂度：O(V+E)
- 适用图类型：连通图（必须连通）

```python
import heapq
from collections import defaultdict

def prim(graph, start):
    mst = []  # 存储最小生成树的边
    visited = set([start])
    edges = [(weight, start, neighbor) for neighbor, weight in graph[start]]
    heapq.heapify(edges)  # 转换为最小堆
    
    while edges:
        weight, u, v = heapq.heappop(edges)
        if v not in visited:
            visited.add(v)
            mst.append((u, v, weight))
            # 将新顶点的边加入堆
            for neighbor, w in graph[v]:
                if neighbor not in visited:
                    heapq.heappush(edges, (w, v, neighbor))
    
    return mst

# 使用示例
graph = {
    'A': [('B', 2), ('D', 6)],
    'B': [('A', 2), ('C', 3), ('D', 8), ('E', 5)],
    'C': [('B', 3), ('E', 7)],
    'D': [('A', 6), ('B', 8), ('E', 9)],
    'E': [('B', 5), ('C', 7), ('D', 9)]
}
```



#### Kruskal算法

Kruskal 算法也是一种**贪心算法**，它按权重从小到大的顺序考虑所有边，如果边不会形成环，就将其加入生成树，本质就是并查集

- 时间复杂度：O(E log E)（主要来自排序）
- 空间复杂度：O(V+E)
- 适用图类型：任意无向图（即使不连通也会生成最小生成森林）

```python
class UnionFind:
    """并查集实现（用于检测环）"""
    def __init__(self, n):
        self.parent = list(range(n))
        self.rank = [0] * n
    
    def find(self, x):
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])
        return self.parent[x]
    
    def union(self, x, y):
        rootx = self.find(x)
        rooty = self.find(y)
        if rootx == rooty:
            return False
        if self.rank[rootx] < self.rank[rooty]:
            self.parent[rootx] = rooty
        elif self.rank[rootx] > self.rank[rooty]:
            self.parent[rooty] = rootx
        else:
            self.parent[rooty] = rootx
            self.rank[rootx] += 1
        return True

def kruskal(graph):
    """
    Kruskal 算法求最小生成树
    :param graph: 图的邻接表 {顶点: [(邻居, 权重), ...]}
    :return: MST 的边列表 [(u, v, weight), ...]
    """
    # 获取所有顶点并映射索引
    vertices = list(graph.keys())
    vertex_index = {v: i for i, v in enumerate(vertices)}
    
    # 收集所有边并排序
    edges = []
    for u in graph:
        for v, weight in graph[u]:
            # 避免重复添加无向边
            if (v, u, weight) not in edges:
                edges.append((u, v, weight))
    
    edges.sort(key=lambda x: x[2])  # 按权重排序
    
    uf = UnionFind(len(vertices))
    mst = []
    
    for u, v, weight in edges:
        idx_u = vertex_index[u]
        idx_v = vertex_index[v]
        # 如果加入不会形成环
        if uf.union(idx_u, idx_v):
            mst.append((u, v, weight))
            if len(mst) == len(vertices) - 1:
                break  # 树有V-1条边
    
    return mst
```



### (4) 拓扑排序 (TAG)

拓扑排序（Topological Sorting）是一个**有向无环图**（DAG, Directed Acyclic Graph）的所有顶点的线性序列。且该序列必须满足下面两个条件：

- 每个顶点出现且只出现一次。
- 若存在一条从顶点 A 到顶点 B 的路径，那么在序列中顶点 A 出现在顶点 B 的前面。



#### Kahn 算法（基于入度）

1. **计算入度**：统计每个节点的入边数量
2. **初始化队列**：将所有入度为0的节点加入队列
3. **处理队列**：
   - 取出节点加入结果
   - 减少其邻居节点的入度
   - 若邻居入度变为0，加入队列
4. **检查结果**：若结果包含所有节点，则成功；否则有环

```python
from collections import deque

def topological_sort(graph):
    # 计算入度
    in_degree = {node: 0 for node in graph}
    for node in graph:
        for neighbor in graph[node]:
            in_degree[neighbor] = in_degree.get(neighbor, 0) + 1
    
    # 初始化队列（入度为0的节点）
    queue = deque([node for node in in_degree if in_degree[node] == 0])
    result = []
    
    # 处理队列
    while queue:
        node = queue.popleft()
        result.append(node)
        
        # 减少邻居入度
        for neighbor in graph.get(node, []):
            in_degree[neighbor] -= 1
            if in_degree[neighbor] == 0:
                queue.append(neighbor)
    
    # 检查是否有环
    if len(result) == len(graph):
        return result
    else:
        return []  # 存在环

# 使用示例
graph = {
    '数据结构': ['算法分析'],
    '离散数学': ['数据结构'],
    '算法分析': ['人工智能'],
    '计算机基础': ['编程入门'],
    '编程入门': ['数据结构', '操作系统'],
    '操作系统': ['计算机网络'],
    '计算机网络': ['人工智能'],
    '人工智能': []  # 终点
}
```



#### DFS 算法（基于深度优先）

1. **执行DFS**：对图进行深度优先遍历
2. **记录完成时间**：节点完成访问时加入栈（后序遍历）
3. **逆序输出**：栈的**逆序**即为拓扑排序

```python
def topological_sort_dfs(graph):
    visited = set()
    stack = []
    cycle_detector = set()  # 用于环检测
    
    def dfs(node):
        if node in cycle_detector:
            return False  # 发现环
        if node in visited:
            return True   # 已访问，跳过
        
        visited.add(node)
        cycle_detector.add(node)
        
        for neighbor in graph.get(node, []):
            if not dfs(neighbor):
                return False
        
        stack.append(node)  # 访问完毕，加入栈，从环检测移除
        cycle_detector.remove(node)
        return True
    
    # DFS遍历所有节点
    for node in graph:
        if node not in visited:
            if not dfs(node):
                return []  # 存在环
    
    return stack[::-1]  # 反转栈
```



### (5) 强连通分量 (SCC)

#### Kosaraju算法

一种用于寻找有向图强连通分量（SCC）的高效算法，通过两次DFS实现：

1. 第一次 DFS：记录节点完成时间（后序遍历顺序）
2. 反向图：将所有边方向反转
3. 第二次 DFS：按完成时间逆序遍历反向图
4. 每个 DFS 树：就是一个强连通分量



- **时间复杂度**：O(V+E)（线性复杂度）
- **空间复杂度**：O(V+E)
- **结果准确**：能找出所有强连通分量
- **实现简单**：基于两次标准 DFS
- **限制条件**：只适用于有向图

```python
from collections import defaultdict

def kosaraju(graph):
    # 第一次 DFS：记录完成顺序
    visited, stack = set(), []
    for node in graph:
        if node not in visited:
            dfs1(node, graph, visited, stack)
    
    # 构建反向图
    reverse = defaultdict(list)
    for u in graph:
        for v in graph[u]:
            reverse[v].append(u)
    
    # 第二次 DFS：按逆序处理
    visited, sccs = set(), []
    while stack:
        node = stack.pop()
        if node not in visited:
            scc = []
            dfs2(node, reverse, visited, scc)
            sccs.append(scc)
    
    return sccs

def dfs1(node, graph, visited, stack):
    visited.add(node)
    for neighbor in graph.get(node, []):
        if neighbor not in visited:
            dfs1(neighbor, graph, visited, stack)
    stack.append(node)

def dfs2(node, graph, visited, scc):
    visited.add(node)
    scc.append(node)
    for neighbor in graph.get(node, []):
        if neighbor not in visited:
            dfs2(neighbor, graph, visited, scc)

# 使用示例
graph = {
    0: [1],
    1: [2],
    2: [0, 3],
    3: [4],
    4: [3]
}

scc = kosaraju(graph)
print("强连通分量:", scc) 
# 输出: [[4, 3], [2, 1, 0]]
```

