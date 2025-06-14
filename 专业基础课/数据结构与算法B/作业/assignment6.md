# Assignment #6: 回溯、树、双向链表和哈希表

Updated 1526 GMT+8 Mar 22, 2025

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

### LC46.全排列

backtracking, https://leetcode.cn/problems/permutations/

思路：

（10min）挺经典的回溯



代码：

```python
class Solution:
    def permute(self, nums: List[int]) -> List[List[int]]:
        ans=[]
        def qpl(ind,cur):
            if len(cur)==len(nums):
                ans.append(cur)
            for i in range(len(ind)):
                if ind[i]:
                    ind[i]=0
                    qpl(ind,cur+[nums[i]])
                    ind[i]=1
        qpl([1]*len(nums),[])
        return ans
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

![image-20250331211219645](C:\Users\33107\AppData\Roaming\Typora\typora-user-images\image-20250331211219645.png)



### LC79: 单词搜索

backtracking, https://leetcode.cn/problems/word-search/

思路：

（15min）回溯，时间复杂度和空间复杂度都是O(m*n)，不知道为什么最后要慢好多



代码：

```python
class Solution:
    def exist(self, board: List[List[str]], word: str) -> bool:
        m,n=len(board),len(board[0])
        visited=set()
        def dfs(x,y,l):
            nonlocal word,m,n
            if l==len(word):
                return True
            for dx,dy in [(1,0),(0,1),(-1,0),(0,-1)]:
                nx,ny=x+dx,y+dy
                if 0<=nx<m and 0<=ny<n and board[nx][ny]==word[l] and (nx,ny) not in visited:
                    visited.add((nx,ny))
                    if dfs(nx,ny,l+1):
                        return True
                    visited.remove((nx,ny))
        for i in range(m):
            for j in range(n):
                if board[i][j]==word[0]:
                    visited.add((i,j))
                    if dfs(i,j,1):
                        return True
                    visited.remove((i,j))
        return False
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

![image-20250331212858649](C:\Users\33107\AppData\Roaming\Typora\typora-user-images\image-20250331212858649.png)



### LC94.二叉树的中序遍历

dfs, https://leetcode.cn/problems/binary-tree-inorder-traversal/

思路：

（10min）递归写法，迭代也写了



代码：

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def inorderTraversal(self, root: Optional[TreeNode]) -> List[int]:
        ans=[]
        def traversal(node):
            if not node:
                return
            if node.left:
                traversal(node.left)
            ans.append(node.val)
            if node.right:
                traversal(node.right)
        traversal(root)
        return ans
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

![image-20250331214929050](C:\Users\33107\AppData\Roaming\Typora\typora-user-images\image-20250331214929050.png)



### LC102.二叉树的层序遍历

bfs, https://leetcode.cn/problems/binary-tree-level-order-traversal/

思路：

（20min）bfs，写的比较粗糙，最后还是用了两个列表来存



代码：

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def levelOrder(self, root: Optional[TreeNode]) -> List[List[int]]:
        if not root:
            return []
        ans=[]
        cur=[root]
        lower=[]
        while cur:
            for node in cur:
                if node.left:
                    lower.append(node.left)
                if node.right:
                    lower.append(node.right)
            ans.append([i.val for i in cur])
            cur=lower.copy()
            lower.clear()
        return ans
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

![image-20250331220044137](C:\Users\33107\AppData\Roaming\Typora\typora-user-images\image-20250331220044137.png)



### LC131.分割回文串

dp, backtracking, https://leetcode.cn/problems/palindrome-partitioning/

思路：



代码：

```python

```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>





### LC146.LRU缓存

hash table, doubly-linked list, https://leetcode.cn/problems/lru-cache/

思路：



代码：

```python

```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>





## 2. 学习总结和收获

<mark>如果发现作业题目相对简单，有否寻找额外的练习题目，如“数算2025spring每日选做”、LeetCode、Codeforces、洛谷等网站上的题目。</mark>

这周摆了，作业只写了4道题，每日选做也停滞……

而且刚好这两周开始上树的内容，题做的少还是挺吃亏的。虽说本质上和链表是差不多的，但题目是OOP结合bfs/dfs算法，相比链表要复杂的多，还是要多做题熟悉写法。另一类（像LRU缓存）自己写类函数，甚至要自定义一个新类的题做起来也有不少阻碍，还是因为写法和之前完全不同了，如果再加上一些数据结构就更加吃力，好吧还是多做题。









