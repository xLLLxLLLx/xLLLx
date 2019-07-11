#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;
typedef long long LL;
const LL N=200005;
LL n,m;
struct qq
{
	LL x,y,last;
}e[N*2];LL num,last[N];
void init (LL x,LL y)
{
	num++;e[num].x=x;e[num].y=y;
	e[num].last=last[x];
	last[x]=num;
}
vector<int> vec[N];
LL dfn[N],low[N],id;
LL sta[N],top,cnt;
LL TOT;//有多少个有用的点 
LL d[N];
void dfs (LL x)
{
	TOT++;
	top++;sta[top]=x;
	low[x]=dfn[x]=++id;
	for (LL u=last[x];u!=-1;u=e[u].last)
	{
		LL y=e[u].y;
		if (dfn[y]==0)
		{
			dfs(y);
			low[x]=min(low[x],low[y]);
			if (low[y]>=dfn[x])
			{
				cnt++;LL i;
				do
				{
					d[cnt]++;
					i=sta[top--];
				//	printf("%lld %lld %lld\n",cnt,i,cnt);
					vec[cnt].push_back(i);
					vec[i].push_back(cnt);
				}while (i!=y);
				d[cnt]++;
			//	printf("%lld %lld %lld\n",cnt,x,cnt);
				vec[x].push_back(cnt);
				vec[cnt].push_back(x);
			}
		}
		else low[x]=min(low[x],dfn[y]);
	}
}
LL tot[N];
LL ans;
void calc (LL x,LL fa)
{
	LL now=0;
	tot[x]=(x<=n);
	LL siz=vec[x].size();
	for (LL u=0;u<siz;u++)
	{
		LL y=vec[x][u];
		if (y!=fa)
		{
			calc(y,x);
		//	printf("%lld %lld %lld %lld\n",x,y,tot[y],now);
			if (x<=n)	ans=ans+tot[y]*now;
			else ans=ans+tot[y]*now*(d[x]-2);
			now=now+tot[y];tot[x]=tot[x]+tot[y];
		}
	}
	if (fa!=0)
	{
		if (x<=n) ans=ans+now*(TOT-tot[x]);
		else ans=ans+now*(TOT-tot[x])*(d[x]-2);
	}
}
int main()
{
	num=0;memset(last,-1,sizeof(last));
	scanf("%lld%lld",&n,&m);cnt=n;
	for (LL u=1;u<=m;u++)
	{
		LL x,y;
		scanf("%lld%lld",&x,&y);
		init(x,y);init(y,x);
	}
	for (LL u=1;u<=n;u++)
		if (dfn[u]==0)
		{
			TOT=0;
			dfs(u);
			calc(u,0);
		}
	printf("%lld\n",ans*2);
	return 0;
}
