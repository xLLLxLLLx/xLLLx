[TOC]



## [Educational Codeforces Round 58 (Rated for Div. 2)](http://codeforces.com/contest/1101)

顺便把网址也给输了进去..23333

这场是2019.01.12早上vp的呢..
达成任务(雾
- [x] 被hack*1

### A. Minimum Integer
`乱搞`
一如既往是道乱搞2333
问在区间$[l,r]$外的$d$的倍数的最小值
显然最小是$d$如果不满足　就在离$r$最近的地方去选即可
```c
#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;

int main(){
	int q;scanf("%d",&q);
	fr(i,1,q){
		LL x,y,d;scanf("%lld%lld%lld",&x,&y,&d);
		if(d<x) printf("%lld\n",d);
		else {
			LL pos=y/d;
			printf("%lld\n",(pos+1)*d);
		}
	}
	return 0;
}
```

------

### B. Accordion

`字符串`　`贪心`

找`[:||:]`的字符串最长是多少

贪心找最前面的`[`与最后的`]`即可
```c
#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=5e5+10;
char lx[N];
int be=-1,ed=-1;
int m[N],s[N];

void fail(){
	printf("-1\n");
	exit(0);
}

int main(){
	scanf("%s",lx+1);
	int len=strlen(lx+1);
	int ct=-1,rs=-1,nm=0,kk=0;
	fr(i,1,len){
		if(lx[i]=='['&&be==-1) be=i;
		if(lx[i]==']') ed=i;
		if(lx[i]==':') m[++kk]=i;
		if(lx[i]=='|') s[++nm]=i;
	}
	if(be==-1||ed==-1||be>ed) fail();
	int ans=4;
	fr(i,1,kk){
		if(m[i]<be) continue;
		if(m[i]>ed) break;
		if(m[i]>be&&rs==-1) rs=m[i];
		ct=m[i];
	}
	if(ct==rs) fail();
	fr(i,1,nm){
		if(s[i]>rs&&s[i]<ct) ans+=1;
	}
	printf("%d\n",ans);
	return 0;
}
```

-------

### C. Division and Union

`贪心`　`思维`

至于为什么写上思维..因为我没有思维..
感觉这道题很水..
但在真正vp的时候就ｇｇ..
没有想到很简便的算法就开始码..
大概是T2Wa了好几发+被Hack了心态上还是有点影响的吧..
但冷静下来还是把这道题给A啦！！

只需找到这个即可
```c
		fr(i,2,n){
			if(a[i].l>maxn) {be=i;break;}
			b[i]=1;
			maxn=max(maxn,a[i].r);
		}
```

```c
#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1e5+10;
struct data{
	int l,r;
	int rk;
}a[N];
int b[N],ys[N],one[N],tw[N];

bool comp(data xx,data yy){
	if(xx.l!=yy.l) return xx.l<yy.l;
	else return xx.r<yy.r;
}

int main(){
	int T;scanf("%d",&T);
	fr(o,1,T){
		int n;scanf("%d",&n);
		fr(i,1,n){
			scanf("%d%d",&a[i].l,&a[i].r);a[i].rk=i;
		}
		sort(a+1,a+1+n,comp);
		int be=-1,maxn=a[1].r;b[1]=1;
		fr(i,2,n){
			if(a[i].l>maxn) {be=i;break;}
			b[i]=1;
			maxn=max(maxn,a[i].r);
		}
		if(be==-1) printf("%d\n",be);
		else {
			fr(i,be,n) b[i]=2;
			fr(i,1,n) ys[a[i].rk]=b[i];
			fr(i,1,n) printf("%d ",ys[i]);
			printf("\n");
		}
	}
	return 0;
}
```

------

### D.GCD Counting

`点分治`

这道题大概是vp快结束的时候想到了点分治吧...
然后和ymz大仙讲了一下..
好像真的可以用点分治做耶..
感觉点分治就是那个套路吧...
主要就是计算答案的时候函数写得不一样??
好像其他的都是一样的说QAQ

自己的思路已经差不多了..
分解质因数什么的都已经想到了..
当然只需维护最大值还是要%%%ymz大仙..
自己想的话大概就维护两个最大值吧
大概和自己早上想那道hdu的点分治差不多..


```c
#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i<=y;--i)
#define LL long long
using namespace std;
const int M=2e5,N=2e5+10,K=2e4+10;
struct data{
	int nt,to;
}a[N<<1];
vector<int>qx[N];
int f[N],dep[N],w[N],head[N],B[K],H[K];
int ys[N],vis[N],g[N],sz[N],yz[N],val[N];
int cnt=0,ans=0,zy=0;

void add(int x,int y){
	a[++cnt].to=y,a[cnt].nt=head[x],head[x]=cnt;
	a[++cnt].to=x,a[cnt].nt=head[y],head[y]=cnt;
}

void init(){
	fr(i,2,M){
		int len=sqrt(i),flg=0,x=i;
		fr(j,2,len){
			if(x%j==0){
				flg=1;
				qx[i].push_back(yz[j]);
				while(x%j==0) x/=j;
			}
			if(x==1) break;
		}
		if(!flg) yz[i]=++zy,ys[zy]=i,qx[i].push_back(zy);
	}
}

int Get(int u,int fa){
	sz[u]=1,f[u]=fa,g[u]=u;
	for(int i=head[u];i;i=a[i].nt){
		int to=a[i].to;
		if(to==fa||vis[to]) continue;
		Get(to,u);
		sz[u]+=sz[to];
	}
	int pos=-1;
	for(int i=head[u];i;i=a[i].nt){
		int to=a[i].to;
		if(to==fa||vis[to]) continue;
		if(sz[to]*2>=sz[u]) pos=g[to];
	}
	if(pos==-1) return g[u];
	while(sz[f[pos]]*2<=sz[u]) pos=f[pos];
	return g[u]=pos;
}

int UPD(int x,int y){
	int len=qx[x].size(),pos=1;
	fr(i,0,len-1){
		H[qx[x][i]]=max(H[qx[x][i]],y);
		pos*=ys[qx[x][i]];
	}
	return pos;
}

int upd(int x,int y,int v){
	int len=qx[x].size(),pos=1;
	fr(i,0,len-1){
		if(v%ys[qx[x][i]]==0) {
			B[qx[x][i]]=max(B[qx[x][i]],y);
			pos*=ys[qx[x][i]];
		}
	}
	return pos;
}

void find(int u,int fa){
	for(int i=head[u];i;i=a[i].nt){
		int to=a[i].to;
		if(vis[to]||to==fa) continue;
		dep[to]=dep[u]+1;
		val[to]=upd(w[to],dep[to],val[u]);
		if(val[to]==1) continue;
		find(to,u);
	}
}

void js(){
	fr(i,1,zy){
		if(H[i]!=-1&&B[i]!=-1) ans=max(ans,B[i]+H[i]);
		H[i]=max(H[i],B[i]);
	}
}

void dfs(int u,int fa){
	memset(H,-1,sizeof H);
	int be=Get(u,fa);//printf("be=%d\n",be);
	val[be]=UPD(w[be],0);//printf("val=%d\n",val[be]);
	for(int i=head[be];i;i=a[i].nt){
		int to=a[i].to;
		if(vis[to]) continue;
		memset(B,-1,sizeof B);dep[to]=1;
		val[to]=upd(w[to],dep[to],val[be]);
		find(to,be);
		js();
	}
	vis[be]=1;
	for(int i=head[be];i;i=a[i].nt){
		int to=a[i].to;
		if(vis[to]) continue;
		dfs(to,be);
	}
}

int main(){
	init();
	int n;scanf("%d",&n);
	fr(i,1,n) scanf("%d",&w[i]);
	for(int i=1,x,y;i<n;++i){
		scanf("%d%d",&x,&y);
		add(x,y);
	}
	vis[0]=1,dfs(1,0);
	if(!ans){
		int res=0;
		fr(i,1,n){
			if(w[i]!=1) res=1;
		}
		printf("%d\n",ans+res);
	}
	else printf("%d\n",ans+1);
	return 0;
}
```

-----

### E.Polycarp's New Job

`贪心`

没想到E题还是有点水的233
主要还是看了一下榜单　发现怎么和我排名差不多的人都A了E题啊
那我就去看了看..
如果不知道有很多人A了的话,,大概就不会再看下去了吧..
最后还是很有信仰的证明了一发..
发现直接排个序取max即可啦!
```c
#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;

int main(){
	int n;scanf("%d",&n);
	int ma=0,mb=0;
	fr(i,1,n){
		char ch;cin>>ch;
		int a,b;scanf("%d%d",&a,&b);
		int x=max(a,b),y=min(b,a);
		if(ch=='+'){
			ma=max(ma,x),mb=max(mb,y);
			//printf("%d %d\n",ma,mb);
		} else {
			if(ma<=x&&mb<=y) printf("YES\n");
			else printf("NO\n");
		}

	}
	return 0;
}
```
发现直接排个序取max即可啦!
```c
#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;

int main(){
	int n;scanf("%d",&n);
	int ma=0,mb=0;
	fr(i,1,n){
		char ch;cin>>ch;
		int a,b;scanf("%d%d",&a,&b);
		int x=max(a,b),y=min(b,a);
		if(ch=='+'){
			ma=max(ma,x),mb=max(mb,y);
			//printf("%d %d\n",ma,mb);
		} else {
			if(ma<=x&&mb<=y) printf("YES\n");
			else printf("NO\n");
		}

	}
	return 0;
}
```

------

### F.Trucks and Cities

`单调` `区间DP`

~~什么听说这道题暴力直接二分就可以过？QwQ~~

我们考虑区间dp

$dp[i][j][k]$  从第$i$个城市到第$j$个城市分成$k$段 最长那段的最小值

那么最后我们的答案就是 $max_{i=1}^m(dp[s][t][r]*c)$



上述$dp$暴力转移:

$$dp[i][j][k]=min_{w=i}^j(max(dp[i][w][k-1],a[j]-a[w]))$$

边界即为 $dp[i][j][0]=a[j]-a[i]$

显然不加优化复杂度$O(n^4)$ ~~TLE稳稳的~~



**这个$dp​$具有单调性！**

设$dp[i][j][k]$ 在$max(dp[i][w_1][k-1],a[j]-a[w_1])$ 取到最优值

而$dp[i][j][k+1]$ 在$max(dp[i][w_2][k],a[j]-a[w_2])$ 取到最优值

那么有$w_1 \leq w_2$

简单理解一下 由于分的段数变多了 总不可能是用越来越少的距离去分段的趴QwQ

```c++
#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=401;
int dp[N][N][N],a[N];

int main(){
	int n,m;scanf("%d%d",&n,&m);
	fr(i,1,n) scanf("%d",&a[i]);
	fr(i,1,n) fr(j,i+1,n) dp[i][j][0]=a[j]-a[i];
	fr(i,1,n) fr(j,i+1,n){
		int w=i;
		fr(k,1,n){
			while(w+1<=n&&max(dp[i][w+1][k-1],a[j]-a[w+1])<max(dp[i][w][k-1],a[j]-a[w])) w++;
			dp[i][j][k]=max(dp[i][w][k-1],a[j]-a[w]);
		}
	}
	LL maxn=0;
	fr(o,1,m){
		int s,t,c,r;scanf("%d%d%d%d",&s,&t,&c,&r);
		maxn=max(maxn,(dp[s][t][r]*1LL*c));
	}
	printf("%lld\n",maxn);
	return 0;
}
```





-------

### G.(Zero XOR Subset)-less

`线性基`

记$qz[i]$ 表示前$i$个数的异或和

**问题可以等价于 $qz[n]$ 必须选 然后在$qz[i](1 \leq i \leq n-1)$ 里面选尽量多个使得任意一个子集的异或和不为0**

这个可以用线性基来搞..

贪心能选就选即可

再稍微讲一下贪心能选就选的正确性趴。(口胡*1)

​	如果当前可以选$qz[i]$ 就选上去 假设$qz[j]$就不能选

​	如果不选上去$qz[j]$就可以选（所以选于不选最多只会影响到一个（一个对一个不就抵消了吗QwQ

```c++
#inclu de<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=32,M=2e5+10;
int q[N],qz[M];

bool insert(int x){
	rf(i,N-1,0){
		if((x>>i)&1){
			if(!q[i]){
				q[i]=x;
				return true;
			} else x^=q[i];
		}
	}
	return false;
}

int main(){
	int n;scanf("%d",&n);
	fr(i,1,n) scanf("%d",&qz[i]);
	fr(i,1,n) qz[i]^=qz[i-1];
	int ans=0;
	if(!qz[n]) return printf("-1\n"),0;
	rf(i,n,1){
		if(insert(qz[i])) ans++;
	}
	cout<<ans<<endl;
	return 0;
}
```

