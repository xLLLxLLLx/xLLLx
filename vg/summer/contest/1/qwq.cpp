#include<bits/stdc++.h>
using namespace std;
#define MN 100000
#define K 17
#define MX 10000000
#define MOD 1000000007
struct edge{int nx,t;}e[MN*2+5];
int h[MN+5],en,a[MN+5],u[MX+5],p[MX+5],pn,fa[K][MN+5],d[MN+5],ans[MN+5],s[MX+5],xx[MN+5];
vector< pair<int,int> > v[MN+5];
void pre(int x)
{
	for(int i=h[x];i;i=e[i].nx)if(e[i].t!=fa[0][x])
		d[e[i].t]=d[x]+1,fa[0][e[i].t]=x,pre(e[i].t);
}
void dfs(int x)
{
	int i,j,k,t;
	for(i=a[x];i>1;)for(j=t=u[i];i%t==0;i/=t,j*=t)s[j]=1LL*s[j]*t%MOD;
	for(k=0;k<v[x].size();++k)
		for(i=xx[v[x][k].first];i>1;)for(j=t=u[i];i%t==0;i/=t,j*=t)
			ans[v[x][k].first]=1LL*ans[v[x][k].first]*(v[x][k].second?inv(s[j]):s[j])%MOD;
	for(i=h[x];i;i=e[i].nx)if(e[i].t!=fa[0][x])dfs(e[i].t);
	for(i=a[x];i>1;)for(j=t=u[i];i%t==0;i/=t,j*=t)s[j]=1LL*s[j]*inv(t)%MOD;
}
int main()
{
	int n=read(),q,i,j,x,y;
	for(i=1;i<n;++i)ins(read(),read());
	for(i=1;i<=n;++i)a[i]=read();
	for(i=2;i<=MX;++i)
	{
		if(!u[i])u[i]=p[++pn]=i;
		for(j=1;i*p[j]<=MX;++j)if(u[i*p[j]]=p[j],i%p[j]==0)break;
	}
	pre(1);
	for(i=1;i<K;++i)for(j=1;j<=n;++j)fa[i][j]=fa[i-1][fa[i-1][j]];
	for(q=read(),i=1;i<=q;++i)
	{
		ans[i]=1;
		j=lca(x=read(),y=read());xx[i]=read();
		v[x].push_back(make_pair(i,0));
		v[y].push_back(make_pair(i,0));
		v[j].push_back(make_pair(i,1));
		v[fa[0][j]].push_back(make_pair(i,1));
	}
	for(i=1;i<=MX;++i)s[i]=1;
	dfs(1);
	for(i=1;i<=q;++i)printf("%d\n",ans[i]);
}