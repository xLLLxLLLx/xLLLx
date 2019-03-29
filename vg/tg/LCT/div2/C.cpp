#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
#define ls ch[x][0]
#define rs ch[x][1]
using namespace std;
const int N=1e5+10;
struct data{
  int nt,to;
}a[N<<1];
int cnt=0;
int head[N],col[N],f[N],ch[N][2],v[N];

void read(int &x){
  char ch=getchar();x=0;
  for(;ch<'0'||ch>'9';ch=getchar()) ;
  for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
}

void add(int x,int y){
  a[++cnt].to=y,a[cnt].nt=head[x],head[x]=cnt;
  a[++cnt].to=x,a[cnt].nt=head[y],head[y]=cnt;
}

struct LCT{
  
  bool isroot(int x){
    return (ch[f[x]][0]!=x)&&(ch[f[x]][1]!=x);
  }
  
  void up(int x){
    if(col[x]) v[x]=x;
    else v[x]=0;
    if(v[ls]) v[x]=v[ls];
  }
  
  void rotate(int x){
    int y=f[x],z=f[y];
    int d=(ch[z][1]==y),k=(ch[y][1]==x);
    if(!isroot(y)) ch[z][d]=x;
    f[x]=z;
    ch[y][k]=ch[x][k^1],f[ch[x][k^1]]=y;
    ch[x][k^1]=y,f[y]=x;
    up(y),up(x);
  }
  
  void splay(int x){
    while(!isroot(x)){
      if(!isroot(f[x])) rotate(x);
      rotate(x);
    }
    up(x);
  }
  
  void access(int x){
    for(int i=0;x;i=x,x=f[x]){
      splay(x),rs=i,up(x);
    }
  }
  
  int Get(int x){
    access(x),splay(x);
    if(v[x]) return v[x];
    else return -1;
  }
  
  void change(int x){
    access(x),splay(x);
    col[x]^=1;
    up(x);
  }
  
}lct;

void dfs(int u,int fa){
  f[u]=fa;
  for(int i=head[u];i;i=a[i].nt){
    if(a[i].to==fa) continue;
    dfs(a[i].to,u);
  }
}

int main(){
  int n,m;read(n),read(m);
  for(int i=1,x,y;i<n;++i){
    read(x),read(y);
    add(x,y);
  }
  dfs(1,0);
  for(int i=1,x,y;i<=m;++i){
    read(x),read(y);
    if(x) printf("%d\n",lct.Get(y));
    else lct.change(y);
  }
  return 0;
}
