#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
#include<vector>
#include<cmath>

#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=2e5+10;
struct data{
	int nt,to,w;
}a[2][N<<1];
ll ans=0;
int res=0;
int q[N],sz[2][N],head[2][N],vis[2][N],cnt[2];

void add(int x,int y,int w){
	a[w][++cnt[w]].to=y,a[w][cnt[w]].nt=head[w][x],head[w][x]=cnt[w];
	a[w][++cnt[w]].to=x,a[w][cnt[w]].nt=head[w][y],head[w][y]=cnt[w];
}

void dfs(int u,int w){
	q[++res]=u;vis[w][u]=1;
	for(int i=head[w][u];i;i=a[w][i].nt){
		int to=a[w][i].to;
		if(vis[w][to]) continue;
		dfs(to,w);
	}
}

int main(){
	int n;scanf("%d",&n);
	for(int i=1,x,y,w;i<n;++i){
		scanf("%d%d%d",&x,&y,&w);
		add(x,y,w);
	}
	ll ans=0;
	fr(o,0,1){
		fr(i,1,n){
			if(vis[o][i]) continue;
			dfs(i,o);
			if(res==1) {res=0;continue;}
			fr(j,1,res) sz[o][q[j]]=res;
			// printf("res=%d\n",res);
			// fr(j,1,res) printf("%d ",q[j]);
			// puts("");
			ans+=res*1ll*(res-1);
			res=0;
		}
	}
	fr(i,1,n){
		if(!sz[0][i]||!sz[1][i]) continue;
		ans+=(sz[0][i]-1)*1ll*(sz[1][i]-1);
	}
	printf("%lld\n",ans);
	return 0;
}