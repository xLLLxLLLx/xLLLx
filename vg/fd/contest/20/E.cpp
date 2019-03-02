#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=2010,M=N*N;
int cnt=0,res=0,top=0,n;
int Next[M],head[N],to[M],col[N];
int vis[N],sk[N],dfn[N],low[N];

void add(int x,int y){
	to[++cnt]=y,Next[cnt]=head[x],head[x]=cnt;
}

void dfs(int u,int fa){
	dfn[u]=low[u]=++res;
	sk[++top]=u,vis[u]=1;
	for(int i=head[u];i;i=Next[i]){
		if(vis[to[i]]) low[u]=min(low[u],low[to[i]]);
		else dfs(to[i],u),low[u]=min(low[u],low[to[i]]);
	}
	if(dfn[u]==low[u]){
		while(sk[top]!=u){
			col[sk[top]]=1;
			top--;
		}
		col[sk[top]]=1;
		fr(i,1,n) if(!col[i]){
			printf("NO\n");
			exit(0);
		}
		printf("YES\n");
		exit(0);
	}
}

int main(){
	scanf("%d",&n);
	fr(i,1,n) fr(j,1,n){
		int x;scanf("%d",&x);
		if(x&&i!=j) add(i,j);
	}
	dfs(1,0);
	return 0;
}
