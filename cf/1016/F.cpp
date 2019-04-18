#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long 
using namespace std;
const int N=3e5+10;
struct data{
	int nt,to;
	ll w;
}a[N<<1];
int cnt=0,tp=1;
ll dis[N],l[N],gg[N];
int head[N],f[N],sz[N],mk[N],st[N],dep[N];

void add(int x,int y,ll w){
	a[++cnt].to=y,a[cnt].w=w,a[cnt].nt=head[x],head[x]=cnt;
	a[++cnt].to=x,a[cnt].w=w,a[cnt].nt=head[y],head[y]=cnt;
}

void dfs(int u,int fa){
	f[u]=fa,dep[u]=dep[fa]+1;
	for(int i=head[u];i;i=a[i].nt){
		if(a[i].to==fa||mk[a[i].to]) continue;
		dis[a[i].to]=dis[u]+a[i].w;
		dfs(a[i].to,u);
	}
}

void Dfs(int u,int fa){
	sz[u]=1;
	for(int i=head[u];i;i=a[i].nt){
		if(a[i].to==fa||mk[a[i].to]) continue;
		Dfs(a[i].to,u);
		l[u]=max(l[u],a[i].w);
		sz[u]+=sz[a[i].to];
	}
}

int main(){
	int n,m;scanf("%d%d",&n,&m);
	fr(i,2,n){
		int x,y;ll w;
		scanf("%d%d%lld",&x,&y,&w);
		add(x,y,w);
	}
	dfs(1,0);
	int tot=dep[n];
	for(int i=n,nw=tot;i;nw--,i=f[i]) mk[i]=1,st[nw]=i;
	fr(i,1,tot) Dfs(st[i],0);
	//fr(i,1,n) printf("%lld ",l[i]);
	int flg=0;
	fr(i,1,tot) if(sz[st[i]]>=3) flg=1;
	if(flg) {
		fr(o,1,m) printf("%lld\n",dis[n]);
		return 0;
	}
	ll maxn=-1e18,pos=0;
	gg[st[1]]=l[st[1]],gg[2]=l[st[2]]+dis[st[2]];
	if(l[st[2]]|l[st[1]]) pos=max(pos,gg[st[1]]),maxn=max(maxn,pos+l[st[2]]-dis[st[2]]);
	fr(i,3,tot){
		if(l[st[i]]||l[st[i-1]]) pos=max(pos,gg[i-1]);
		pos=max(pos,gg[i-2]);
		maxn=max(maxn,pos+l[st[i]]-dis[st[i]]);
		gg[i]=l[st[i]]+dis[st[i]];
	}
	fr(o,1,m){
		ll x;scanf("%lld",&x);
		ll ans=min(dis[n],maxn+x+dis[n]);
		printf("%lld\n",ans);
	}
	return 0;
}