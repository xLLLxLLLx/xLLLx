#include <bits/stdc++.h>
#define FR first
#define SE second
 
using namespace std;
 
typedef pair<int,int> pr;
 
namespace LCT {
 
int ch[100005][2],fa[100005];
int size[100005];
 
inline bool isroot(int o) {
  return (ch[fa[o]][0]!=o)&&(ch[fa[o]][1]!=o);
}
 
inline void pushup(int o) {
  size[o]=size[ch[o][0]]+size[ch[o][1]]+1;
}
 
void rotate(int x) {
  int y=fa[x],z=fa[y],d=(ch[y][1]==x);
  if (!isroot(y)) {
    if (ch[z][0]==y) ch[z][0]=x; else ch[z][1]=x;
  }
  fa[x]=z;fa[y]=x;fa[ch[x][d^1]]=y;
  ch[y][d]=ch[x][d^1];ch[x][d^1]=y;
  pushup(y);
}
 
void splay(int x) {
  while (!isroot(x)) {
    int y=fa[x],z=fa[y];
    if (!isroot(y)) {
      if ((ch[y][0]==x)^(ch[z][0]==y)) rotate(x); else rotate(y);
    }
  rotate(x);
  }
  pushup(x);
}
 
void access(int x) {
  int y=0;
  while (x) {
    splay(x);
    ch[x][1]=y;pushup(x);
    y=x;x=fa[x];
  }
}
 
void link(int x,int y) {
  access(x);
  splay(x);
  fa[x]=y;
}
 
void cut(int x) {
  access(x);
  splay(x);
  fa[ch[x][0]]=0;ch[x][0]=0;
  pushup(x);
}
 
int findroot(int x) {
  access(x);
  splay(x);
  while (ch[x][0]) x=ch[x][0];
  splay(x);
  return x;
}
 
pr query(int x) {
  x=findroot(x);
  return pr(x,size[x]);
}
 
}
 
int num[100005],r[100005];
int cmin[100005],cmax[100005];
 
namespace ST {
 
int minn[17][100005],maxn[17][100005];
 
void pre(int n) {
  for(int i=1;i<=n;i++) minn[0][i]=maxn[0][i]=cmin[i]=cmax[i]=num[i];
  for(int i=1;i<17;i++)
    for(int j=1;j<=n-(1<<i)+1;j++) {
      minn[i][j]=min(minn[i-1][j],minn[i-1][j+(1<<(i-1))]);
      maxn[i][j]=max(maxn[i-1][j],maxn[i-1][j+(1<<(i-1))]);
  }
}
 
int jump(int x,int d,int n) {
  for(int j=16;j>=0;j--)
    if (r[x]+(1<<j)<=n&&max(cmax[x],maxn[j][r[x]+1])-min(cmin[x],minn[j][r[x]+1])<=d) {
      cmin[x]=min(cmin[x],minn[j][r[x]+1]);
      cmax[x]=max(cmax[x],maxn[j][r[x]+1]);
      r[x]+=(1<<j);
  }
  return r[x];
}
 
}
 
const int SIZE=50;
 
pr a[5500005];
int cnt,rx=1;
 
void update(int d,int n) {
  while (rx<=cnt&&a[rx].FR<=d) {
    int x=a[rx++].SE;
    r[x]++;
    cmin[x]=min(cmin[x],num[r[x]]);
    cmax[x]=max(cmax[x],num[r[x]]);
    LCT::cut(x);
    if (r[x]<=n&&r[x]-x<=SIZE) LCT::link(x,r[x]+1);
  }
}
 
int query(int d,int n) {
  int x=1,ans=0;
  while (x<=n)
    if (LCT::fa[x]) {
      pr t=LCT::query(x);
      ans+=t.SE-1;
      x=t.FR;
  }
  else {
    x=ST::jump(x,d,n)+1;
    ans++;
  }
  return ans-1;
}
 
pr q[100005];
int ans[100005];
 
int main() {
  int n,m,k;
  scanf("%d%d%d",&n,&m,&k);
  for(int i=1;i<=n;i++) scanf("%d",&num[i]);
  for(int i=1;i<=n;i++) {
    r[i]=i;
    LCT::size[i]=1;
    LCT::link(i,i+1);
  }
  ST::pre(n);
  for(int i=1;i<=n;i++) {
    int minn=num[i],maxn=num[i];
    for(int j=1;j<=SIZE+1&&i+j<=n;j++) {
      minn=min(minn,num[i+j]);
      maxn=max(maxn,num[i+j]);
      a[++cnt]=pr(maxn-minn,i);
    }
  }
  sort(a+1,a+cnt+1);
  for(int i=1;i<=k;i++) {
    int x;
    scanf("%d",&x);
    q[i]=pr(m-x,i);
  }
  sort(q+1,q+k+1);
  for(int i=1;i<=k;i++) {
    update(q[i].FR,n);
    ans[q[i].SE]=query(q[i].FR,n);
  }
  for(int i=1;i<=k;i++) printf("%d\n",ans[i]);
  return 0;
}