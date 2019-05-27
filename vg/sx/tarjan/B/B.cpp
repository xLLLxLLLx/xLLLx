#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
using namespace std;
const int N=1010;
struct data{
	int nt,to;
}a[N<<1];
int head[N],dfn[N],low[N],vis[N],cnt=0,res=0,num=0;

void add(int x,int y){
	a[++cnt].to=y,a[cnt].nt=head[x],head[x]=cnt;
	a[++cnt].to=x,a[cnt].nt=head[y],head[y]=cnt;
}

void dfs(int u,int fa){
	dfn[u]=low[u]=++res;
	int flg=0,son=0;
	for(int i=head[u];i;i=a[i].nt) {
		int to=a[i].to;
		if(to==fa) continue;
		if(!dfn[to]) {
			dfs(to,u);
			son++;
			low[u]=min(low[u],low[to]);
			if(low[to]>=dfn[u]) flg=1;
		} else {
			low[u]=min(low[u],dfn[to]);
		}
	}
	if(!fa) num+=(son>=2);
	else num+=flg;
}

int main(){
	int n;
	while(scanf("%d",&n)==1&&n) {
		cnt=res=num=0;
		for(int x;scanf("%d",&x)&&x;) {
			for(;getchar()!='\n';) {
				int y;scanf("%d",&y);
				add(x,y);
			}
		}
		dfs(1,0);
		printf("%d\n",num);
		fr(i,1,n) vis[i]=head[i]=dfn[i]=low[i]=0;
	}
	return 0;
}