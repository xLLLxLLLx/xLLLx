#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
#include<cmath>
#define P pair<int,int>
#define mp make_pair
#define fi first
#define se second
#define INF 0x3f3f3f3f
#define N 20
#define M 20010
using namespace std;

int n,m,dp[M],ct[M],a[M],b[M],c[M];
bool f[N][N][M];
vector<int>to[N];
vector<P>ans;

inline void Min(int &u,int v){if(v<u) u=v;}
void dfs(int now,int zt,int st)
{
	if(now==st&&zt) return;
	int i,t;
	for(i=0;i<to[now].size();i++)
	{
		t=to[now][i];
		if((1 << (t-1))&zt) continue;
		if(ct[zt]==1&&t==st) continue;
		if(f[st][t][zt]) continue;
		f[st][t][zt]=1;
		dfs(t,(1 << (t-1))|zt,st);
	}
}

void out(int u,int v,int w)
{
	if(!w)
	{
		ans.push_back(mp(u,v));
		return;
	}
	int i,t;
	for(i=0;i<to[u].size();i++)
	{
		t=to[u][i];
		if(!((1 << (t-1))&w)) continue;
		if(!f[t][v][(1 << (t-1))^w]) continue;
		ans.push_back(mp(u,t));
		out(t,v,w^(1 << (t-1)));
		return;
	}
}

int main()
{
	memset(dp,0x3f,sizeof(dp));
	int i,j,k,p,q,t;
	cin>>n>>m;
	for(i=1;i<=m;i++)
	{
		scanf("%d%d",&p,&q);
		to[p].push_back(q);
		to[q].push_back(p);
	}
	for(i=1;i<(1 << n);i++) ct[i]=ct[i^(i&(-i))]+1;
	for(i=1;i<=n;i++) dfs(i,0,i);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int t = 0; t < (1 << n); t++) {
				if(f[i+1][j+1][t]) {
					printf("f[%d][%d][%d]\n", i,j,t);
				}
			}
		}
	}
	for(i=0;i<n;i++) dp[(1 << i)]=0;
	for(i=1;i<(1 << n);i++)
	{
		for(p=1;p<=n;p++)
		{
			if(!((1 << (p-1))&i)) continue;
			for(q=p;q<=n;q++)
			{
				if(!((1 << (q-1))&i)) continue;
				t=((1 << n)-1)^i;
				for(j=t;j;j=(j-1)&t)
				{
					if(!f[p][q][j]) continue;
					if(dp[i]+ct[j]+1<dp[i|j])
					{
						dp[i|j]=dp[i]+ct[j]+1;
						a[i|j]=p,b[i|j]=q,c[i|j]=j;
					}
				}
			}
		}
	}
	for(i=(1 << n)-1;ct[i]>1;i=i^c[i])
	{
		out(a[i],b[i],c[i]);
	}
	cout<<ans.size()<<endl;
	for(i=0;i<ans.size();i++)
	{
		printf("%d %d\n",ans[i].fi,ans[i].se);
	}
}
