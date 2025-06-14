# Assignment #B: 图为主

Updated 2223 GMT+8 Apr 29, 2025

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

### E07218:献给阿尔吉侬的花束

bfs, http://cs101.openjudge.cn/practice/07218/

思路：



代码：

```python
from collections import deque

def find_start_end(maze):
    start=(0,0)
    end=(0,0)
    for i in range(len(maze)):
        for j in range(len(maze[0])):
            if maze[i][j]=='S':
                start=(i,j)
            elif maze[i][j]=='E':
                end=(i,j)
    return start,end

t=int(input())
for _ in range(t):
    r,c=map(int,input().split())
    maze=[input() for i in range(r)]
    start,end=find_start_end(maze)
    q=deque()
    q.append((start,0))
    visited={start}
    while q:
        curr,step=q.popleft()
        if curr==end:
            print(step)
            break
        for dx,dy in [(0,1),(0,-1),(1,0),(-1,0)]:
            x,y=curr[0]+dx,curr[1]+dy
            if 0<=x<r and 0<=y<c and maze[x][y]!='#' and (x,y) not in visited:
                visited.add((x,y))
                q.append(((x,y),step+1))
    else:
        print('oop!')
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

![image-20250506115701524](C:\Users\33107\AppData\Roaming\Typora\typora-user-images\image-20250506115701524.png)



### M3532.针对图的路径存在性查询I

disjoint set, https://leetcode.cn/problems/path-existence-queries-in-a-graph-i/

思路：



代码：

```python
class Solution:
    def pathExistenceQueries(self, n: int, nums: List[int], maxDiff: int, queries: List[List[int]]) -> List[bool]:
        nums[0]=(nums[0],nums[0])
        for i in range(1,n):
            if nums[i]-nums[i-1][0]<=maxDiff:
                nums[i]=(nums[i],nums[i-1][1])
            else:
                nums[i]=(nums[i],nums[i])
        for i in range(len(queries)):
            if nums[queries[i][0]][1]==nums[queries[i][1]][1]:
                queries[i]=True
            else:
                queries[i]=False
        return queries
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

![image-20250506122144986](C:\Users\33107\AppData\Roaming\Typora\typora-user-images\image-20250506122144986.png)



### M22528:厚道的调分方法

binary search, http://cs101.openjudge.cn/practice/22528/

思路：



代码：

```python
def check(a,stu):
    goal=int(len(stu)*0.4//1)
    x=stu[goal]
    if a*x+1.1**(a*x)>=85:
        return True
    else:
        return False

stu=list(map(float,input().split()))
stu.sort()
left=0
right=10**9
while left<right:
    mid=(left+right)//2
    if check(mid/10**9,stu):
        right=mid
    else:
        left=mid+1
print(left)
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

![image-20250506124945705](C:\Users\33107\AppData\Roaming\Typora\typora-user-images\image-20250506124945705.png)



### Msy382: 有向图判环 

dfs, https://sunnywhy.com/sfbj/10/3/382

思路：



代码：

```python
class Vertex:
    def __init__(self, val):
        self.val = val
        self.next = []

class Graph:
    def __init__(self):
        self.vertices={}

def dfs(start ,curr):
    if visited[start.val] and curr==start:
        return True
    if curr==None or visited[curr.val]:
        return False
    visited[curr.val] = True
    for i in curr.next:
        if dfs(start,i):
            return True
    return False


n,m=map(int,input().split())
g=Graph()
for i in range(n):
    g.vertices[i]=Vertex(i)
for i in range(m):
    u,v=map(int,input().split())
    g.vertices[u].next.append(g.vertices[v])

for i in g.vertices:
    visited=[False]*n
    if dfs(g.vertices[i],g.vertices[i]):
        print('Yes')
        break
else:
    print('No')

```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

![image-20250506131729420](C:\Users\33107\AppData\Roaming\Typora\typora-user-images\image-20250506131729420.png)



### M05443:兔子与樱花

Dijkstra, http://cs101.openjudge.cn/practice/05443/

思路：



代码：

```python
import heapq
class Vertex:
    def __init__(self, val):
        self.val = val
        self.connections = []

class Graph:
    def __init__(self):
        self.vertices={}

def dijkstra(start, end):
    open_list = []
    closed_list = set()
    heapq.heappush(open_list, [0, start,[start.val]])
    while open_list:
        current_distance, current_vertex ,path= heapq.heappop(open_list)
        if current_vertex == end:
            return path
        if current_vertex in closed_list:
            continue
        closed_list.add(current_vertex)
        for distance,vertex in current_vertex.connections:
            if vertex not in closed_list:
                heapq.heappush(open_list, [current_distance + distance, vertex, path+['('+str(distance)+')',vertex.val]])



p=int(input())
g=Graph()
for i in range(p):
    name=input()
    g.vertices[name]=Vertex(name)

q=int(input())
for i in range(q):
    u,v,d=input().split()
    d=int(d)
    g.vertices[u].connections.append((d,g.vertices[v]))
    g.vertices[v].connections.append((d,g.vertices[u]))

r=int(input())
for _ in range(r):
    start,end=input().split()
    ans=dijkstra(g.vertices[start],g.vertices[end])
    print('->'.join(ans))
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

![image-20250506141020794](C:\Users\33107\AppData\Roaming\Typora\typora-user-images\image-20250506141020794.png)



### T28050: 骑士周游

dfs, http://cs101.openjudge.cn/practice/28050/

思路：



代码：

```python

```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>





## 2. 学习总结和收获

<mark>如果发现作业题目相对简单，有否寻找额外的练习题目，如“数算2025spring每日选做”、LeetCode、Codeforces、洛谷等网站上的题目。</mark>

五一出去旅游了（）

下半个学期的重心都放在数算上，继续补每日选做。

这周的题主要是图结合搜索，总体做起来还是比较顺手的，和基于二维列表的搜索算法题（比如第一题）做起来差不多，对于我个人而言难点还是在写搜索的时候完善思路。

M05443:兔子与樱花，第一次接触Dijkstra算法，查了一下CSDN了解了原理，然后在AI自动补充的帮助下做出来了。

M3532.针对图的路径存在性查询I，和之前的并查集题目有点不一样，数据是一次给出而不是逐行处理，时间要求好像也紧一些，所以没有像之前一样每次查询都调用一次find_father，而是统一处理把father直接存起来。







