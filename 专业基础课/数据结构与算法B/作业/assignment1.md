# Assignment #1: 虚拟机，Shell & 大语言模型

Updated 1730 GMT+8 Feb 20, 2025

2025 spring, Complied by <mark>王瞿骋、生命科学学院</mark>



**作业的各项评分细则及对应的得分**

| 标准                                 | 等级                                                         | 得分 |
| ------------------------------------ | ------------------------------------------------------------ | ---- |
| 按时提交                             | 完全按时提交：1分<br/>提交有请假说明：0.5分<br/>未提交：0分  | 1 分 |
| 源码、耗时（可选）、解题思路（可选） | 提交了4个或更多题目且包含所有必要信息：1分<br/>提交了2个或以上题目但不足4个：0.5分<br/>没有提供源码：0分 | 1 分 |
| AC代码截图                           | 提交了4个或更多题目且包含所有必要信息：1分<br/>提交了2个或以上题目但不足4个：0.5分<br/>没有提供截图：0分 | 1 分 |
| 清晰头像、PDF文件、MD/DOC附件        | 包含清晰的Canvas头像、PDF文件以及MD或DOC格式的附件：1分<br/>缺少上述三项中的任意一项：0.5分<br/>缺失两项或以上：0分 | 1 分 |
| 学习总结和个人收获                   | 提交了学习总结和个人收获：1分<br/>未提交学习总结或内容不详：0分 | 1 分 |
| 总得分： 5                           | 总分满分：5分                                                |      |
>
> 
>
> **说明：**
>
> 1. **解题与记录：**
>       - 对于每一个题目，请提供其解题思路（可选），并附上使用Python或C++编写的源代码（确保已在OpenJudge， Codeforces，LeetCode等平台上获得Accepted）。请将这些信息连同显示“Accepted”的截图一起填写到下方的作业模板中。（推荐使用Typora https://typoraio.cn 进行编辑，当然你也可以选择Word。）无论题目是否已通过，请标明每个题目大致花费的时间。
>    
>2. **课程平台与提交安排：**
> 
>   - 我们的课程网站位于Canvas平台（https://pku.instructure.com ）。该平台将在第2周选课结束后正式启用。在平台启用前，请先完成作业并将作业妥善保存。待Canvas平台激活后，再上传你的作业。
> 
>       - 提交时，请首先上传PDF格式的文件，并将.md或.doc格式的文件作为附件上传至右侧的“作业评论”区。确保你的Canvas账户有一个清晰可见的头像，提交的文件为PDF格式，并且“作业评论”区包含上传的.md或.doc附件。
> 
>3. **延迟提交：**
> 
>   - 如果你预计无法在截止日期前提交作业，请提前告知具体原因。这有助于我们了解情况并可能为你提供适当的延期或其他帮助。 
> 
>请按照上述指导认真准备和提交作业，以保证顺利完成课程要求。



## 1. 题目

### 27653: Fraction类

http://cs101.openjudge.cn/practice/27653/



思路：

（耗时10min）OOP题目，在寒假中已经做过，当时不会写OOP直接看答案，这次手搓出来了。主要要实现Fraction类的定义、输出和加法（包含化简），化简调用math库的gcd来实现。



代码：

```python
import math
class Fraction:
    def __init__(self, up, down):
        self.up = up
        self.down = down

    def __str__(self):
        return str(self.up) + '/' + str(self.down)

    def __add__(self, other):
        new_up = self.up * other.down + self.down * other.up
        new_down = self.down * other.down
        tmp=math.gcd(new_up,new_down)
        new_up=new_up//tmp
        new_down=new_down//tmp
        return Fraction(new_up,new_down)

a,b,c,d=map(int,input().split())
print(Fraction(a,b)+Fraction(c,d))
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

![image-20250302152904837](C:\Users\33107\AppData\Roaming\Typora\typora-user-images\image-20250302152904837.png)



### 1760.袋子里最少数目的球

 https://leetcode.cn/problems/minimum-limit-of-balls-in-a-bag/




思路：

（耗时15min）二分查找题。显然可能的开销应当大于nums[i]的最小值，小于nums[i]的最大值，以此为范围进行二分查找。每次判断mid开销下所需操作数是否小于等于maxOperations限制，如果符合则取向下继续查找，反之向上。所需操作数的计算由每一袋达成mid开销所需的操作数（nums[i]-1）//mid加合得到。



代码：

```python
class Solution:
    def minimumSize(self, nums: List[int], maxOperations: int) -> int:
        right=max(nums)
        left=1
        ans=0
        while left<=right:
            mid= (left+right)//2
            if sum((x-1)//mid for x in nums)<=maxOperations:
                right=mid-1
                ans=mid
            else:
                left=mid+1
        return ans
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

![image-20250302154026185](C:\Users\33107\AppData\Roaming\Typora\typora-user-images\image-20250302154026185.png)



### 04135: 月度开销

http://cs101.openjudge.cn/practice/04135



思路：

（耗时15min）二分查找题。fajo月最大开销应当大于天开销的最大值，小于天开销的总和，以此为范围进行二分查找。检查当前开销限制下是否能用限制的fajo月数量达成，用简单的贪心算法实现即可。



代码：

```python
def check(limit):
    global cost,m
    count=0
    stack=0
    for i in cost:
        if stack+i<=limit:
            stack+=i
        else:
            count+=1
            stack=i
    count+=1
    if count<=m:
        return True
    else:
        return False

n,m = map(int,input().split())
cost=[]
for _ in range(n):
    cost.append(int(input()))
right=sum(cost)
left=max(cost)
ans=0
while left<=right:
    mid=(left+right)//2
    if check(mid):
        ans=mid
        right=mid-1
    else:
        left=mid+1
print(ans)
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

![image-20250302154513337](C:\Users\33107\AppData\Roaming\Typora\typora-user-images\image-20250302154513337.png)



### 27300: 模型整理

http://cs101.openjudge.cn/practice/27300/



思路：

用字典来存储模型名称（key）并与参数（value，存成list）关联。由于题目已经说明B数量级参数一定比M大，只要分别进行排序即可。



代码：

```python
def show(l):
    m=[]
    b=[]
    for i in range(len(l)):
        if l[i][-1]=='M':
            m.append((float(l[i][:-1]),i))
        else:
            b.append((float(l[i][:-1]),i))
    m.sort(key=lambda x: x[0])
    b.sort(key=lambda x: x[0])
    print(', '.join(l[x[1]] for x in m+b))

n=int(input())
dic={}
model=[]
for _ in range(n):
    s=input().split('-')
    if s[0] in model:
        dic[s[0]].append(s[1])
    else:
        dic[s[0]]=[s[1]]
        model.append(s[0])
model.sort()
for i in model:
    print(i+':',end=' ')
    show(dic[i])
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

![image-20250302155449924](C:\Users\33107\AppData\Roaming\Typora\typora-user-images\image-20250302155449924.png)



### Q5. 大语言模型（LLM）部署与测试

本任务旨在本地环境或通过云虚拟机（如 https://clab.pku.edu.cn/ 提供的资源）部署大语言模型（LLM）并进行测试。用户界面方面，可以选择使用图形界面工具如 https://lmstudio.ai 或命令行界面如 https://www.ollama.com 来完成部署工作。

测试内容包括选择若干编程题目，确保这些题目能够在所部署的LLM上得到正确解答，并通过所有相关的测试用例（即状态为Accepted）。选题应来源于在线判题平台，例如 OpenJudge、Codeforces、LeetCode 或洛谷等，同时需注意避免与已找到的AI接受题目重复。已有的AI接受题目列表可参考以下链接：
https://github.com/GMyhf/2025spring-cs201/blob/main/AI_accepted_locally.md

请提供你的最新进展情况，包括任何关键步骤的截图以及遇到的问题和解决方案。这将有助于全面了解项目的推进状态，并为进一步的工作提供参考。





### Q6. 阅读《Build a Large Language Model (From Scratch)》第一章

作者：Sebastian Raschka

请整理你的学习笔记。这应该包括但不限于对第一章核心概念的理解、重要术语的解释、你认为特别有趣或具有挑战性的内容，以及任何你可能有的疑问或反思。通过这种方式，不仅能巩固你自己的学习成果，也能帮助他人更好地理解这一部分内容。





## 2. 学习总结和个人收获

<mark>如果发现作业题目相对简单，有否寻找额外的练习题目，如“数算2025spring每日选做”、LeetCode、Codeforces、洛谷等网站上的题目。</mark>

Typora真好用^_^

之前上过计概A和闫老师的计概B，对一些算法都比较熟悉了，但是数据结构方面还略生疏。寒假选做只做到tree era就摆了，熟悉了Leetcode这种OOP的编程方式，链表的题都能解决，树的课件没看完，感觉和链表没有本质区别。每日选做持续跟进，不过是隔几天做一次、一次做几天的量，目前还比较轻松，算法里面二分查找写起来不太熟练，细节比较多，在考虑多做些题。LLM在本地部署了Deepseek-7b的模型，还没怎么使用过，好像比较笨；创建了虚拟机，还没用来部署大模型，主要是本身对LLM不怎么感兴趣，不过Linux方面的内容比较重要，再多看看。



