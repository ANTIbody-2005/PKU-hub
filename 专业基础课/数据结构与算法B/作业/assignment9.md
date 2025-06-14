# Assignment #9: Huffman, BST & Heap

Updated 1834 GMT+8 Apr 15, 2025

2025 spring, Complied by <mark>王瞿骋、生命科学学院</mark>



> **说明：**
>
> 1. **解题与记录：**
>
>    对于每一个题目，请提供其解题思路（可选），并附上使用Python或C++编写的源代码（确保已在OpenJudge， Codeforces，LeetCode等平台上获得Accepted）。请将这些信息连同显示“Accepted”的截图一起填写到下方的作业模板中。（推荐使用Typora https://typoraio.cn 进行编辑，当然你也可以选择Word。）无论题目是否已通过，请标明每个题目大致花费的时间。
>
> 2. **提交安排：**提交时，请首先上传PDF格式的文件，并将.md或.doc格式的文件作为附件上传至右侧的“作业评论”区。确保你的Canvas账户有一个清晰可见的头像，提交的文件为PDF格式，并且“作业评论”区包含上传的.md或.doc附件。
>
> 3. **延迟提交：**如果你预计无法在截止日期前提交作业，请提前告知具体原因。这有助于我们了解情况并可能为你提供适当的延期或其他帮助。 
>
> 请按照上述指导认真准备和提交作业，以保证顺利完成课程要求。



## 1. 题目

### LC222.完全二叉树的节点个数

dfs, https://leetcode.cn/problems/count-complete-tree-nodes/

思路：

用二分查找做，时间复杂度比dfs低一些

代码：

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def countNodes(self, root: Optional[TreeNode]) -> int:
        depth=0
        tmp=root
        while tmp:
            tmp=tmp.left
            depth+=1
        mi=2**(depth-1)
        ma=2**depth-1
        def check(k):
            bk=bin(k)[3:]
            node=root
            for i in bk:
                if i=='0':
                    node=node.left
                else:
                    node=node.right
            if node:
                return True
            else:
                return False
        while mi<ma:
            mid=(mi+ma)//2+1
            if check(mid):
                mi=mid
            else:
                ma=mid-1
        return ma
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

![image-20250421130148646](C:\Users\33107\AppData\Roaming\Typora\typora-user-images\image-20250421130148646.png)



### LC103.二叉树的锯齿形层序遍历

bfs, https://leetcode.cn/problems/binary-tree-zigzag-level-order-traversal/

思路：



代码：

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def zigzagLevelOrder(self, root: Optional[TreeNode]) -> List[List[int]]:
        if not root:
            return []
        ans=[]
        stack=[]
        next_stack=[root]
        while next_stack:
            ans.append([])
            stack=deque(next_stack.copy())
            next_stack.clear()
            while stack:
                node=stack.popleft()
                ans[-1].append(node.val)
                if node.left:
                    next_stack.append(node.left)
                if node.right:
                    next_stack.append(node.right)
        for i in range(1,len(ans),2):
            ans[i].reverse()
        return ans
                
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

![image-20250421131510374](C:\Users\33107\AppData\Roaming\Typora\typora-user-images\image-20250421131510374.png)



### M04080:Huffman编码树

greedy, http://cs101.openjudge.cn/practice/04080/

思路：

第一次知道了Huffman编码树

代码：

```python
import heapq
n=int(input())
a=list(map(int,input().split()))
heapq.heapify(a)
ans=sum(a)
while len(a)>2:
    x=heapq.heappop(a)
    y=heapq.heappop(a)
    ans+=x+y
    heapq.heappush(a,x+y)
print(ans)
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

![image-20250421140558412](C:\Users\33107\AppData\Roaming\Typora\typora-user-images\image-20250421140558412.png)



### M05455: 二叉搜索树的层次遍历

http://cs101.openjudge.cn/practice/05455/

思路：



代码：

```python
from collections import deque
class TreeNode:
    def __init__(self, val):
        self.val = val
        self.left = None
        self.right = None

def insert_node(num):
    global root
    if not root:
        root=TreeNode(num)
        return
    node=root
    prev=None
    while node:
        prev=node
        if node.val==num:
            return
        elif node.val>num:
            node=node.left
        else:
            node=node.right
    if prev.val>num:
        prev.left=TreeNode(num)
    else:
        prev.right=TreeNode(num)


nums=list(map(int,input().split()))
root=None
for i in nums:
    insert_node(i)

ans=[]
stack=[]
next_stack=[root]
while next_stack:
    stack=deque(next_stack.copy())
    next_stack.clear()
    while stack:
        node=stack.popleft()
        if node.left:
            next_stack.append(node.left)
        if node.right:
            next_stack.append(node.right)
        if node:
            ans.append(node.val)
print(*ans)
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

![image-20250421142612059](C:\Users\33107\AppData\Roaming\Typora\typora-user-images\image-20250421142612059.png)



### M04078: 实现堆结构

手搓实现，http://cs101.openjudge.cn/practice/04078/

类似的题目是 晴问9.7: 向下调整构建大顶堆，https://sunnywhy.com/sfbj/9/7

思路：

不显式地用二叉树来实现堆，第一次知道了父节点和子节点在索引上的关系

代码：

```python
class MinHeap:
    def __init__(self):
        self.heap = []

    def insert(self, val):
        self.heap.append(val)
        self.heapify_up(len(self.heap)-1)

    def heapify_up(self,i):
        if self.heap[(i-1)//2] <= self.heap[i] or i==0:
            return
        self.heap[(i-1)//2], self.heap[i] = self.heap[i], self.heap[(i-1)//2]
        self.heapify_up((i-1)//2)

    def extract_min(self):
        if len(self.heap) == 0:
            return None
        min_val = self.heap[0]
        self.heap[0] = self.heap[-1]
        self.heap.pop()
        self.heapify_down(0)
        return min_val

    def heapify_down(self,i):
        if 2*i+1 >= len(self.heap):
            return
        smallest = 2*i+1
        if 2*i+2 < len(self.heap) and self.heap[2*i+2] < self.heap[smallest]:
            smallest = 2*i+2
        if self.heap[i] > self.heap[smallest]:
            self.heap[i], self.heap[smallest] = self.heap[smallest], self.heap[i]
            self.heapify_down(smallest)


n=int(input())
heap = MinHeap()
for _ in range(n):
    s=input().split()
    if s[0]=='1':
        heap.insert(int(s[1]))
    else:
        print(heap.extract_min())
    #print(heap.heap)
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

![image-20250421170337941](C:\Users\33107\AppData\Roaming\Typora\typora-user-images\image-20250421170337941.png)



### T22161: 哈夫曼编码树

greedy, http://cs101.openjudge.cn/practice/22161/

思路：

已被本题打败，正在向答案学习。

代码：

```python

```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>





## 2. 学习总结和收获

<mark>如果发现作业题目相对简单，有否寻找额外的练习题目，如“数算2025spring每日选做”、LeetCode、Codeforces、洛谷等网站上的题目。</mark>

两周的真空期下来有点要跟不上了，还好期中结束了，这几周准备狂刷每日选做。

和树相关的定义不少，前中后序遍历、平衡二叉树、霍夫曼树、二叉搜索树……应该会随着做题逐渐熟悉的。

最近的题更多是在oj上的OOP题了，相比leetcode自带模版要更考验OOP基础了。









