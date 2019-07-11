#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e5+7,M=31700000;
struct query{ll n,k;int id;}q[N];
int t,cnt,qs,qe,l,ans[N],vis[M],pri[M],que[N*20];
ll p[N],f[N];
bool cmp(query a,query b){return a.k<b.k;}
ll qpow(ll a,ll b,ll mod)
{
	ll ret=1;
	while(b)
	{
		if(b&1)ret=ret*a%mod;
		a=a*a%mod,b>>=1;
	}
	return ret;
}
int main()
{
	scanf("%d",&t);
	for(int i=1;i<=t;i++)scanf("%lld%lld",&q[i].n,&q[i].k),q[i].id=i;
	sort(q+1,q+t+1,cmp);
	for(int i=2;i<M;i++)
	{
		if(!vis[i])pri[++cnt]=i;
		for(int j=1;j<=cnt&&i*pri[j]<M;j++)
		{
			vis[i*pri[j]]=1;
			if(i%pri[j]==0)break;
		}
	}
	for(int i=1;i<M;i++)vis[i]=0;
	for(int i=1;i<=t;i++)
	{
		ll n=q[i].n,k=q[i].k;
		if(k!=q[i-1].k)
		{
			l=0;
			for(int j=1;k>1;j++)
			{
				if(1ll*pri[j]*pri[j]>k){p[++l]=k;break;}
				if(k%pri[j]==0)
				{
					p[++l]=pri[j];
					while(k%pri[j]==0)k/=pri[j];
				}
			}
		}
		k=q[i].k;
		if(!l)ans[q[i].id]=0;
		else if(l==1)ans[q[i].id]=n%k==0;
		else if(l==2)ans[q[i].id]=n%p[1]*qpow(p[2],p[1]-2,p[1])%p[1]*p[2]<=n;
		else{
			if(k!=q[i-1].k)
			{
				f[0]=0;
				for(int j=1;j<=p[1];j++)f[j]=1e18;
				qs=0,qe=1,vis[que[0]=0]=1;
				while(qs!=qe)
				{
					int u=que[qs++];
					for(int j=2;j<=l;j++)
					{
						ll dis=f[u]+p[j];
						int v=(u+p[j])%p[1];
						if(dis<f[v])
						{
							f[v]=dis;
							if(!vis[v])vis[que[qe++]=v]=1;
						}
					}
					vis[u]=0;
				}
			}
			ans[q[i].id]=f[q[i].n%p[1]]<=q[i].n;
		}
	}
	for(int i=1;i<=t;i++)if(ans[i])puts("YES");else puts("NO");
}