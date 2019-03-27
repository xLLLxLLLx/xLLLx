#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
using namespace std;
const int N=1e5+10;
const int inf=233333;
struct data{
  int nt,to;
}a[N<<1];
multiset<int>cl[N];
int cnt=0;
int head[N],w[N],col[N],ch[N][2],len[N],f[N],rmn[N],lmn[N],sum[N];

void read(int &x){
  char ch=getchar();x=0;
  for(;ch<'0'||ch>'9';ch=getchar()) ;
  for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
}

#define ls ch[x][0]
#define rs ch[x][1]

struct LCT{
  
  int fi(int x){
    if(cl[x].size()) return *cl[x].begin();
    else return inf;
  }

  void up(int x){
    sum[x]=sum[ls]+sum[rs]+len[x];
    int G=min(w[x],fi(x));
    int L=min(G,rmn[ls]+len[x]);
    int R=min(G,lmn[rs]);
    rmn[x]=min(rmn[rs],sum[rs]+L);
    lmn[x]=min(lmn[ls],sum[ls]+len[x]+R);
  }

  bool isroot(int x){
    return (ch[f[x]][0]!=x)&&(ch[f[x]][1]!=x);
  }

  void rotate(int x){
    int y=f[x],z=f[y];
    int k=(ch[z][1]==y),d=(ch[y][1]==x);
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
      if(i) cl[x].erase(cl[x].find(lmn[i]));
      if(rs) cl[x].insert(lmn[rs]);
      rs=i,up(x);
    }
  }

  void change(int x){
    access(x),splay(x);
    col[x]^=1;
    if(col[x]) w[x]=0;
    else w[x]=inf;
    up(x);
  }

  int Get(int x){
    access(x),splay(x);
    if(rmn[x]!=inf)  return rmn[x];
    else return -1;
  }

}lct;


void dfs(int u,int fa){
  f[u]=fa;
  for(int i=head[u];i;i=a[i].nt){
    if(a[i].to==fa) continue;
    len[a[i].to]=1,dfs(a[i].to,u);
    cl[u].insert(lmn[a[i].to]);
  }
  lct.up(u);
}

void add(int x,int y){
  a[++cnt].to=y,a[cnt].nt=head[x],head[x]=cnt;
  a[++cnt].to=x,a[cnt].nt=head[y],head[y]=cnt;
}

int main(){
  int n;read(n);
  for(int i=1,x,y;i<n;++i){
    read(x),read(y);
    add(x,y);
  }
  fr(i,0,n) rmn[i]=lmn[i]=w[i]=inf;
  dfs(1,0);
  int m;read(m);
  fr(o,1,m){
    int x,y;
    read(x),read(y);
    if(x) printf("%d\n",lct.Get(y));
    else lct.change(y);
  } 
  return 0;
}
