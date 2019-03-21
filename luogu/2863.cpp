#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=5e4+10;
struct data{
  int nt,to;
}a[N];
int stk[N],head[N],vis[N],col[N],nm[N],dfn[N],low[N];
int top=0,cnt=0,res=0,nw=0;

void add(int x,int y){
  a[++cnt].to=y,a[cnt].nt=head[x],head[x]=cnt;
}

void dfs(int u){
  dfn[u]=low[u]=++res;
  stk[++top]=u,vis[u]=1;
  for(int i=head[u];i;i=a[i].nt){
    int to=a[i].to;
    if(!dfn[to])
      dfs(to),
      low[u]=min(low[u],low[to]);
    else low[u]=min(low[u],low[to]);
  }
  if(low[u]==dfn[u]){
    vis[u]=0,col[u]=++nw;
    while(stk[top]!=u){
      vis[stk[top]]=0,col[stk[top--]]=nw;
    }
    top--;
  }
}

int main(){
  int n,m;scanf("%d%d",&n,&m);
  for(int i=1,x,y;i<=m;++i){
    scanf("%d%d",&x,&y);
    add(x,y);
  }
  fr(i,1,n) if(!dfn[i]) dfs(i);
  //fr(i,1,n) printf("%d col=%d\n",i,col[i]);
  fr(i,1,n) nm[col[i]]++;
  int ans=0;
  fr(i,1,nw) ans+=(nm[i]>1);
  printf("%d\n",ans);
  return 0;
}
