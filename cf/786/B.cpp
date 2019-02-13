#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn=1e5*40;
struct edge
{
	int u,v;
	LL d;
};
struct node
{
	int u;
	LL d;
	bool operator < (const node &o) const
	{
		return d>o.d;
	}
};
int n,n1,m,s;
LL dis[maxn];
bool done[maxn];
vector<edge> e;
vector<int> G[maxn];
void add(int u,int v,LL d)
{
	e.push_back((edge){u,v,d});
	int k=e.size();
	G[u].push_back(k-1);
}
void build(int o,int l,int r)
{
	n1=max(n1,o);
	if (l==r)
	{
		add(n+o,l,0);
		return ;
	}
	int mid=(l+r)/2;
	add(n+o,n+2*o,0);add(n+o,n+2*o+1,0);
	build(2*o,l,mid);build(2*o+1,mid+1,r);
}
void build2(int o,int l,int r)
{
	if (l==r)
	{
		add(l,n+n1+o,0);
		return ;
	}
	int mid=(l+r)/2;
	add(n+n1+2*o,n+n1+o,0);add(n+n1+2*o+1,n+n1+o,0);
	build2(2*o,l,mid);build2(2*o+1,mid+1,r);
}
void make(int o,int l,int r,int L,int R,int u,LL d)
{
	if (L<=l&&r<=R)
	{
		add(u,n+o,d);
		return ;
	}
	int mid=(l+r)/2;
	if (L<=mid) make(2*o,l,mid,L,R,u,d);
	if (R>mid) make(2*o+1,mid+1,r,L,R,u,d);
}
void make2(int o,int l,int r,int L,int R,int u,LL d)
{
	if (L<=l&&r<=R)
	{
		add(n+n1+o,u,d);
		return ;
	}
	int mid=(l+r)/2;
	if (L<=mid) make2(2*o,l,mid,L,R,u,d);
	if (R>mid) make2(2*o+1,mid+1,r,L,R,u,d);
}
void dijkstra()
{
	priority_queue<node> Q;
	dis[s]=0;
	Q.push((node){s,0});
	while (!Q.empty())
	{
		node nd=Q.top();Q.pop();
		int u=nd.u;
		if (done[u]) continue;
		done[u]=1;
		for (int i=0;i<G[u].size();i++)
		{
			edge e1=e[G[u][i]];
			int v=e1.v;
			if (dis[v]==-1||dis[v]>dis[u]+e1.d)
			{
				dis[v]=dis[u]+e1.d;
				Q.push((node){v,dis[v]});
			}
		}
	}
}
int main()
{
	memset(dis,-1,sizeof(dis));
	cin>>n>>m>>s;
	build(1,1,n);
	build2(1,1,n);
	for (int i=1;i<=m;i++)
	{
		int t,u;
		LL d;
		scanf("%d%d",&t,&u);
		if (t==1)
		{
			int v;
			scanf("%d%I64d",&v,&d);
			add(u,v,d);
		}
		if (t==2)
		{
			int l,r;
			scanf("%d%d%I64d",&l,&r,&d);
			make(1,1,n,l,r,u,d);
		}
		if (t==3)
		{
			int l,r;
			scanf("%d%d%I64d",&l,&r,&d);
			make2(1,1,n,l,r,u,d);
		}
	}
	dijkstra();
	for (int i=1;i<=n;i++) printf("%I64d ",dis[i]);
	return 0;
}
