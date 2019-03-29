#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1e5+10,inf=1e9;
struct data{
  int nt,to;
}a[N<<1];
int cnt=0;
int ba[N],head[N],col[N],v[N];

template <class T>
void read(T &x){
    char ch=getchar();bool t=0;x=0;
    for(;ch<'0'||ch>'9';ch=getchar()) t|=(ch=='-');
    for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<3)+(x<<1)+(ch^48);
    if(t) x=-x;
}

void add(int x,int y){
  a[++cnt].to=y,a[cnt].nt=head[x],head[x]=cnt;
  a[++cnt].to=x,a[cnt].nt=head[y],head[y]=cnt;
}

#define ls ch[x][0]
#define rs ch[x][1]

struct LCT{
  int ch[N][2],f[N],w[N];
  multiset<int>xu[N];
  
  LCT(){
    w[0]=-inf;
  }
  
  int fir(int x){
    if(xu[x].size()) return *xu[x].rbegin();
    else return -inf;
  }
  
  void up(int x){
    int gg=fir(x);
    w[x]=max(max(w[ls],w[rs]),max(gg,v[x]));
  }
  
  bool isroot(int x){
    return (ch[f[x]][0]!=x)&&(ch[f[x]][1]!=x);
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
      if(rs) xu[x].insert(w[rs]);
      if(i) xu[x].erase(xu[x].find(w[i]));
      rs=i,up(x); 
    }
  }
  
  void link(int x){
    splay(x);
    int y=f[x]=ba[x];
    access(y),splay(y);
    ch[y][1]=x;
    up(y);
  }
  
  void cut(int x){
    access(x),splay(x);
    ls=f[ls]=0;
    up(x);
  }
  
  void change(int x){
    access(x),splay(x);
    read(v[x]);
    up(x);
  }
  
  int Ask(int x){
    access(x),splay(x);
    while(ls) x=ls;
    splay(x);
    return w[rs];
  }
  
}lct[2];

void dfs(int u,int fa){
  ba[u]=fa;
  for(int i=head[u];i;i=a[i].nt)
    if(a[i].to!=fa) dfs(a[i].to,u);
  lct[col[u]].link(u);
}

int main(){
  int n;read(n);
  for(int i=1,x,y;i<n;++i) {
    read(x),read(y);
    add(x,y);
  }
  fr(i,1,n) read(col[i]);
  fr(i,1,n) read(v[i]);
  dfs(1,n+1);
  int m;read(m);
  for(int i=1,x,y;i<=m;++i){
    read(x),read(y);
    if(!x) printf("%d\n",lct[col[y]].Ask(y));
    else if(x==1) lct[col[y]].cut(y),col[y]^=1,lct[col[y]].link(y);
    else lct[col[y]].change(y); 
  }
  return 0;
}
