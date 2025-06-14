# Assignment #D: 图 & 散列表

Updated 2042 GMT+8 May 20, 2025

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

### M17975: 用二次探查法建立散列表

http://cs101.openjudge.cn/practice/17975/

<mark>需要用这样接收数据。因为输入数据可能分行了，不是题面描述的形式。OJ上面有的题目是给C++设计的，细节考虑不周全。</mark>

```python
import sys
input = sys.stdin.read
data = input().split()
index = 0
n = int(data[index])
index += 1
m = int(data[index])
index += 1
num_list = [int(i) for i in data[index:index+n]]
```



思路：

题不难，没发现关键字还能重复，无敌了……



代码：

```python
def turn(a):
    if a%2==0:
        return -((a+1)//2)**2
    else:
        return ((a+1)//2)**2

def add_to_l(num):
    global m
    x=num%m
    if num in visited:
        ans.append(visited[num])
        return
    while l[(x+turn(use[x]))%m]:
        use[x]+=1
    l[(x+turn(use[x]))%m]=1
    visited[num]=x+turn(use[x])%m
    ans.append((x+turn(use[x]))%m)

import sys
data = sys.stdin.read().split()
n = int(data[0])
m = int(data[1])
nums = [int(i) for i in data[2:2+n]]
l=[0]*m
use=[0]*m
visited=dict()
ans=[]
for i in nums:
    add_to_l(i)
print(*ans)
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

![image-20250522200305623](C:\Users\33107\AppData\Roaming\Typora\typora-user-images\image-20250522200305623.png)



### M01258: Agri-Net

MST, http://cs101.openjudge.cn/practice/01258/

思路：

怎么又多个案例可能分行啊……不认真读题导致的



代码：

```python
while True:
    try:
        n = int(input())
        l = []
        while len(l) < n * n:
            l += list(map(int, input().split()))
        cost = [(l[i * n + j], i, j) for i in range(n) for j in range(i)]
        cost.sort()
        connect = list(range(n))


        def find_father(x):
            if connect[x] == x:
                return x
            return find_father(connect[x])


        ans = 0
        for c, i, j in cost:
            fi, fj = find_father(i), find_father(j)
            if fi != fj:
                connect[fi] = fj
                ans += c
        print(ans)
    except EOFError:
        break
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

![image-20250522204734172](C:\Users\33107\AppData\Roaming\Typora\typora-user-images\image-20250522204734172.png)



### M3552.网络传送门旅游

bfs, https://leetcode.cn/problems/grid-teleportation-traversal/

思路：



代码：

```python
class Solution:
    def minMoves(self, matrix: List[str]) -> int:
        m,n=len(matrix),len(matrix[0])
        portal={}
        for i in range(26):
            portal[chr(i+ord('A'))]=set()
        for i in range(m):
            for j in range(n):
                if 'A'<=matrix[i][j]<='Z':
                    portal[matrix[i][j]].add((i,j))
        q=deque()
        q.append((0,0,0,set()))
        if 'A'<=matrix[0][0]<='Z':
            for nx,ny in portal[matrix[0][0]]-{(0,0)}:
                        q.append((nx,ny,0,{matrix[0][0]}))
        visited=[[0]*n for _ in range(m)]
        visited[0][0]=1
        while q:
            x,y,step,used=q.popleft()
            if x==m-1 and y==n-1:
                return step
            for dx,dy in [(1,0),(0,1),(-1,0),(0,-1)]:
                nx,ny=x+dx,y+dy
                if 0<=nx<m and 0<=ny<n and matrix[nx][ny]!='#' and not visited[nx][ny]:
                    if 'A'<=matrix[nx][ny]<='Z' and not matrix[nx][ny] in used:
                        used|={matrix[nx][ny]}
                        for nnx,nny in portal[matrix[nx][ny]]-{(nx,ny)}:
                            visited[nnx][nny]=1
                            q.append((nnx,nny,step+1,used))
                    visited[nx][ny]=1
                    q.append((nx,ny,step+1,used))
        return -1
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

![image-20250522204827485](C:\Users\33107\AppData\Roaming\Typora\typora-user-images\image-20250522204827485.png)



### M787.K站中转内最便宜的航班

Bellman Ford, https://leetcode.cn/problems/cheapest-flights-within-k-stops/

思路：



代码：

```python
class Solution:
    def findCheapestPrice(self, n: int, flights: List[List[int]], src: int, dst: int, k: int) -> int:
        goto=[[] for _ in range(n)]
        price=[float('inf')]*n
        for a,b,c in flights:
            goto[a].append((b,c))
        q=deque()
        q=deque([(0,0,src)])
        while q:
            step,cost,city=q.popleft()
            #print(step,cost,city)
            if step>k:
                break
            for nxt,c in goto[city]:
                if cost+c<price[nxt]:
                    price[nxt]=cost+c
                    q.append((step+1,cost+c,nxt))
        return price[dst] if price[dst]!=float('inf') else -1
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

![image-20250522204915657](C:\Users\33107\AppData\Roaming\Typora\typora-user-images\image-20250522204915657.png)



### M03424: Candies

Dijkstra, http://cs101.openjudge.cn/practice/03424/

思路：

最难的是把题目转化成Dijkstra的模型，剩下就是很经典的Dijkstra，算是第一次熟练运用吧



代码：

```python
import heapq
n,m=map(int,input().split())
l=[[] for _ in range(n+1)]
for _ in range(m):
    a,b,c=map(int,input().split())
    l[a].append((b,c))

open_list=[(0,1)]
close_list=[0]*(n+1)
min_cost=[float('inf')]*(n+1)
min_cost[1]=0
while open_list:
    cost,node=heapq.heappop(open_list)
    if node==n:
        print(min_cost[n])
        break
    for nxt,c in l[node]:
        if close_list[nxt]==0:
            new_cost=cost+c
            if new_cost<min_cost[nxt]:
                min_cost[nxt]=new_cost
                heapq.heappush(open_list,(new_cost,nxt))
    close_list[node]=1
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

![image-20250522210219008](C:\Users\33107\AppData\Roaming\Typora\typora-user-images\image-20250522210219008.png)



### M22508:最小奖金方案

topological order, http://cs101.openjudge.cn/practice/22508/

思路：



代码：

```python
from collections import deque
class Vertex:
    def __init__(self, key):
        self.key = key
        self.defeated=set()
        self.attack=set()
        self.val=0

class Graph:
    def __init__(self):
        self.vertices = {}

n,m=map(int,input().split())
g=Graph()
for i in range(n):
    g.vertices[i]=Vertex(i)
for _ in range(m):
    u,v=map(int,input().split())
    g.vertices[u].attack.add(v)
    g.vertices[v].defeated.add(u)

queue=deque()
price=[]
for v in g.vertices:
    if not g.vertices[v].attack:
        queue.append(v)
while queue:
    v=queue.popleft()
    price.append(g.vertices[v].val)
    for u in g.vertices[v].defeated:
        g.vertices[u].val=max(g.vertices[u].val,g.vertices[v].val+1)
        g.vertices[u].attack.remove(v)
        if not g.vertices[u].attack:
            queue.append(u)
print(100*n+sum(price))
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

![image-20250522210433464](C:\Users\33107\AppData\Roaming\Typora\typora-user-images\image-20250522210433464.png)



## 2. 学习总结和收获

<mark>如果发现作业题目相对简单，有否寻找额外的练习题目，如“数算2025spring每日选做”、LeetCode、Codeforces、洛谷等网站上的题目。</mark>

喜报：每日选做已跟进到目前进度

悲报：每日选做里面很多之前的作业题，ac过的就直接跳了，现在不一定能熟练做出来

上上周第一次接触Dijkstra，这周还接触了Bellman Fold，这两个算法的思路容易乱，做题的时候磨了好久，现在总算是搞的比较清楚了。并查集的题做的也多了，还接触了最小生成树，这些题都是比较容易看出来考点的，还比较好做。

剩下的一两周主要就是再系统性地复习一下知识点，把之前收藏的经典题再回顾一下，备战机考了。









