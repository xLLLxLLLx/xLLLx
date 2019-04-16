#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ls ch[x][0]
#define rs ch[x][1]
#define LL long long
using namespace std;
const int N=1e5+10,M=2e6+10;
struct data{
	int nt,to;
}a[N<<1];
LL d[N],sum[M];
int mx[M],ch[M][2];
int cnt=0,sz=0,n,head[N],v[N],rt[N];

void read(int &x){
	char ch=getchar();x=0;
	for(;ch<'0'||ch>'9';ch=getchar()) ;
	for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
}

void add(int x,int y){
	a[++cnt].to=y,a[cnt].nt=head[x],head[x]=cnt;
	a[++cnt].to=x,a[cnt].nt=head[y],head[y]=cnt;
}

void pushup(int x){
	mx[x]=max(mx[ls],mx[rs]);
	if(mx[ls]==mx[rs]) sum[x]=sum[ls]+sum[rs];
	else if(mx[ls]>mx[rs]) sum[x]=sum[ls];
	else sum[x]=sum[rs];
}

int merge(int x,int y,int l,int r){
	if(!x||!y) return x^y;
	if(l==r){
		sum[x]=l;
		mx[x]+=mx[y];
		return x;
	}
	int mid=(l+r)>>1;
	ls=merge(ls,ch[y][0],l,mid);
	rs=merge(rs,ch[y][1],mid+1,r);
	pushup(x);
	return x;
}

void up(int &x,int l,int r,int k){
	if(!x) x=++sz;
	if(l==r){
		sum[x]=l;
		mx[x]++;
		return ;
	}
	int mid=(l+r)>>1;
	if(k<=mid) up(ls,l,mid,k);
	else up(rs,mid+1,r,k);
	pushup(x);
}

void dfs(int u,int fa){
	for(int i=head[u];i;i=a[i].nt){
		if(a[i].to==fa) continue;
		dfs(a[i].to,u);
		merge(rt[u],rt[a[i].to],1,n);
	}
	up(rt[u],1,n,v[u]);
	d[u]=sum[rt[u]];
}

int main(){
	read(n);
	fr(i,1,n) rt[i]=++sz,read(v[i]);
	for(int i=1,x,y;i<n;++i){
		read(x),read(y);
		add(x,y);
	}
	dfs(1,0);
	fr(i,1,n) printf("%lld ",d[i]);
	return 0;
}