#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1e4+10,M=1e5+10;
struct data{
  int nt,to;
}a[M],b[M];
int cnt,top,res,nw,maxn=0;
int dp[N],w[N],stk[N],head[N],nm[N],d[N],dfn[N],low[N],col[N],vis[N];

void add(int x,int y){
  a[++cnt].to=y,a[cnt].nt=head[x],head[x]=cnt;
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

queue<int>q;
vector<int>g[N];

void go(){
  memset(vis,0,sizeof vis);
  while(!q.empty()){
    int h=q.front();q.pop();
    vis[h]=0;
    int len=g[h].size();
    fr(i,0,len-1){
      int to=g[h][i];
      if(dp[to]<dp[h]+nm[to]){
        dp[to]=dp[h]+nm[to];
        if(!vis[to]) q.push(to),vis[to]=1;
      }
    }
  }
  fr(i,1,nw) maxn=max(maxn,dp[i]);
}

int main(){
  int n,m;scanf("%d%d",&n,&m);
  fr(i,1,n) scanf("%d",&w[i]);
  cnt=top=res=nw=0;
  for(int i=1,x,y;i<=m;++i){
    scanf("%d%d",&x,&y);
    add(x,y);
    b[i].nt=x,b[i].to=y;
  }
  fr(i,1,n) if(!dfn[i]) dfs(i);
  fr(i,1,n) nm[col[i]]+=w[i];
  fr(i,1,m){
    int pos=col[b[i].nt],tmp=col[b[i].to];
    if(pos==tmp) continue;
    g[pos].push_back(tmp);  
    d[tmp]++;
  }
  fr(i,1,nw){
    dp[i]=nm[i];
    if(!d[i]) q.push(i);
  }
  go();
  printf("%d\n",maxn);
  return 0;
}
