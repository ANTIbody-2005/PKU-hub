# Assignment #4: 位操作、栈、链表、堆和NN

Updated 1203 GMT+8 Mar 10, 2025

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

### 136.只出现一次的数字

bit manipulation, https://leetcode.cn/problems/single-number/



<mark>请用位操作来实现，并且只使用常量额外空间。</mark>



代码：

```python
class Solution:
    def singleNumber(self, nums: List[int]) -> int:
        ans=0
        for i in nums:
            ans^=i
        return ans
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

![image-20250317021714182](C:\Users\33107\AppData\Roaming\Typora\typora-user-images\image-20250317021714182.png)



### 20140:今日化学论文

stack, http://cs101.openjudge.cn/practice/20140/



思路：



代码：

```python
s=input()

stack=[]
tmp=""
ans=""

for i in s:
    if i=='[':
        if tmp:
            stack.append(tmp)
            tmp=""
        stack.append(i)
    elif i==']':
        while stack and not stack[-1]=='[':
            x=stack.pop()
            if x.isdigit():
                tmp*=int(x)
            else:
                tmp=x+tmp
        if not stack:
            ans+=tmp
            tmp=""
        else:
            stack.pop()
    elif not i.isdigit() and tmp.isdigit():
        stack.append(tmp)
        tmp=i
    else:
        tmp+=i

while stack:
    ans=stack.pop()+ans
if tmp:
    ans+=tmp

print(ans)
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

![image-20250317024004794](C:\Users\33107\AppData\Roaming\Typora\typora-user-images\image-20250317024004794.png)



### 160.相交链表

linked list, https://leetcode.cn/problems/intersection-of-two-linked-lists/



思路：

最开始是使用集合解决，发现空间复杂度略高，后来发现双指针交替可以达成常数空间复杂度



代码：

```python
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, x):
#         self.val = x
#         self.next = None

class Solution:
    def getIntersectionNode(self, headA: ListNode, headB: ListNode) -> Optional[ListNode]:
        pa,pb=headA,headB
        count=0
        while pa!=pb:
            if pa and pb:
                pa=pa.next
                pb=pb.next
            elif not pa:
                pa=headB
            elif not pb:
                pb=headA
        if pa:
            return pa
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

![image-20250317030137088](C:\Users\33107\AppData\Roaming\Typora\typora-user-images\image-20250317030137088.png)



### 206.反转链表

linked list, https://leetcode.cn/problems/reverse-linked-list/



思路：

最初用了三个指针，后来看了题解发现可以用递归解决



代码：

```python
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def reverseList(self, head: Optional[ListNode]) -> Optional[ListNode]:
        def recur(cur,pre):
            if not cur:
                return pre
            res=recur(cur.next,cur)
            cur.next=pre
            return res
        return recur(head,None)

```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

![image-20250317030348358](C:\Users\33107\AppData\Roaming\Typora\typora-user-images\image-20250317030348358.png)



### 3478.选出和最大的K个元素

heap, https://leetcode.cn/problems/choose-k-elements-with-maximum-sum/



思路：

感觉是比较明显的heap题，开始是想用字典将nums1的元素和索引存起来，还用了nlargest，后来想到可以改成把nums1、nums2和索引直接存一起



代码：

```python
import heapq
class Solution:
    def findMaxSum(self, nums1: List[int], nums2: List[int], k: int) -> List[int]:
        allowed=[]
        heapq.heapify(allowed)
        sum_allowed=0

        nums=[(nums1[i],nums2[i],i) for i in range(len(nums1))]
        nums.sort()
        ans=[0]*len(nums)

        i=0
        pre=0
        while i<len(nums) and nums[i][0]==nums[0][0]:
            i+=1
        pre=0
        while i<len(nums):
            while nums[pre][0]<nums[i][0]:
                if len(allowed)<k:
                    heapq.heappush(allowed,nums[pre][1])
                    sum_allowed+=nums[pre][1]
                else:
                    sum_allowed=sum_allowed+nums[pre][1]-heapq.heappushpop(allowed,nums[pre][1])
                pre+=1
            ans[nums[i][2]]=sum_allowed
            i+=1
        return ans
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

![image-20250317211300616](C:\Users\33107\AppData\Roaming\Typora\typora-user-images\image-20250317211300616.png)



### Q6.交互可视化neural network

https://developers.google.com/machine-learning/crash-course/neural-networks/interactive-exercises

**Your task:** configure a neural network that can separate the orange dots from the blue dots in the diagram, achieving a loss of less than 0.2 on both the training and test data.

**Instructions:**

In the interactive widget:

1. Modify the neural network hyperparameters by experimenting with some of the following config settings:
   - Add or remove hidden layers by clicking the **+** and **-** buttons to the left of the **HIDDEN LAYERS** heading in the network diagram.
   - Add or remove neurons from a hidden layer by clicking the **+** and **-** buttons above a hidden-layer column.
   - Change the learning rate by choosing a new value from the **Learning rate** drop-down above the diagram.
   - Change the activation function by choosing a new value from the **Activation** drop-down above the diagram.
2. Click the Play button above the diagram to train the neural network model using the specified parameters.
3. Observe the visualization of the model fitting the data as training progresses, as well as the **Test loss** and **Training loss** values in the **Output** section.
4. If the model does not achieve loss below 0.2 on the test and training data, click reset, and repeat steps 1–3 with a different set of configuration settings. Repeat this process until you achieve the preferred results.

给出满足约束条件的<mark>截图</mark>，并说明学习到的概念和原理。





## 2. 学习总结和收获

<mark>如果发现作业题目相对简单，有否寻找额外的练习题目，如“数算2025spring每日选做”、LeetCode、Codeforces、洛谷等网站上的题目。</mark>

本次作业的题目中链表的题还是比较能处理，毕竟寒假预习了。stack的题算是比较麻烦，但是做法相对固定的（比如中序表达式转后序表达式、字符串解码），也是复习了一下。每日选做落后有点多，周末刚追到3月10号左右，要开始链表了。在leetcode摸索了一些小用法，使用起来更熟练了，也第一次知道了可以在自定义函数内嵌套自定义函数，以及nonlocal声明等。









