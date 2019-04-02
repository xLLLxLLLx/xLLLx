#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long 
using namespace std;
const int N=5e5+10;
struct data{
	int nt,to;
}a[N<<1];
LL ans=0;
int cnt=0;
int head[N];

template <class T>
void read(T &x){
	char ch=getchar();x=0;
	for(;ch<'0'||ch>'9';ch=getchar()) ;
	for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
}

void add(int x,int y){
	a[++cnt].to=y,a[cnt].nt=head[x],head[x]=cnt;
	a[++cnt].to=x,a[cnt].nt=head[y],head[y]=cnt;
}

#define ls ch[x][0]
#define rs ch[x][1]

int ch[N][2],f[N],zs[N];
LL tag[N],sum[N],v[N],A[N];

bool isroot(int x){
	return (ch[f[x]][0]!=x)&&(ch[f[x]][1]!=x);
}

void down(int x){
	if(x&&tag[x]){
		if(ls) tag[ls]+=tag[x];
		if(rs) tag[rs]+=tag[x];
		sum[x]+=tag[x];
		tag[x]=0;
	}
}

void pushdown(int x){
	if(!isroot(x)) pushdown(f[x]);
	down(x);
}

bool pd(int x){ return ch[f[x]][1]==x; }

void rotate(int x){
	int y=f[x],z=f[y];
	int k=pd(y),d=pd(x);
	if(!isroot(y)) ch[z][k]=x;
	f[x]=z;
	ch[y][d]=ch[x][d^1],f[ch[x][d^1]]=y;
	ch[x][d^1]=y,f[y]=x;
}

void splay(int x){
	pushdown(x);
	//printf("wx=%d\n",x);
	for(;!isroot(x);rotate(x)){
		//printf("x=%d\n",x);
		if(!isroot(f[x])) pd(f[x])^pd(x) ? rotate(x) : rotate(f[x]);
	}
}

void cal(int x){
	ans-=A[x];
	//printf("x=%d sum=%d %d %d %d\n",x,sum[x],zs[x],sum[zs[x]],v[x]);
	A[x]=(zs[x]) ? (2*(sum[x]-sum[zs[x]])) : (sum[x]-1);
	if(v[x]*2>sum[x]+1) A[x]=2*(sum[x]-v[x]);
	ans+=A[x];
}

int Getroot(int x){
	for(;ls;) down(x),x=ls;
	down(x);
	return x;
}

void access(int x,int y){
	v[x]+=y;
	for(int i=0;x;i=x,x=f[x]){
		splay(x);
		sum[x]+=y,tag[ls]+=y,down(ls);
		if(zs[x]){
			pushdown(zs[x]);
			if(sum[zs[x]]*2<=sum[x]+1) zs[x]=rs=0;
		}
		int zz=Getroot(i);
		if(sum[zz]*2>sum[x]+1) zs[x]=zz,rs=i;
		cal(x);
	}
}

void dfs(int x,int fa){
	f[x]=fa,sum[x]=v[x];
	for(int i=head[x];i;i=a[i].nt){
		if(a[i].to==fa) continue;
		dfs(a[i].to,x);
		sum[x]+=sum[a[i].to];
		if(sum[a[i].to]>sum[zs[x]]) zs[x]=a[i].to;
	}
	if(sum[zs[x]]*2<=sum[x]+1) zs[x]=0;
	rs=zs[x],cal(x);
}

int main(){
	int n,m;read(n),read(m);
	fr(i,1,n) read(v[i]);
	for(int i=1,x,y;i<n;++i) read(x),read(y),add(x,y);
	dfs(1,0);
	printf("%lld\n",ans);
	for(int i=1,x,y;i<=m;++i) read(x),read(y),access(x,y),printf("%lld\n",ans);
	return 0;
}