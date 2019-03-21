#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1e4+10,M=5e4+10;
struct data{
  int fr,to,nt;
}a[M];
int cnt,top,res,nw;
int stk[N],head[N],nm[N],dp[N],d[N],dfn[N],low[N],col[N],vis[N];

void add(int x,int y){
  a[++cnt].fr=x,a[cnt].to=y,a[cnt].nt=head[x],head[x]=cnt;
}

void dfs(int u){
  low[u]=dfn[u]=++res;
  vis[u]=1,stk[++top]=u;
  for(int i=head[u];i;i=a[i].nt){
    int to=a[i].to;
    if(!dfn[to]) dfs(to),low[u]=min(low[u],low[to]);
    else if(vis[to]) low[u]=min(low[u],low[to]);
  }
  if(dfn[u]==low[u]){
    vis[u]=0,col[u]=++nw;
    while(stk[top]!=u){
      vis[stk[top]]=0,col[stk[top--]]=nw;
    }
    --top;
  }
}

int main(){
  int n,m;
  while(scanf("%d%d",&n,&m)==2){
    cnt=top=res=nw=0;
    memset(head,0,sizeof head),memset(d,0,sizeof d);
    memset(dfn,0,sizeof dfn),memset(nm,0,sizeof nm);
    memset(dp,0,sizeof dp);
    for(int i=1,x,y;i<=m;++i){
      scanf("%d%d",&x,&y);
      add(x,y);
    }
    fr(i,1,n) if(!dfn[i]) dfs(i);
    fr(i,1,n) nm[col[i]]++;
    //fr(i,1,n) printf("%d col=%d\n",i,col[i]);
    memset(head,0,sizeof head);
    cnt=0;
    fr(i,1,m){
      int pos=col[a[i].fr],tmp=col[a[i].to];
      if(pos==tmp) continue;
      d[pos]++;
    }
    int ans=0,gg=0;
    fr(i,1,nw)
      if(!d[i]) ans+=nm[i],gg++;
    if(gg==1) printf("%d\n",ans);
    else printf("0\n");
  }
  return 0;
}
