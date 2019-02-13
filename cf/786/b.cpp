#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
#define lson (x<<1)
#define rson (x<<1|1)
using namespace std;
const int N=1e5+10,M=N*40;
struct data{
	int nt,to;
	LL w;
}a[M];
struct node{
	int u;
	LL d;
	bool operator < (const node &C) const{
		return d>C.d;
	}
};
LL dis[M];
int head[M],vis[M],cnt=0,n1=0;
int n,m,s;

void add(int x,int y,LL w){
//	printf("%d %d %lld\n",x,y,w);
	a[++cnt].to=y,a[cnt].w=w,a[cnt].nt=head[x],head[x]=cnt;
}

void build(int x,int l,int r){
	n1=max(n1,x);
	if(l==r){
		add(n+x,l,0);
		return ;
	}
	int mid=(l+r)>>1;
	add(n+x,n+lson,0),add(n+x,n+rson,0);
	build(lson,l,mid),build(rson,mid+1,r);
}

void Build(int x,int l,int r){
	if(l==r){
		add(l,n+n1+x,0);
		return ;
	}
	int mid=(l+r)>>1;
	add(n+n1+lson,n+n1+x,0),add(n+n1+rson,n+n1+x,0);
	Build(lson,l,mid),Build(rson,mid+1,r);
}

void Do(int x,int l,int r,int u,int L,int R,LL k){
	if(L<=l&&r<=R){
		add(u,n+x,k);
		return ;
	}
	int mid=(l+r)>>1;
	if(L<=mid) Do(lson,l,mid,u,L,R,k);
	if(R>mid) Do(rson,mid+1,r,u,L,R,k);
}

void Go(int x,int l,int r,int L,int R,int u,LL k){
	if(L<=l&&r<=R) {
		add(n+n1+x,u,k);
		return ;
	}
	int mid=(l+r)>>1;
	if(L<=mid) Go(lson,l,mid,L,R,u,k);
	if(R>mid) Go(rson,mid+1,r,L,R,u,k);
}

priority_queue<node>q;

void Dijstra(){
	memset(dis,-1,sizeof dis);
	dis[s]=0;
	q.push((node){s,0});
	while(!q.empty()){
		node h=q.top();q.pop();
		if(vis[h.u]) continue;
		vis[h.u]=1;
		for(int i=head[h.u];i;i=a[i].nt){
	//		printf("%d ",a[i].to);
			if(vis[a[i].to]) continue;
			if(dis[a[i].to]==-1||dis[a[i].to]>dis[h.u]+a[i].w) {
				dis[a[i].to]=dis[h.u]+a[i].w;
				q.push((node){a[i].to,dis[a[i].to]});
			}
		}
	}
}

int main(){
	scanf("%d%d%d",&n,&m,&s);
	build(1,1,n),Build(1,1,n);
	fr(i,1,m){
		int id,x,y,z;
		LL k;
		scanf("%d",&id);
		if(id==1){
			scanf("%d%d%lld",&x,&y,&k);
			add(x,y,k);
		}
		else if(id==2){
			scanf("%d%d%d%lld",&x,&y,&z,&k);
			Do(1,1,n,x,y,z,k);
		} else {
			scanf("%d%d%d%lld",&x,&y,&z,&k);
			Go(1,1,n,y,z,x,k);
		}
	}
	Dijstra();
	fr(i,1,n) printf("%lld ",dis[i]);
	return 0;
}
