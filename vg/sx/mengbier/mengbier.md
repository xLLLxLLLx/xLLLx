[TOC]

## 

~~非常良心的~~博主的~~良心之作~~

决定将二项式反演和莫比乌斯反演一起写了~~因为都柑橘和容斥有关QwQ~~





窝们设

$$F(i)=\sum_{d|i}f(d)$$



- 可以得到 ~~注意观察式子~~

$F(1)=f(1)​$

$F(2)=f(1)+f(2)$

$F(3)=f(1)+f(3)$

$F(4)=f(1)+f(2)+f(4)$

$F(5)=f(1)+f(5)$

$F(6)=f(1)+f(2)+f(3)+f(6)$

$$\downarrow$$

$f(1)=F(1)$

$f(2)=F(2)-F(1)$

$f(3)=F(3)-F(1)​$

$f(4)=F(4)-f(2)$

$f(5)=F(5)-F(1)$

$f(6)=F(6)-F(2)-F(3)+F(1)$



$\Rightarrow$ $$f(i)=\sum_{d|i}\mu(d)*F(\dfrac{i}{d})$$

其中:

$$\mu(d)=\begin{cases} 
		1，d=1;\\
		(-1)^{k}，d=p_1*...*p_k\\0，otherwise\end{cases}​$$



-------

接下来来证明一下这个东西QwQ.

如果你能够用容斥原理感性理解上述结论~~窝觉得可能就行了证明只需要知道方法..公式死记肯定会忘掉..总之感性理解是个好东西QwQ珂我没有~~

其实本质上也是一个容斥原理



