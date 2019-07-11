#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=2e5+10,mod=998244353;
struct data{
	int nt,to;
}a[N<<1];
ll jc[N]={1},f[N];
int head[N],cnt=0;

void add(int x,int y){
	a[++cnt].to=y,a[cnt].nt=head[x],head[x]=cnt;
	a[++cnt].to=x,a[cnt].nt=head[y],head[y]=cnt;
}

void Add(ll &x,ll y){
	x=(x+y)%mod;
}

void Mul(ll &x,ll y){
	x=(x*y)%mod;
}

ll add(ll x,ll y){
	return (x+y)%mod;
}

ll mul(ll x,ll y){
	return x*y%mod;
}

void dfs(int u,int fa){
	f[u]=1;
	int son=0;
	for(int i=head[u];i;i=a[i].nt){
		int to=a[i].to;
		if(to==fa) {
			continue;
		}
		son++;
		dfs(to,u);
		Mul(f[u],f[to]);
	}
	if(u!=1) Mul(f[u],jc[son+1]);
	else {
		Mul(f[u],jc[son]);
	}
}

int main() {
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n+1;++i) jc[i]=mul(jc[i-1],i);
	for(int i=1,x,y;i<n;++i){
		scanf("%d%d",&x,&y);
		add(x,y);
	}
	dfs(1,0);
	printf("%lld\n",mul(f[1],n));
	return 0;
}