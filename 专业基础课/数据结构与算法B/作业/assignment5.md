# Assignment #5: 链表、栈、队列和归并排序

Updated 1348 GMT+8 Mar 17, 2025

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

### LC21.合并两个有序链表

linked list, https://leetcode.cn/problems/merge-two-sorted-lists/

思路：

（10min）其实就是归并排序

代码：

```python
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def mergeTwoLists(self, list1: Optional[ListNode], list2: Optional[ListNode]) -> Optional[ListNode]:
        head=None
        if not list1:
            return list2
        if not list2:
            return list1

        if list1.val<=list2.val:
            head=list1
            list1=list1.next
        else:
            head=list2
            list2=list2.next
        point=head
        while list1 and list2:
            if list1.val<=list2.val:
                point.next=list1
                list1=list1.next
                point=point.next
            else:
                point.next=list2
                list2=list2.next
                point=point.next
        while list1:
            point.next=list1
            list1=list1.next
            point=point.next
        while list2:
            point.next=list2
            list2=list2.next
            point=point.next
        return head
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

![image-20250323123736335](C:\Users\33107\AppData\Roaming\Typora\typora-user-images\image-20250323123736335.png)



### LC234.回文链表

linked list, https://leetcode.cn/problems/palindrome-linked-list/

<mark>请用快慢指针实现。</mark>



代码：

```python
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def isPalindrome(self, head: Optional[ListNode]) -> bool:
        fast=slow=pre=head
        while fast and fast.next:
            fast=fast.next.next
            slow=slow.next
            
        if fast:
            slow=slow.next
        while slow:
            if slow.val!=pre.val:
                return False
            slow=slow.next
            pre=pre.next
        return True
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

![image-20250323123913288](C:\Users\33107\AppData\Roaming\Typora\typora-user-images\image-20250323123913288.png)



### LC1472.设计浏览器历史记录

doubly-lined list, https://leetcode.cn/problems/design-browser-history/

<mark>请用双链表实现。</mark>



代码：

```python
class Node:
    def __init__(self,val:str,pre=None):
        self.val=val
        self.next=None
        self.pre=pre

class BrowserHistory:

    def __init__(self, homepage: str):
        self.cur=Node(homepage,None)

    def visit(self, url: str) -> None:
        self.cur.next=Node(url,self.cur)
        self.cur=self.cur.next

    def back(self, steps: int) -> str:
        while self.cur and self.cur.pre and steps:
            self.cur=self.cur.pre
            steps-=1
        return self.cur.val

    def forward(self, steps: int) -> str:
        while self.cur and self.cur.next and steps:
            self.cur=self.cur.next
            steps-=1
        return self.cur.val


# Your BrowserHistory object will be instantiated and called as such:
# obj = BrowserHistory(homepage)
# obj.visit(url)
# param_2 = obj.back(steps)
# param_3 = obj.forward(steps)
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

![image-20250323131523253](C:\Users\33107\AppData\Roaming\Typora\typora-user-images\image-20250323131523253.png)



### 24591: 中序表达式转后序表达式

stack, http://cs101.openjudge.cn/practice/24591/

思路：

（20min）复习了一下调度场算法

代码：

```python
level={"+":1,"-":1,"*":2,"/":2}

def prep():
    s=input()
    new=[]
    tmp=""
    for i in s:
        if i in "+-*/()":
            if tmp!="":
                new.append(tmp)
            tmp=""
            new.append(i)
        else:
            tmp+=i
    if tmp:
        new.append(tmp)
    return new

n=int(input())
for _ in range(n):
    lst=prep()
    stack=[]
    ans=[]
    for i in lst:
        if i in "+-*/()":
            if i=="(":
                stack.append(i)
            elif i==")":
                while stack and stack[-1]!="(":
                    ans.append(stack.pop())
                stack.pop()
            else:
                while stack and stack[-1]!="(" and level[i]<=level[stack[-1]]:
                    ans.append(stack.pop())
                stack.append(i)
        else:
            ans.append(i)
    while stack:
        ans.append(stack.pop())
    print(" ".join(ans))
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

![image-20250323131613966](C:\Users\33107\AppData\Roaming\Typora\typora-user-images\image-20250323131613966.png)



### 03253: 约瑟夫问题No.2

queue, http://cs101.openjudge.cn/practice/03253/

<mark>请用队列实现。</mark>



代码：

```python
from collections import deque

def joseph(n,q,m):
    if n==0 and q==0 and m==0:
        return False
    queue=deque(i for i in range(1,n+1))
    ans=[]
    for i in range(q-1):
        queue.append(queue.popleft())
    while queue:
        for i in range(m-1):
            queue.append(queue.popleft())
        ans.append(queue.popleft())
    print(",".join(map(str,ans)))
    return True

while True:
    if not joseph(*map(int,input().split())):
        break
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

![image-20250323133021091](C:\Users\33107\AppData\Roaming\Typora\typora-user-images\image-20250323133021091.png)



### 20018: 蚂蚁王国的越野跑

merge sort, http://cs101.openjudge.cn/practice/20018/

思路：

(15min)读题发现和之前的ultra-quick sort几乎没有区别，只不过是从大到小的归并排序

代码：

```python
ans=0

def merge_sort(arr):
    global ans
    if len(arr)<=1:
        return arr
    mid = len(arr) // 2
    left = arr[:mid]
    right = arr[mid:]
    left=merge_sort(left)
    right=merge_sort(right)
    i=j=k=0
    new_arr=[]
    while i < len(left) and j < len(right):
        if left[i]>=right[j]:
            new_arr.append(left[i])
            i+=1
        else:
            new_arr.append(right[j])
            j+=1
            ans+=len(left)-i
        k+=1
    while i<len(left):
        new_arr.append(left[i])
        i+=1
        k+=1
    while j<len(right):
        new_arr.append(right[j])
        j+=1
        k+=1
    return new_arr

n=int(input())
l=[]
for i in range(n):
    l.append(int(input()))

merge_sort(l)
print(ans)
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

![image-20250323131734281](C:\Users\33107\AppData\Roaming\Typora\typora-user-images\image-20250323131734281.png)



## 2. 学习总结和收获

<mark>如果发现作业题目相对简单，有否寻找额外的练习题目，如“数算2025spring每日选做”、LeetCode、Codeforces、洛谷等网站上的题目。</mark>

喜报：跟上每日选做进度了（3月22日及以前已完成），整理了一个每日选做经典题收藏夹（包括双指针、并查集、归并排序、堆、栈、单调栈的一些题，或者调度场、二分查找+greedy等算法）。（p.s.有没有办法在本地对每日选做md文件做标记的同时保持和github网页的同步）

随着做过的题越来越多，很多新遇到的题已经可以直接套用做过的题的模版了（比如蚂蚁王国的越野跑，一看就知道是归并排序），难题则往往是算法不直接显示、思路需要结合数学思维简化的题（比如01159: Palindrome，不看提示真的想不到去找和反转序列的最长公共序列，但是一旦知道了算法就能比较快解决）；OOP的题，尤其是链表，感觉更随机应变一点，主要是要熟悉类的写法，像LC1472.设计浏览器历史记录，之前其实只接触过单链表和循环链表，但是看了题就能猜到什么是双链表和怎么写了，希望接下来树的部分也能顺利掌握吧。









