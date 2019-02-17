#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
#define pb push_back
using namespace std;
const int N=2010,M=20010;
vector<int>tr[N];
struct data{
	int x,y;
}g[M];
int dep[N],f[N],vis[N];

void dfs(int u,int fa){
	dep[u]=dep[fa]+1;f[u]=fa;
	int len=tr[u].size();
	fr(i,0,len-1){
		if(tr[u][i]==fa) continue;
		dfs(tr[u][i],u);
	}
}

bool cmp(data xx,data yy){
	if(dep[xx.y]!=dep[yy.y]) return dep[xx.y]>dep[yy.y];
	return dep[xx.x]>dep[yy.x];
}

int main(){
	int n,m;
	while(scanf("%d%d",&n,&m)==2&&(n||m)){
		memset(vis,0,sizeof vis);
		int fs=m-n+1;
		fr(i,1,n-1){
			int x,y;
			scanf("%d%d",&x,&y);
			tr[x].pb(y),tr[y].pb(x);
		}
		dep[1]=0;
		dfs(1,1);
		fr(i,1,fs){
			scanf("%d%d",&g[i].x,&g[i].y);
			if(dep[g[i].x]<dep[g[i].y]) swap(g[i].x,g[i].y);
		}
		sort(g+1,g+fs+1,cmp);
		int ans=0;
		fr(i,1,fs){
			int x=g[i].x,y=g[i].y;
			for(;f[x]!=y;){
				if(vis[x]) break;
				else x=f[x];
			}
			if(!vis[x]) vis[x]=1,ans++;
		}
		printf("%d\n",ans);
		fr(i,1,n) tr[i].clear();
	}
	return 0;
}
