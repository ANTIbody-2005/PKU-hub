# Assignment #3: 惊蛰 Mock Exam

Updated 1641 GMT+8 Mar 5, 2025

2025 spring, Complied by <mark>王瞿骋、生命科学学院</mark>



> **说明：**
>
> 1. **惊蛰⽉考**：AC3。考试题⽬都在“题库（包括计概、数算题目）”⾥⾯，按照数字题号能找到，可以重新提交。作业中提交⾃⼰最满意版本的代码和截图。
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

### E04015: 邮箱验证

strings, http://cs101.openjudge.cn/practice/04015



思路：

（耗时10min）别忘了考虑“.@”的情况就行



代码：

```python
while True:
    try:
        s=input().split()[0]
    except EOFError:
        break
    if s.count('@')!=1:
        print("NO")
        continue
    if s[0]=='@' or s[0]=='.' or s[-1]=='@' or s[-1]=='.':
        print("NO")
        continue
    for i in range(len(s)):
        if s[i]=='@':
            if s[i+1]=='.' or s[i-1]=='.' or s[i+1:].count('.')==0:
                print("NO")
            else:
                print("YES")
            break
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

![image-20250309192601249](C:\Users\33107\AppData\Roaming\Typora\typora-user-images\image-20250309192601249.png)



### M02039: 反反复复

implementation, http://cs101.openjudge.cn/practice/02039/



思路：

（耗时15min）矩阵处理，按照题意还原矩阵然后按序输出就行了



代码：

```python
n=int(input())
s=input()
c=(len(s)+n-1)//n
m=[]
for i in range(c):
        if i%2==0:
            m.append(s[i*n:i*n+n])
        else:
            m.append(s[i*n+n-1:i*n-1:-1])
for i in range(n):
    for j in range(c):
        print(m[j][i],end="")
print()
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

![image-20250309192744532](C:\Users\33107\AppData\Roaming\Typora\typora-user-images\image-20250309192744532.png)



### M02092: Grandpa is Famous

implementation, http://cs101.openjudge.cn/practice/02092/



思路：

（耗时20min）字典+集合解决计数（用defaultdict也可以），结合排序解决



代码：

```python
while True:
    n,m=map(int,input().split())
    if n==0 and m==0:
        break
    dic={}
    x=set()
    for i in range(n):
        s=list(map(int,input().split()))
        for j in s:
            if j in x:
                dic[j]+=1
            else:
                x.add(j)
                dic[j]=1
    l=[]
    x1=list(x)
    for i in x1:
        l.append((i,dic[i]))
    l.sort(reverse=True,key=lambda x:x[1])
    ms=0
    ans=[]
    for i in l:
        if i[1]<l[0][1]:
            ms=i[1]
            break
    for i in l:
        if i[1]==ms:
            ans.append(i[0])
    ans.sort()
    print(*ans)
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

![image-20250309192919579](C:\Users\33107\AppData\Roaming\Typora\typora-user-images\image-20250309192919579.png)



### M04133: 垃圾炸弹

matrices, http://cs101.openjudge.cn/practice/04133/



思路：

（耗时25min，WA，后续用时10min）滑动窗口，重点是要遍历垃圾而不能遍历格点。考试时遍历格点导致TLE了，然后转变思路当成合并区间做，但是合并的方式搞错了导致WA。



代码：

```python
d=int(input())
n=int(input())
trash=[]
mx,my=0,0
for _ in range(n):
    trash.append(tuple(map(int,input().split())))
    mx,my=max(mx,trash[-1][0]),max(my,trash[-1][1])
count=0
ma=0
for i in range(min(mx+d+1,1025)):
    for j in range(min(my+d+1,1025)):
        value=0
        for k in trash:
            if i+d>=k[0] and j+d>=k[1] and i-d<=k[0] and j-d<=k[1]:
                value+=k[2]
        if value>ma:
            ma=value
            count=1
        elif value==ma:
            count+=1
print(count,ma)
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

![image-20250309200243770](C:\Users\33107\AppData\Roaming\Typora\typora-user-images\image-20250309200243770.png)



### T02488: A Knight's Journey

backtracking, http://cs101.openjudge.cn/practice/02488/



思路：

（耗时25min，WA，后续耗时5min）dfs，只要按字典序从小到大的顺序搜索找到的第一个就对了。但是，由于本题是英文题我根本没发现是要字典序最小的路径。

代码：

```python
board=[]
p,q=0,0
gflag=False
def dfs(x,y,path,deep):
    global board,p,q,gflag
    if gflag:
        return
    if deep==p*q:
        print(path)
        gflag=True
        return
    for dx,dy in [(-1,-2),(1,-2),(-2,-1),(2,-1),(-2,1),(2,1),(-1,2),(1,2)]:
        nx,ny=x+dx,y+dy
        if nx>=0 and nx<p and ny>=0 and ny<q and board[nx][ny]==0:
            board[nx][ny]=1
            dfs(nx,ny,path+chr(ny+ord('A'))+str(nx+1),deep+1)
            board[nx][ny] = 0

n=int(input())
for _ in range(n):
    if _>0:
        print()
    print("Scenario #"+str(_+1)+":")
    gflag=False
    p,q=map(int,input().split())
    board.clear()
    for i in range(p):
        board.append([0]*q)
    board[0][0]=1
    dfs(0,0,"A1",1)
    if not gflag:
        print("impossible")
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

![image-20250309200617411](C:\Users\33107\AppData\Roaming\Typora\typora-user-images\image-20250309200617411.png)



### T06648: Sequence

heap, http://cs101.openjudge.cn/practice/06648/



思路：

（耗时10min，未提交，后续耗时30min）用heapq实现每次取出都是最小，另外由于数据量太大需要逐行处理，而逐行处理后实际上每行只需要嵌套n次循环（因为只要最小的n个和），不需要用dp等算法。



代码：

```python
import heapq

t=int(input())
for _ in range(t):
    m,n=map(int,input().split())
    seq0=sorted(list(map(int,input().split())))
    for _ in range(m-1):
        seq1=sorted(list(map(int,input().split())))
        min_heap=[(seq0[i]+seq1[0],i,0) for i in range(n)]
        heapq.heapify(min_heap)
        res=[]
        for _ in range(n):
            s,x,y=heapq.heappop(min_heap)
            res.append(s)
            if y+1<n:
                heapq.heappush(min_heap,(seq0[x]+seq1[y+1],x,y+1))
        seq0=res.copy()
    print(*seq0)
```



代码运行截图 ==（AC代码截图，至少包含有"Accepted"）==

![image-20250309202406426](C:\Users\33107\AppData\Roaming\Typora\typora-user-images\image-20250309202406426.png)



## 2. 学习总结和收获

<mark>如果发现作业题目相对简单，有否寻找额外的练习题目，如“数算2025spring每日选做”、LeetCode、Codeforces、洛谷等网站上的题目。</mark>

45min做出前3题，然后1h15min一题没ac…… 从看到英文题的时候心态就炸了，感觉很容易漏条件，果然后面A Knight's Journey根本没意识到要输出字典序最小的路径，一直WA……不过既然说期末不考英文题，那就顺从了吧。

 这次月考还是看出一些问题，一点是之前写搜索写的比较随性，没有固定写法，终止和参数传递的思路很混乱，速度也就比较慢。另外就是计概学的大量数据结构和算法软件包（deque，heapq，binary_search，defaultdict）并不熟悉（毕竟当时是旁听，后半学期跟进的不好），一些比较经典的思路都没见过。









