#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1e5+10;
struct data{
  int nt,to;
}g[N<<1];
int n,cnt=0;
int head[N],col[N],ba[N];

void read(int &x){
  char ch=getchar();x=0;
  for(;ch<'0'||ch>'9';ch=getchar()) ;
  for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
}

void add(int x,int y){
  g[++cnt].to=y,g[cnt].nt=head[x],head[x]=cnt;
  g[++cnt].to=x,g[cnt].nt=head[y],head[y]=cnt;
}

#define ls ch[x][0]
#define rs ch[x][1]

struct LCT{
  int ch[N][2],s[N],f[N],si[N];
  
  LCT(){
    fr(i,1,n) s[i]=1;
  }
  
  bool isroot(int x){
    return (ch[f[x]][0]!=x)&&(ch[f[x]][1]!=x);
  }
  
  void up(int x){
    s[x]=s[ls]+s[rs]+si[x]+1;
  }
  
  void rotate(int x){
    int y=f[x],z=f[y];
    int d=(ch[y][1]==x),k=(ch[z][1]==y);
    if(!isroot(y)) ch[z][k]=x;
    f[x]=z;
    ch[y][d]=ch[x][d^1],f[ch[x][d^1]]=y;
    ch[x][d^1]=y,f[y]=x;
    up(y),up(x);
  }
  
  void splay(int x){
    while(!isroot(x)){
      int y=f[x],z=f[y];
      if(!isroot(y))
        (ch[z][1]==y)^(ch[y][1]==x) ? rotate(x) : rotate(y);
      rotate(x);
    }
    up(x);
  }
  
  void access(int x){
    for(int i=0;x;i=x,x=f[x]){
      splay(x);
      si[x]-=s[i];
      si[x]+=s[rs];
      rs=i,up(x);
    }
  }
  
  void link(int x){
    splay(x);
    int y=ba[x];
    f[x]=ba[x];
    access(y),splay(y);
    si[y]+=s[x];
    up(y);
  }
  
  void cut(int x){
    access(x),splay(x);
    f[ls]=0,ls=0;
    up(x);
  }
  
  int findroot(int x){
    access(x),splay(x);
    while(ls) x=ls;
    splay(x);
    return x;
  }
  
}lct[2];

void dfs(int u){
  for(int i=head[u];i;i=g[i].nt)
    if(g[i].to!=ba[u]) {
      ba[g[i].to]=u,dfs(g[i].to),lct[0].link(g[i].to);
    }
}

int main(){
//  freopen("out","r",stdin);
  read(n);
  for(int i=1,x,y;i<n;++i){
    read(x),read(y);
    add(x,y);
  }
  dfs(1);
  ba[1]=n+1,lct[0].link(1);
  int m;read(m);
  for(int i=1,x,y;i<=m;++i){
    read(x),read(y);
    if(x) lct[col[y]].cut(y),lct[col[y]^=1].link(y);
    else {
      int v=lct[col[y]].findroot(y);
      printf("%d\n",lct[col[y]].s[lct[col[y]].ch[v][1]]); 
    }
  }
  return 0;
}
