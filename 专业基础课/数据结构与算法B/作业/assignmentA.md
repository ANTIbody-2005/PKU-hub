# Assignment #A: Graph starts

Updated 1830 GMT+8 Apr 22, 2025

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

### M19943:图的拉普拉斯矩阵

OOP, implementation, http://cs101.openjudge.cn/practice/19943/

要求创建Graph, Vertex两个类，建图实现。

思路：



代码：

```python
class Vertex:
    def __init__(self, key):
        self.key = key
        self.connectedTo = {}

class Graph:
    def __init__(self):
        self.vertices = {}
        self.numVertices = 0

    def addVertex(self, key):
        self.numVertices += 1
        newVertex = Vertex(key)
        self.vertices[key] = newVertex

def laplacian(g):
    n=g.numVertices
    laplace=[[0 for j in range(n)] for i in range(n)]
    for i in range(n):
        for j in range(n):
            if i==j:
                laplace[i][j]=len(g.vertices[i].connectedTo)
            else:
                if i in g.vertices[j].connectedTo:
                    laplace[i][j]=-1
    for i in laplace:
        print(*i)

n,m=map(int,input().split())
g=Graph()
for i in range(n):
    g.addVertex(i)
for i in range(m):
    u,v=map(int,input().split())
    g.vertices[u].connectedTo[v]=1
    g.vertices[v].connectedTo[u]=1
laplacian(g)
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

![image-20250428125109413](C:\Users\33107\AppData\Roaming\Typora\typora-user-images\image-20250428125109413.png)



### LC78.子集

backtracking, https://leetcode.cn/problems/subsets/

思路：



代码：

```python
class Solution:
    def subsets(self, nums: List[int]) -> List[List[int]]:
        visited=[True]*len(nums)
        ans=[]
        def dfs(cur_list,loc):
            ans.append(cur_list)
            for i in range(loc,len(visited)):
                if visited[i]:
                    visited[i]=False
                    dfs(cur_list+[nums[i]],i)
                    visited[i]=True
        dfs([],0)
        return ans
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

![image-20250428125327787](C:\Users\33107\AppData\Roaming\Typora\typora-user-images\image-20250428125327787.png)



### LC17.电话号码的字母组合

hash table, backtracking, https://leetcode.cn/problems/letter-combinations-of-a-phone-number/

思路：



代码：

```python
class Solution:
    def letterCombinations(self, digits: str) -> List[str]:
        redic=['','','abc','def','ghi','jkl','mno','pqrs','tuv','wxyz']
        ans=[]
        def dfs(d,s):
            if d==len(digits):
                if s:
                    ans.append(s)
                return
            for i in redic[int(digits[d])]:
                dfs(d+1,s+i)
        dfs(0,'')
        return ans
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

![image-20250428130701973](C:\Users\33107\AppData\Roaming\Typora\typora-user-images\image-20250428130701973.png)



### M04089:电话号码

trie, http://cs101.openjudge.cn/practice/04089/

思路：



代码：

```python
class TreeNode:
    def __init__(self, val):
        self.val = val
        self.children = [0]*10
        self.tail=False

def check(nums):
    root = TreeNode(0)
    for s in nums:
        curr = root
        for c in s:
            if curr.tail:
                return 'NO'
            if not curr.children[int(c)]:
                curr.children[int(c)] = TreeNode(int(c))
            curr = curr.children[int(c)]
        if curr.tail:
            return 'NO'
        for i in curr.children:
            if i:
                return 'NO'
        curr.tail=True
    return 'YES'


t=int(input())
for _ in range(t):
    n=int(input())
    nums=[]
    for i in range(n):
        nums.append(input())
    print(check(nums))
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

![image-20250428133708700](C:\Users\33107\AppData\Roaming\Typora\typora-user-images\image-20250428133708700.png)



### T28046:词梯

bfs, http://cs101.openjudge.cn/practice/28046/

思路：



代码：

```python
from collections import deque
class Vertex:
    def __init__(self, key):
        self.key = key
        self.connectedTo = {}

class Graph:
    def __init__(self):
        self.vertices = {}

    def addVertex(self, key):
        chrs=['abcdefghijklmnopqrstuvwxyz','ABCDEFGHIJKLMNOPQRSTUVWXYZ']
        chr_count=0
        if key[0]>='A' and key[0]<='Z':
            chr_count=1
        self.vertices[key] = Vertex(key)
        for i in range(4):
            for c in chrs[chr_count]:
                if c!= key[i]:
                    neighbor_word = key[:i]+c+key[i+1:]
                    if neighbor_word in self.vertices:
                        self.vertices[key].connectedTo[neighbor_word] = self.vertices[neighbor_word]
                        self.vertices[neighbor_word].connectedTo[key] = self.vertices[key]

n=int(input())
g=Graph()
for _ in range(n):
    word=input()
    g.addVertex(word)
start,end=input().split()
visited={}
for i in g.vertices:
    visited[i]=False
q=deque([[start,[start]]])
while q:
    vertex,path=q.popleft()
    if vertex==end:
        print(*path)
        break
    visited[vertex]=True
    for neighbor in g.vertices[vertex].connectedTo:
        if not visited[neighbor]:
            q.append([neighbor,path+[neighbor]])
else:
    print("NO")
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

![image-20250428141013989](C:\Users\33107\AppData\Roaming\Typora\typora-user-images\image-20250428141013989.png)



### T51.N皇后

backtracking, https://leetcode.cn/problems/n-queens/

思路：

为什么同样是O(N!)我比别人慢这么多……

代码：

```python
class Solution:
    def solveNQueens(self, n: int) -> List[List[str]]:
        ans=[]
        def check(x,y,board):
            nonlocal n
            for i in range(n):
                if board[i][y]=='Q' and i!=x:
                    return False
            for dx,dy in [(-1,1),(-1,-1)]:
                nx,ny=x+dx,y+dy
                while 0<=nx<n and 0<=ny<n:
                    if board[nx][ny]=='Q':
                        return False
                    nx+=dx
                    ny+=dy
            return True

        def dfs(line,board):
            nonlocal n
            if line==n:
                ans.append(board.copy())
            for i in range(n):
                if check(line,i,board):
                    board[line]=board[line][:i]+'Q'+board[line][i+1:]
                    dfs(line+1,board)
                    board[line]='.'*n
        dfs(0,['.'*n for i in range(n)])
        return ans
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

![image-20250428143748759](C:\Users\33107\AppData\Roaming\Typora\typora-user-images\image-20250428143748759.png)



## 2. 学习总结和收获

<mark>如果发现作业题目相对简单，有否寻找额外的练习题目，如“数算2025spring每日选做”、LeetCode、Codeforces、洛谷等网站上的题目。</mark>

怎么都讲到图了……不过上手做题感觉还行，只是图本身还算简单（毕竟链表、树和图都差不多，只是互相接来接去，然后整个字典索引到各个节点），不知道会不会又像树一样有一堆定义和算法需要熟悉。

每日选做还在补，树的内容是真有点麻烦，做得快也要个一二十分钟，不过大多数时间是找思路和敲代码，写到一半还容易忘记接下来要怎么写，debug倒是不会花太多时间。









