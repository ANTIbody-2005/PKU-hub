# Assignment #7: 20250402 Mock Exam

Updated 1624 GMT+8 Apr 2, 2025

2025 spring, Complied by <mark>王瞿骋、生命科学学院</mark>



> **说明：**
>
> 1. **⽉考**：<mark>AC4</mark> 。考试题⽬都在“题库（包括计概、数算题目）”⾥⾯，按照数字题号能找到，可以重新提交。作业中提交⾃⼰最满意版本的代码和截图。
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

### E05344:最后的最后

http://cs101.openjudge.cn/practice/05344/



思路：

循环链表解决约瑟夫问题，为了方便断连重连还用了双向的，结果忘了把.next.prev=.prev，debug了一会，差点直接用deque逃课了。



代码：

```python
class Linknode:
    def __init__(self,val):
        self.val=val
        self.next=None
        self.prev=None
n,k=map(int,input().split())
pre=Linknode(1)
head=pre
for i in range(2,n+1):
    new=Linknode(i)
    pre.next=new
    new.prev=pre
    pre=pre.next
pre.next=head
head.prev=pre

ans=[]
for i in range(n-1):
    for j in range(k):
       pre=pre.next
    ans.append(pre.val)
    pre.prev.next=pre.next
    pre.next.prev=pre.prev
print(*ans)
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

![image-20250403094503229](C:\Users\33107\AppData\Roaming\Typora\typora-user-images\image-20250403094503229.png)



### M02774: 木材加工

binary search, http://cs101.openjudge.cn/practice/02774/



思路：

还挺典型的二分查找+贪心，还好贪心很简单，但是二分查找的初始上限找错了又debug了一会。



代码：

```python
def check(l):
    global k
    count=0
    for i in log:
        count+=i//l
    if count>=k:
        return True
    return False

n,k=map(int,input().split())
log=[]
for i in range(n):
    log.append(int(input()))
if sum(log)<k:
    print(0)
else:
    left=1
    right=max(log)
    while left<right:
        #print(left,right)
        mid=(left+right)//2
        if check(mid):
            if left==mid:
                if check(right):
                    left=right
                    break
                else:
                    right=left
                    break
            left=mid
        else:
            right=mid-1
    print(left)
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

![image-20250403094543211](C:\Users\33107\AppData\Roaming\Typora\typora-user-images\image-20250403094543211.png)



### M07161:森林的带度数层次序列存储

tree, http://cs101.openjudge.cn/practice/07161/



思路：

没仔细读题（后根序遍历），妄图不用OOP直接做，白花了10分钟……

树的题个人做的不多，不过这题还是比较简单，dfs用递归很好写。



代码：

```python
from collections import deque
class Treenode:
    def __init__(self,val,degree):
        self.val=val
        self.degree=degree
        self.next=[]

def trav(node):
    if node.degree:
        for i in node.next:
            trav(i)
    ans.append(node.val)

n=int(input())
ans=[]
for _ in range(n):
    ori=input().split()
    root=Treenode(ori[0],int(ori[1]))
    stack=deque([root])
    next_count=0
    for i in range(1,len(ori)//2):
        node=Treenode(ori[2*i],int(ori[2*i+1]))
        if node.degree:
            stack.append(node)
        if len(stack[0].next)<stack[0].degree:
            stack[0].next.append(node)
        if len(stack[0].next)==stack[0].degree:
            stack.popleft()

    trav(root)
print(*ans)
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

![image-20250403094605728](C:\Users\33107\AppData\Roaming\Typora\typora-user-images\image-20250403094605728.png)



### M18156:寻找离目标数最近的两数之和

two pointers, http://cs101.openjudge.cn/practice/18156/



思路：

没考虑数据量，用了O(n^2)的算法，还因为大脑短路以为sort后从左往右遍历就可以保证输出多解中小的，考试时一直WA百思不得其解。就目前做过的题来讲主考双指针的题难度都不算高，比较掉以轻心了。



代码：

```python
t=int(input())
s=list(map(int,input().split()))
s.sort()
min_c=abs(s[0]+s[-1]-t)
ans=s[0]+s[-1]
left=0
right=len(s)-1
while left<right:
    if abs(s[left]+s[right]-t)<min_c or abs(s[left]+s[right]-t)==min_c and s[left]+s[right]<ans:
        min_c=abs(s[left]+s[right]-t)
        ans=s[left]+s[right]
    if s[left]+s[right]<t:
        left+=1
    else:
        right-=1
print(ans)
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

![image-20250403094706935](C:\Users\33107\AppData\Roaming\Typora\typora-user-images\image-20250403094706935.png)



### M18159:个位为 1 的质数个数

sieve, http://cs101.openjudge.cn/practice/18159/



思路：

欧拉筛不记得了，只写出了埃氏筛，好在也够用了。感觉在找输出范围的时候可以用bisect的，能快一点，还能方便地解决右端包含问题。



代码：

```python
t=int(input())
s=[]
for _ in range(t):
    s.append(int(input()))
nums=[1]*(max(s)+1)
res=[]
for i in range(2,max(s)):
    if nums[i]==0:
        continue
    if i%10==1:
        res.append(i)
    for j in range(2*i,max(s),i):
        nums[j]=0

for i in range(t):
    print("Case"+str(i+1)+":")
    x=-1
    for j in range(len(res)):
        if s[i]<=res[j]:
            x=j-1
            break
    else:
        x=len(res)-1
    if x==-1:
        print("NULL")
    else:
        print(*res[:x+1])

```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

![image-20250403094735846](C:\Users\33107\AppData\Roaming\Typora\typora-user-images\image-20250403094735846.png)



### M28127:北大夺冠

hash table, http://cs101.openjudge.cn/practice/28127/



思路：

很正常的哈希表题，但是掺了点排序。

但是！没时间了！就差一点点！！！



代码：

```python
teams=set()
dic={}
m=int(input())
for _ in range(m):
    team,ques,judge=input().split(',')
    if team in teams:
        dic[team][0]+=1
    else:
        teams.add(team)
        dic[team]=[1,0,set()]

    if judge == "yes":
        if ques not in dic[team][2]:
            dic[team][2].add(ques)
            dic[team][1] += 1

ans=[]
for i in teams:
    ans.append([i,dic[i][1],dic[i][0]])
ans.sort(key=lambda x:x[0])
ans.sort(key=lambda x:x[2])
ans.sort(reverse=True,key=lambda x:x[1])
for i in range(min(12,len(ans))):
    print(i+1,ans[i][0],ans[i][1],ans[i][2])
```



代码运行截图 ==（AC代码截图，至少包含有"Accepted"）==

![image-20250403094813394](C:\Users\33107\AppData\Roaming\Typora\typora-user-images\image-20250403094813394.png)



## 2. 学习总结和收获

<mark>如果发现作业题目相对简单，有否寻找额外的练习题目，如“数算2025spring每日选做”、LeetCode、Codeforces、洛谷等网站上的题目。</mark>

坠机了。

最后一题就差半分钟，交上就ac了。

没想到会在oj考OOP,不过做起来压力不大，其他几道题也是比较容易想到思路的（二分查找、双指针、素数筛、哈希表），二分查找因为每日选做出现的多写起来比较顺。谢不杀之恩——

之前一直在想2h做6题平均一题20min，现在发现前3-4题根本不能按这个进度来，必须要往快了做，不然但凡中间被debug卡一下或者最后题目比较烦就完蛋了。







