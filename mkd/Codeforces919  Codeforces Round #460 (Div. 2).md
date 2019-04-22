[TOC]

### [Codeforces Round #460 (Div. 2)](https://codeforces.com/contest/919)

***菜啊* **

-----





#### codeforces919D.[Substring](https://codeforces.com/contest/919/problem/D)

`拓扑排序` `dp`

##### Description

> 给你一个长度为$n$的字符串
>
> 给你一张有向图，$n$个节点，$m$条边
>
> 选择一条路径 使得路径上的点所对应的字符形成的字符串 同一个字母出现的次数最多是多少？
>
> （无穷大输出`-1`

> $1 \leq n,m \leq 3*10^5$

##### Solution

~~.dp状态想傻了~~

我们考虑一下，如果这张图有环的话 那么肯定是无穷大了。

这个可以用`topsort`也就是拓扑排序去判断

很容易想到$dp$ 

$dp[u][i]$表示到达$u$点 字符为$i$的个数最大有多少个

在用拓扑判断的时候顺便$dp$一下就行啦qwq

```c++
#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=3e5+10,M=30;
struct data{
	int nt,to;
}a[N<<1];
queue<int>q;
char lx[N];
int f[N][M],head[N],vis[N],c[N],d[N],cnt=0;

void add(int x,int y){
	d[y]++;
	a[++cnt].to=y,a[cnt].nt=head[x],head[x]=cnt;
}

int main(){
	int n,m;scanf("%d%d",&n,&m);
	scanf("%s",lx+1);
	for(int i=1,x,y;i<=m;++i){
		scanf("%d%d",&x,&y);
		add(x,y);
	}
	fr(i,1,n) if(!d[i]) q.push(i),f[i][lx[i]-'a'+1]=1;
	int tot=n;
	while(!q.empty()){
		int nw=q.front();q.pop();
		tot--;
		for(int i=head[nw];i;i=a[i].nt){
			int to=a[i].to;
			d[to]--;
			fr(j,1,26) 
				if(f[to][j]<f[nw][j]+(lx[to]-'a'+1==j)) f[to][j]=f[nw][j]+(lx[to]-'a'+1==j);
			if(!d[to]) q.push(to);
		}
	}
	if(tot) return printf("-1\n"),0;
	int maxn=0;
	fr(i,1,n) fr(j,1,26) maxn=max(maxn,f[i][j]);
	cout<<maxn<<endl;
	return 0;
}
```



#### E. [Congruence Equation](https://codeforces.com/contest/919/problem/E)

`乱搞` `周期性`

##### Description

> 

