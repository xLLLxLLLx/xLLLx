#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=5e5+10;
struct data{
	int nt,to;
}a[N],b[N];
queue<int>q;
int dp[N],vis[N],d[N];
int head[N],hea[N],dfn[N],low[N],val[N],mk[N],stk[N],v[N],col[N];
int cnt=0,num=0,res=0,top=0;

void add(int x,int y){
	a[++cnt].to=y,a[cnt].nt=head[x],head[x]=cnt;
}

void Add(int x,int y){
	if(x==y) return ;
	b[++cnt].to=y,b[cnt].nt=hea[x],hea[x]=cnt;
}

void dfs(int u){
	vis[u]=1;
  dfn[u]=low[u]=++res;
  stk[++top]=u;
  for(int i=head[u];i;i=a[i].nt){
    int to=a[i].to;
    if(!dfn[to]) dfs(to),low[u]=min(low[u],low[to]);
    else if(vis[to]==1) low[u]=min(low[u],dfn[to]);
  }
  if(dfn[u]==low[u]){
  	vis[u]=0,col[u]=++num;
    while(stk[top]!=u){
      vis[stk[top]]=0,col[stk[top--]]=num;
    }
    top--;
  }
}

int main(){
	// freopen("1.in","r",stdin);
	int n,m;
	scanf("%d%d",&n,&m);
	fr(i,1,m) {
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);
	}
	fr(i,1,n) {
		scanf("%d",&val[i]);
	}
	fr(i,1,n) {
		if(!dfn[i]) {
			dfs(i);
		}
	}
	cnt=0;
	int s,p;
	scanf("%d%d",&s,&p);
	fr(i,1,p) {
		int x;scanf("%d",&x);
		mk[col[x]]=1;
	}
	fr(u,1,n) {
		v[col[u]]+=val[u];
		for(int i=head[u];i;i=a[i].nt) {
			Add(col[u],col[a[i].to]);
		}
	}
	int ans=0;
	memset(vis,0,sizeof vis);
	q.push(col[s]),vis[col[s]]=1,dp[col[s]]=v[col[s]];
	while(!q.empty()) {
		int u=q.front();
		q.pop();vis[u]=0;
		for(int i=hea[u];i;i=b[i].nt) {
			int to=b[i].to;
			if(dp[to]<dp[u]+v[to]) {
				dp[to]=dp[u]+v[to];
				if(!vis[to]) q.push(to),vis[to]=1;
			}
		}
	}
	fr(i,1,num) {
		if(mk[i]) ans=max(ans,dp[i]);
	}
	printf("%d\n",ans);
	return 0;
}