# Assignment #C: 202505114 Mock Exam

Updated 1518 GMT+8 May 14, 2025

2025 spring, Complied by <mark>王瞿骋、生命科学学院</mark>



> **说明：**
>
> 1. **⽉考**：AC6<mark>（请改为同学的通过数）</mark> 。考试题⽬都在“题库（包括计概、数算题目）”⾥⾯，按照数字题号能找到，可以重新提交。作业中提交⾃⼰最满意版本的代码和截图。
>
> 2. **解题与记录：**
>
>    对于每一个题目，请提供其解题思路（可选），并附上使用Python或C++编写的源代码（确保已在OpenJudge， Codeforces，LeetCode等平台上获得Accepted）。请将这些信息连同显示“Accepted”的截图一起填写到下方的作业模板中。（推荐使用Typora https://typoraio.cn 进行编辑，当然你也可以选择Word。）无论题目是否已通过，请标明每个题目大致花费的时间。
>
> 3. **提交安排：**提交时，请首先上传PDF格式的文件，并将.md或.doc格式的文件作为附件上传至右侧的“作业评论”区。确保你的Canvas账户有一个清晰可见的头像，提交的文件为PDF格式，并且“作业评论”区包含上传的.md或.doc附件。
>
> 4. **延迟提交：**如果你预计无法在截止日期前提交作业，请提前告知具体原因。这有助于我们了解情况并可能为你提供适当的延期或其他帮助。 
>
> 请按照上述指导认真准备和提交作业，以保证顺利完成课程要求。



## 1. 题目

### E06364: 牛的选举

http://cs101.openjudge.cn/practice/06364/

思路：



代码：

```python
n,k=map(int,input().split())
cow=[]
for i in range(n):
    a,b=map(int,input().split())
    cow.append((a,b,i))
cow.sort(key=lambda x:x[0],reverse=True)
cow1=cow[:k]
cow1.sort(key=lambda x:x[1],reverse=True)
print(cow1[0][2]+1)
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

![image-20250515205353764](C:\Users\33107\AppData\Roaming\Typora\typora-user-images\image-20250515205353764.png)



### M04077: 出栈序列统计

http://cs101.openjudge.cn/practice/04077/

思路：

不是哥们这题我做了30min

代码：

```python
n=int(input())
ans=0

def dfs(stack,cur,num):
    global n,ans
    if len(cur)==n:
        ans+=1
        return
    if num:
        dfs(stack+[num[0]],cur,num[1:])
    if stack:
        dfs(stack[:-1],cur+[stack[-1]],num)


dfs([],[],range(1,n+1))
print(ans)
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

![image-20250515205424410](C:\Users\33107\AppData\Roaming\Typora\typora-user-images\image-20250515205424410.png)



### M05343:用队列对扑克牌排序

http://cs101.openjudge.cn/practice/05343/

思路：



代码：

```python
qa=[[] for i in range(9)]
qb=[[] for i in range(4)]
n=int(input())
s=input().split()
for i in s:
    qa[int(i[1])-1].append(i)
for i in range(9):
    print('Queue'+str(i+1)+':',sep='',end='')
    print(*qa[i])

for i in range(9):
    for j in qa[i]:
        qb[ord(j[0])-ord('A')].append(j)
for i in range(4):
    print('Queue'+chr(ord('A')+i)+':',sep='',end='')
    print(*qb[i])

ans=[]
for i in range(4):
    for j in qb[i]:
        ans.append(j)
print(*ans)
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

![image-20250515205723115](C:\Users\33107\AppData\Roaming\Typora\typora-user-images\image-20250515205723115.png)



### M04084: 拓扑排序

http://cs101.openjudge.cn/practice/04084/

思路：



代码：

```python
class Vertex:
    def __init__(self, val):
        self.val = val
        self.prev = set()
        self.next = set()

class Graph:
    def __init__(self):
        self.vertices = {}

g=Graph()
b,a=map(int,input().split())
for i in range(b):
    g.vertices[i+1]=Vertex(i+1)
for i in range(a):
    u,v=map(int,input().split())
    g.vertices[v].prev.add(g.vertices[u])
    g.vertices[u].next.add(g.vertices[v])

ans=[]
l=[i for i in range(1,b+1)]
while l:
    for vertex in l:
        if not g.vertices[vertex].prev:
            ans.append('v'+str(g.vertices[vertex].val))
            for next_vertex in g.vertices[vertex].next:
                g.vertices[next_vertex.val].prev.remove(g.vertices[vertex])
            del g.vertices[vertex]
            l.pop(l.index(vertex))
            break
print(*ans)
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

![image-20250515205751124](C:\Users\33107\AppData\Roaming\Typora\typora-user-images\image-20250515205751124.png)



### M07735:道路

Dijkstra, http://cs101.openjudge.cn/practice/07735/

思路：



代码：

```python
import heapq
from collections import deque
class Vertex:
    def __init__(self, val):
        self.val = val
        self.neighbors = []

class Graph:
    def __init__(self):
        self.vertices = {}

k=int(input()) #可接受路费
n=int(input()) #城市数
r=int(input()) #道路数

g = Graph()
for i in range(1,n+1):
    g.vertices[i] = Vertex(i)

for _ in range(r):
    s,d,l,t=map(int,input().split())
    g.vertices[s].neighbors.append((d,l,t))

queue=[[0,0,1,{1}]] # [distance,cost,current_city,visited]
heapq.heapify(queue)

while queue:
    dist,cost,cur,visited=heapq.heappop(queue)
    if cost>k:
        continue
    if cur==n:
        print(dist)
        break
    for neighbor,length,spend in g.vertices[cur].neighbors:
        if neighbor not in visited:
            new_dist=dist+length
            new_cost=cost+spend
            new_visited=visited.union({neighbor})
            heapq.heappush(queue,[new_dist,new_cost,neighbor,new_visited])
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

![image-20250515205826589](C:\Users\33107\AppData\Roaming\Typora\typora-user-images\image-20250515205826589.png)



### T24637:宝藏二叉树

dp, http://cs101.openjudge.cn/practice/24637/

思路：



代码：

```python
class TreeNode:
    def __init__(self, val):
        self.val = val
        self.left = None
        self.right = None

n=int(input())
arr=[int(x) for x in input().split()]
root=TreeNode(arr[0])
tree={1:root}
for i in range(2,n+1):
    node=TreeNode(arr[i-1])
    tree[i]=node
    if i%2==0:
        tree[i//2].left=node
    else:
        tree[i//2].right=node

def dfs(node,use):
    if not node:
        return 0
    if use:
        return max(node.val+dfs(node.left,0)+dfs(node.right,0),dfs(node.left,1)+dfs(node.right,1))
    else:
        return dfs(node.left,1)+dfs(node.right,1)

print(dfs(root,1))
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

![image-20250515205849378](C:\Users\33107\AppData\Roaming\Typora\typora-user-images\image-20250515205849378.png)



## 2. 学习总结和收获

<mark>如果发现作业题目相对简单，有否寻找额外的练习题目，如“数算2025spring每日选做”、LeetCode、Codeforces、洛谷等网站上的题目。</mark>

周三上机课没去，周四晚上做的，中间还暂离了几分钟，最后时间加起来也差不多2h，算ak吧。手感不错，好几题都一遍ac。

出栈序列那题之前一直写不对（dfs的思路没想清楚），都是先存储全排列然后筛选的，但是这次n=15的估计会超时，就想着不管时间了先硬做出来，后来发现题目下面有给很明显的思路就写出来了，花了半个小时……不过3、4、6题都很快ac了，最后剩了半个多小时做第5题。

第5题其实是没多难的dijstra，但是最开始先用dfs超时，然后想怎么既限制路费又找最短路径想了半天，后来发现dijstra本身和dp不一样，没有分解子问题，每条路径都是单独考虑不会互相干扰，路费只要做一个判断就行，然后就很快写出来了。









