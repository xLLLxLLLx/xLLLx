#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define db double
using namespace std;
const int N=1e5+10;
vector<int>g[N];
int dep[N];

void dfs(int u,int fa){
  int len=g[u].size();
  dep[u]=dep[fa]+1;
  fr(i,0,len-1)
    if(g[u][i]!=fa) dfs(g[u][i],u);
}

int main(){
  int n;scanf("%d",&n);
  for(int i=1,x,y;i<n;++i){
    scanf("%d%d",&x,&y);
    g[x].push_back(y);
    g[y].push_back(x);
  }
  dfs(1,0);
  db ans=0;
  fr(i,1,n) ans+=1.0/dep[i];
  printf("%.12f\n",ans);
  return 0;
}
