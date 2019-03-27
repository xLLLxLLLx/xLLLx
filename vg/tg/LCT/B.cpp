#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
#define ls ch[x][0]
#define rs ch[x][1]
using namespace std;
const int N=1e4+10;
struct data{
  int nt,to,w;
}a[N<<1];
int ch[N][2],sum[N],v[N],tag[N],sz[N];
int f[N],head[N],cnt=0;

void read(int &x){
  char ch=getchar();x=0;
  for(;ch<'0'||ch>'9';ch=getchar()) ;
  for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<3)+(x<<1)+(ch^48);
}

struct LCT{

  void up(int x){
    sum[x]=sum[ls]+sum[rs]+v[x];
    sz[x]=sz[ls]+sz[rs]+1;
  }
  
  bool isroot(int x){
    return (ch[f[x]][0]!=x)&&(ch[f[x]][1]!=x);
  }

  void down(int x){
    if(tag[x]){
      tag[x]^=1;
      swap(ls,rs);
      tag[ls]^=1,tag[rs]^=1;
    }
  }

  void pushdown(int x){
    if(!isroot(x)) pushdown(f[x]);
    down(x);
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
    pushdown(x);
    while(!isroot(x)){
      int y=f[x],z=f[y];
      if(!isroot(y)) rotate(x);
      rotate(x);
    }
    up(x);
  }
  
  void access(int x){
    for(int i=0;x;i=x,x=f[x]){
      splay(x),rs=i,up(x);
    }
  }
  
  void reverse(int x){
    access(x),splay(x),tag[x]^=1;
  }
  
  int find(int x,int k){
    int gg=sz[ls]+1;
    if(gg>k) return find(ls,k);
    else if(gg==k) return x;
    else return find(rs,k-gg);    
  }
  
  int Ask(int x,int y,int k){
    reverse(x),access(y),splay(y);
    int pos=find(y,k);
    reverse(1);
    return pos;
  }
  
  int Get(int x,int y){
    access(y),y=0;
    for(splay(x);f[x];y=x,x=f[x],splay(x)){
      rs=y,up(x);
    }
    return sum[y]+sum[rs];
  }

}lct;

void add(int x,int y,int z){
  a[++cnt].to=y,a[cnt].w=z,a[cnt].nt=head[x],head[x]=cnt;
  a[++cnt].to=x,a[cnt].w=z,a[cnt].nt=head[y],head[y]=cnt;
}

void dfs(int u,int fa){
  f[u]=fa;sz[u]=1;
  for(int i=head[u];i;i=a[i].nt){
    if(a[i].to==fa) continue;
    v[a[i].to]=sum[a[i].to]=a[i].w;
    dfs(a[i].to,u);
  }
}

void init(){
  cnt=0;
  memset(sum,0,sizeof sum);
  memset(ch,0,sizeof ch);
  memset(head,0,sizeof head);
  memset(v,0,sizeof v);
  memset(sz,0,sizeof sz);
}

char lx[20];

int main(){
  int T;read(T);
  fr(o,1,T){
    init();
    int n;read(n);
    for(int i=1,x,y,z;i<n;++i){
      read(x),read(y),read(z);
      add(x,y,z);
    }
    dfs(1,0);
    for(;;){
      scanf("%s",lx+1);
      if(lx[1]=='K'){
        int x,y,k;read(x),read(y),read(k);
        printf("%d\n",lct.Ask(x,y,k));
      } else if(lx[2]=='I'){
        int x,y;read(x),read(y);
        printf("%d\n",lct.Get(x,y));
      } else break;
    }
  }
  return 0;
}
