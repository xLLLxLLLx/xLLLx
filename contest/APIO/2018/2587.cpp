#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
#include<cmath>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define frl(i,x,y) for(int i=x;i<y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=1e5+10,M=55;
struct data{
	int nt,to;
}a[N<<1];
ll ans=0;
int pd[M][M][M];
int dep[N],head[N],sz[N],vis[N],c[N];
int n,m,cnt=0,tot=0;

void add(int x,int y){
	a[++cnt].to=y,a[cnt].nt=head[x],head[x]=cnt;
	a[++cnt].to=x,a[cnt].nt=head[y],head[y]=cnt;
}

void dfs(int u,int fa){
	sz[u]=1;vis[u]=1;
	ans+=dep[u];
	for(int i=head[u];i;i=a[i].nt) {
		int to=a[i].to;
		if(to==fa) continue;
		dep[to]=dep[u]+1;
		dfs(to,u);
		sz[u]+=sz[to];
	}
}

void Dfs(int u,int fa,ll now){
	for(int i=head[u];i;i=a[i].nt) {
		int to=a[i].to;
		if(to==fa) continue;
		ll pos=now+1ll*(tot-2*sz[to]);
		Dfs(to,u,pos);
		ans+=pos;
	}
}

void go(int x){
	int flg=0;
	for(int i=head[x];i;i=a[i].nt) {
		int to=a[i].to;
		if(vis[to]) continue;
		c[++c[0]]=to,vis[to]=1;
		go(to);
		c[0]--,vis[to]=0;
		flg=1;
	}
	if(!flg) {
		// fr(j,1,c[0]) printf("%d ",c[j]);
		// puts("");
		fr(j,2,c[0]) fr(k,j+1,c[0]) {
			pd[c[1]][c[j]][c[k]]=1;
		}
	}
}

int main(){
	scanf("%d%d",&n,&m);
	fr(i,1,m) {
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);
	}
	if(n<=50) {
		fr(i,1,n) {
			memset(vis,0,sizeof vis);
			c[0]=0;
			c[++c[0]]=i;vis[i]=1;
			go(i);
		}
		int ans=0;
		fr(i,1,n) fr(j,1,n) fr(k,1,n) {
			ans+=pd[i][j][k];
			// if(pd[i][j][k]) printf("%d %d %d\n",i,j,k);
		}
		printf("%d\n",ans);
		return 0;
	}
	ll sum=0;
	fr(i,1,n) {
		if(vis[i]) continue;
		ans=0;
		dfs(i,0);
		tot=sz[i];
		Dfs(i,0,ans);
		ans-=1ll*(sz[i]-1)*sz[i];
		sum+=ans;
	}
	printf("%lld\n",sum);
	return 0;
}