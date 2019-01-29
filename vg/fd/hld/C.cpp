#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
#define lson x<<1
#define rson x<<1|1
using namespace std;
const int N=1e5+10;
struct data{
	int nt,to;
}a[N<<1];
int f[N],dep[N],s[N],sz[N],id[N],ed[N],ys[N],tp[N],head[N];
int n,m,cnt=0,res=0;
LL sum[N<<2],lz[N<<2],w[N];

void add(int x,int y){
	a[++cnt].to=y,a[cnt].nt=head[x],head[x]=cnt;
	a[++cnt].to=x,a[cnt].nt=head[y],head[y]=cnt;
}

void dfs1(int u,int v){
	f[u]=v;dep[u]=dep[v]+1;
	sz[u]=1;
	for(int i=head[u];i;i=a[i].nt){
		int to=a[i].to;
		if(v==to) continue;
		dfs1(to,u);
		sz[u]+=sz[to];
		if(sz[s[u]]<sz[to]) s[u]=to;
	}
}

void dfs2(int u,int v){
	id[u]=++res;tp[u]=v;
	if(!s[u]) {
		ed[u]=res;
		return ;
	}
	else dfs2(s[u],v);
	for(int i=head[u];i;i=a[i].nt){
		int to=a[i].to;
		if(to==f[u]||to==s[u]) continue;
		dfs2(to,to);
	}
	ed[u]=res;
}

void pushdown(int x,int l,int r){
	if(!lz[x]) return ;
	int mid=(l+r)>>1;
	sum[lson]+=lz[x]*(mid-l+1);
	sum[rson]+=lz[x]*(r-mid);
	lz[lson]+=lz[x],lz[rson]+=lz[x];
	lz[x]=0;
}

void Gai(int x,int l,int r,int L,int R,LL k){
	if(L<=l&&r<=R) {
		sum[x]+=k*(r-l+1);
		lz[x]+=k;
		return ;
	}
	int mid=(l+r)>>1;
	pushdown(x,l,r);
	if(L<=mid) Gai(lson,l,mid,L,R,k);
	if(R>mid) Gai(rson,mid+1,r,L,R,k);
	sum[x]=sum[lson]+sum[rson];
}

LL Get(int x,int l,int r,int L,int R){
	if(L<=l&&r<=R) return sum[x];
	int mid=(l+r)>>1;
	LL ans1=0,ans2=0;
	pushdown(x,l,r);
	if(L<=mid) ans1=Get(lson,l,mid,L,R);
	if(R>mid) ans2+=Get(rson,mid+1,r,L,R);
	return ans1+ans2;
}

LL find(int x,int y){
	LL ans=0;
	int fx=tp[x],fy=tp[y];
	for(;fx!=fy;){
		if(dep[fx]>dep[fy]){
			ans+=Get(1,1,n,id[fx],id[x]);
			x=f[fx],fx=tp[x];
		} else {
			ans+=Get(1,1,n,id[fy],id[y]);
			y=f[fy],fy=tp[y];
		}
	}
	if(id[x]<id[y]) ans+=Get(1,1,n,id[x],id[y]);
	else ans+=Get(1,1,n,id[y],id[x]);
	return ans;
}

int main(){
	scanf("%d%d",&n,&m);
	fr(i,1,n) scanf("%lld",&w[i]);
	fr(i,1,n-1){
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);
	}
	dfs1(1,1),dfs2(1,1);
	fr(i,1,n) {
		Gai(1,1,n,id[i],id[i],w[i]);
	}
	fr(i,1,m){
		int x,y;LL z;
		scanf("%d%d",&x,&y);
		if(x==1) {
			scanf("%lld",&z);
			Gai(1,1,n,id[y],id[y],z);
		} else if(x==2) {
			scanf("%lld",&z);
			Gai(1,1,n,id[y],ed[y],z);
		} else {
			printf("%lld\n",find(1,y));
		}
	}
	return 0;
}
