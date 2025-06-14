# Assignment #8: 树为主

Updated 1704 GMT+8 Apr 8, 2025

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

### LC108.将有序数组转换为二叉树

dfs, https://leetcode.cn/problems/convert-sorted-array-to-binary-search-tree/

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
    def sortedArrayToBST(self, nums: List[int]) -> Optional[TreeNode]:
        def newtree(l):
            if not l:
                return None
            if len(l)==1:
                return TreeNode(l[0])
            mid=len(l)//2
            node=TreeNode(l[mid])
            node.left=newtree(l[:mid])
            node.right=newtree(l[mid+1:])
            return node
        return newtree(nums)
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

![image-20250414214925570](C:\Users\33107\AppData\Roaming\Typora\typora-user-images\image-20250414214925570.png)



### M27928:遍历树

 adjacency list, dfs, http://cs101.openjudge.cn/practice/27928/

思路：



代码：

```python
class TreeNode:
    def __init__(self,val=None):
        self.val = val
        self.next=[]

def traverse(node):
    tmp=[node.val]
    for i in node.next:
        if i:
            tmp.append(i.val)
    tmp.sort()
    ans=[]
    for i in tmp:
        if i!=node.val:
            ans+=traverse(dic[i])
        else:
            ans.append(i)
    return ans


n=int(input())
dic={}
nodes=set()
not_root=set()
for _ in range(n):
    s=list(map(int,input().split()))
    for i in s:
        if i not in nodes:
            dic[i]=TreeNode(i)
            nodes.add(i)
    if len(s)>1:
        for i in s[1:]:
            dic[s[0]].next.append(dic[i])
            not_root.add(i)
    else:
        not_root.add(s[0])

root=list(nodes-not_root)[0]
for i in traverse(dic[root]):
    print(i)
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

![image-20250414222856036](C:\Users\33107\AppData\Roaming\Typora\typora-user-images\image-20250414222856036.png)



### LC129.求根节点到叶节点数字之和

dfs, https://leetcode.cn/problems/sum-root-to-leaf-numbers/

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
    def sumNumbers(self, root: Optional[TreeNode]) -> int:
        ans=0
        def work(node,num):
            nonlocal ans
            node.val=num*10+node.val
            if not node.left and not node.right:
                ans+=node.val
                return
            if node.left:
                work(node.left,node.val)
            if node.right:
                work(node.right,node.val)
        work(root,0)
        return ans
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

![image-20250414223656518](C:\Users\33107\AppData\Roaming\Typora\typora-user-images\image-20250414223656518.png)



### M22158:根据二叉树前中序序列建树

tree, http://cs101.openjudge.cn/practice/22158/

思路：



代码：

```python

```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>





### M24729:括号嵌套树

dfs, stack, http://cs101.openjudge.cn/practice/24729/

思路：



代码：

```python
class TreeNode:
    def __init__(self,val=None):
        self.val = val
        self.next=[]

def front(tnode):
    if not tnode:
        return []
    ans=[tnode.val]
    for i in tnode.next:
        ans+=front(i)
    return ans

def back(tnode):
    if not tnode:
        return []
    ans=[]
    for i in tnode.next:
        ans+=back(i)
    ans.append(tnode.val)
    return ans

s=input()
root=TreeNode(s[0])
stack=[]
tmp=root
if len(s)>1:
    for i in s[1:]:
        if i=='(':
            stack.append(tmp)
        elif i==')':
            stack.pop()
        elif i!=',':
            node=TreeNode(i)
            stack[-1].next.append(node)
            tmp=node
print(*front(root),sep='')
print(*back(root),sep='')
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

![image-20250414225518544](C:\Users\33107\AppData\Roaming\Typora\typora-user-images\image-20250414225518544.png)



### LC3510.移除最小数对使数组有序II

doubly-linked list + heap, https://leetcode.cn/problems/minimum-pair-removal-to-sort-array-ii/

思路：



代码：

```python

```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>





## 2. 学习总结和收获

<mark>如果发现作业题目相对简单，有否寻找额外的练习题目，如“数算2025spring每日选做”、LeetCode、Codeforces、洛谷等网站上的题目。</mark>

被期中周干烂了，先做4题交掉（怎么上上周也是这样……）

树的遍历这种“正向”题猛猛写递归，就是以前搜索的思路，但是根据遍历结果等重建树这种“逆向”的题就不太熟练，可能还涉及栈之类的内容，这周所有期中考完好好研究

每日选做日渐积累，考完也要开始赎罪了









