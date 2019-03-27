#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
using namespace std;
const int N=1e5+10;
const int inf=233333;
struct data{
  int nt,to;
}a[N<<1];
int cnt=0;
int S[N];
int head[N],d[N],nm[N],col[N],ch[N][2],f[N];

void read(int &x){
  char ch=getchar();x=0;
  for(;ch<'0'||ch>'9';ch=getchar()) ;
  for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
}

#define ls ch[x][0]
#define rs ch[x][1]

struct LCT{
  
  int fi(int x){
    return nm[x].size();
  }

  void up(int x){
    if(rs) rmx[x]=rmx[rs];
    else rmx[x]=col[x];
    if(ls) lmx[x]=lmx[ls];
    else lmx[x]=col[x];
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
      if(i&&col[i]) nm[x]++;
      if(rs&&col[i]) nm[x]--; 
      rs=i,up(x);
    }
  }

  void change(int x){
    access(x),splay(x);
    col[x]^=1;
  }

  int Get(int x){
    access(x),splay(x);
    if(col[x]) return nm[x];
    else return d[x]-nm[x];
  }

}lct;


void dfs(int u,int fa){
  f[u]=fa;
  for(int i=head[u];i;i=a[i].nt){
    if(a[i].to==fa) continue;
    dfs(a[i].to,u);
  }
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
    d[x]++,d[y]++;
  }
  dfs(1,0);
  int m;read(m);
  fr(o,1,m){
    int x,y;
    read(x),read(y);
    if(!x) printf("%d\n",lct.Get(y));
    else lct.change(y);
  } 
  return 0;
}
