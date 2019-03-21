## $tarjan$

### 前言

~~LLL的脑子 过目即忘~~

~~算不清多少次搜索$tarjan$要怎么写 还是不会写~~

懒。

### 变量名介绍

- $dfn[u]$ 表示$u$节点是**第几个被搜到的**($dfs$序)
- $low[u]$表示$u$节点及其子孙节点中$dfn$的最小值
- $stk[]$ 表示当前所有可能构成强连通分量的点
- $vis[]$ 表示一个点是否在$stk[]$ 数组中

by the way，

> <font color="redblue">$low$的作用是什么? </font>

> **显然是记录一个它最大能联通到哪个祖先节点(包括自己)**



而$dfn[u]=low[u]$ $\Rightarrow$ $u$的子树中 没有一个节点有边指向$u$的祖先 **即$u$点与它的子孙节点构成了一个最大的强连通图又强连通分量**



魔板

```c++
#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=
```











