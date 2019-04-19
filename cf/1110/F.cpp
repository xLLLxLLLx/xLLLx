#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ls (x<<1)
#define rs (x<<1|1)
#define ll long long
using namespace std;
const int N=5e5+10;
const ll inf=5e14;
struct data{
	int nt,to;
	ll w;
}a[N<<1];
struct node{
	int l,r,id;
};
ll dis[N],d[N],tag[N<<2],v[N<<2];
vector<node>g[N];
int head[N],ed[N],vis[N],cnt=0,n,m;

template <class T>
void read(T &x){
	char ch=getchar();x=0;
	for(;ch<'0'||ch>'9';ch=getchar()) ;
	for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
}

void add(int x,int y,ll w){
	a[++cnt].to=y,a[cnt].w=w,a[cnt].nt=head[x],head[x]=cnt;
	a[++cnt].to=x,a[cnt].w=w,a[cnt].nt=head[y],head[y]=cnt;
}

void dfs(int u,int fa){
	ed[u]=u;
	int flg=0;
	for(int i=head[u];i;i=a[i].nt){
		if(a[i].to==fa) continue;
		flg=1;
		dis[a[i].to]=dis[u]+a[i].w,dfs(a[i].to,u);
		ed[u]=max(ed[u],ed[a[i].to]);
	}
	if(!flg) vis[u]=1;
}

void up(int x){
	v[x]=min(v[ls],v[rs]);
}

void build(int x,int l,int r){
	if(l==r){
		if(vis[l]) v[x]=dis[l];
		return ;
	}
	int mid=(l+r)>>1;
	build(ls,l,mid),build(rs,mid+1,r);
	up(x);
}

void down(int x){
	if(tag[x]){
		v[ls]+=tag[x],tag[ls]+=tag[x];
		v[rs]+=tag[x],tag[rs]+=tag[x];
		tag[x]=0;
	}
}

void change(int x,int l,int r,int L,int R,ll k){
	if(L<=l&&r<=R){
		v[x]+=k;
		tag[x]+=k;
		return ;
	}
	down(x);
	int mid=(l+r)>>1;
	if(L<=mid) change(ls,l,mid,L,R,k);
	if(R>mid) change(rs,mid+1,r,L,R,k);
	up(x);
}

ll Get(int x,int l,int r,int L,int R){
	if(L<=l&&r<=R) return v[x];
	down(x);
	int mid=(l+r)>>1;
	if(R<=mid) return Get(ls,l,mid,L,R);
	else if(L>mid) return Get(rs,mid+1,r,L,R);
	else return min(Get(ls,l,mid,L,R),Get(rs,mid+1,r,L,R));
}

void Dfs(int u,int fa){
	int len=g[u].size();
	fr(i,0,len-1) d[g[u][i].id]=Get(1,1,n,g[u][i].l,g[u][i].r);
	for(int i=head[u];i;i=a[i].nt){
		if(a[i].to==fa) continue;
		int to=a[i].to;
		change(1,1,n,1,n,a[i].w),
		change(1,1,n,to,ed[to],-a[i].w-a[i].w);
		Dfs(to,u);
		change(1,1,n,to,ed[to],a[i].w+a[i].w),
		change(1,1,n,1,n,-a[i].w);
	}
}

int main(){
	read(n),read(m);
	for(int i=2;i<=n;++i){
		int y;ll w;
		read(y),read(w),add(i,y,w);
	}
	fr(i,1,m){
		int v,l,r;
		read(v),read(l),read(r);
		g[v].push_back((node){l,r,i});
	}
	fr(i,1,n*4) v[i]=inf;
	dfs(1,0);
	build(1,1,n);
	Dfs(1,0);
	fr(i,1,m) printf("%lld\n",d[i]);
	return 0;
}