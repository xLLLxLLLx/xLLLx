#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=1e4+10,M=2e5+10;
struct data{
	int nt,to;
}a[M];
vector<int>g[N];
int head[N],vs[N],mk[M],f[N],vis[M],dfn[N],low[N],cnt=0,res=0,num=0;

void add(int x,int y){
	a[++cnt].to=y,a[cnt].nt=head[x],head[x]=cnt;
	a[++cnt].to=x,a[cnt].nt=head[y],head[y]=cnt;
}

void dfs(int u,int fa){
	low[u]=dfn[u]=++res;
	for(int i=head[u];i;i=a[i].nt){
		int to=a[i].to;
		if(to==fa) continue;
		if(!dfn[to]) {
			dfs(to,u);
			low[u]=min(low[to],low[u]);
			if(!vis[i]&&low[to]>dfn[u]) {
				num++;
				mk[(i+1)/2]=1;
			}
		}
		else {
			low[u]=min(low[u],dfn[to]);
		}
	}
}

void Dfs(int u,int fa){
	int pos=0;
	vs[u]=1;
	for(int i=head[u];i;i=a[i].nt) {
		int to=a[i].to;
		if(to==fa) {
			g[u].push_back(i);
			pos++;
			continue;
		}
		if(vs[to]) continue;
		Dfs(to,u);
	}
	if(pos>=2) {
		int len=g[u].size();
		fr(i,0,len-1) {
			vis[g[u][i]]=1;
			if(g[u][i]&1) vis[g[u][i]+1]=1;
			else vis[g[u][i]-1]=1;
		}
	}
}

int main(){
	int T;scanf("%d",&T);
	fr(o,1,T) {
		cnt=0,res=0,num=0;
		int n,m;
		scanf("%d%d",&n,&m);
		fr(i,1,m) {
			int x,y;
			scanf("%d%d",&x,&y);
			add(x,y);
		}
		Dfs(1,0),dfs(1,0);
		printf("%d\n",num);
		fr(i,1,m) {
			if(mk[i]) {
				num--;
				printf("%d",i);
				if(num) printf(" ");
				else printf("\n");
			}
			mk[i]=vis[i]=0;
		}
		fr(i,1,n) {
			head[i]=f[i]=low[i]=dfn[i]=0;
			vs[i]=0;
			g[i].clear();
		}
		if(o!=T) printf("\n");
	}
	return 0;
}