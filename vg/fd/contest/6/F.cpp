#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define bug(x); cout<<#x<<"="<<x<<endl;
#define lson x<<1
#define rson x<<1|1
#define LL long long
using namespace std;
const int N=1e5+10,M=1e6+10;
struct data{
	int nt,to;
	LL w;
}a[N<<1];
LL v[M<<2],Ti,dp[N],f[N];
int head[N],cnt=0,n,w[M<<2],nm[N],s[N];

void read(int &x){
	char ch=getchar();x=0;
	for(;ch<'0'||ch>'9';ch=getchar()) ;
	for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
}

void read(LL &x){
	char ch=getchar();x=0;
	for(;ch<'0'||ch>'9';ch=getchar()) ;
	for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
}

void add(int x,int y,LL w){
	a[++cnt].to=y,a[cnt].w=w,a[cnt].nt=head[x],head[x]=cnt;
	a[++cnt].to=x,a[cnt].w=w,a[cnt].nt=head[y],head[y]=cnt;
}

int find(int x,int l,int r,LL T){
	if(l==r){
		return min(w[x]*1LL,T/l);
	}
	int mid=(l+r)>>1;
	if(v[x]<T) return w[x];
	if(v[lson]>=T) return find(lson,l,mid,T);
	else return w[lson]+find(rson,mid+1,r,T-v[lson]);
}

void change(int x,int l,int r,int L,LL k){
	if(l==r&&l==L) { v[x]+=L*k*1LL;w[x]+=k;return ; }
	int mid=(l+r)>>1;
	if(L<=mid) change(lson,l,mid,L,k);
	else change(rson,mid+1,r,L,k);
	w[x]=w[lson]+w[rson],v[x]=v[lson]+v[rson];
}

void dfs(int u,int fa,LL w){
	change(1,1,1e6,s[u],nm[u]);
	f[u]=find(1,1,1e6,Ti-2*w);
	LL maxn=0,maxx=0;
	for(int i=head[u];i;i=a[i].nt){
		int to=a[i].to;
		if(to==fa) continue;
		dfs(to,u,w+a[i].w);
		if(dp[to]>=maxn) maxx=maxn,maxn=dp[to];
		else if(dp[to]>maxx) maxx=dp[to];
	}
	if(u!=1) dp[u]=max(maxx,f[u]);
	else dp[u]=max(maxn,f[u]);
	change(1,1,1e6,s[u],-nm[u]);
}

int main(){
	read(n),read(Ti);
	fr(i,1,n) read(nm[i]);
	fr(i,1,n) read(s[i]);
	fr(i,2,n){
		int x;LL w;
		read(x),read(w);
		add(x,i,w);
	}
	dfs(1,0,0);
/*	fr(i,1,n) {
		bug(i);
		bug(dp[i]);
		bug(f[i]);
	}*/
	printf("%lld\n",dp[1]);
	return 0;
}
