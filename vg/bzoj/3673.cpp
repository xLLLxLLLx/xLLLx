#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=2e4+10,M=2e6+10;
int rt[N],lson[M],rson[M],f[M],deep[M];
int n,m,sz=0;

void read(int &x){
  char ch=getchar();x=0;
  for(;ch<'0'||ch>'9';ch=getchar()) ;
  for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
}

void build(int &x,int l,int r){
  x=++sz;
  if(l==r) {
    f[x]=l;
    return ;
  } 
  int mid=(l+r)>>1;
  build(lson[x],l,mid),build(rson[x],mid+1,r);
}

void change(int old,int &nw,int l,int r,int L,int k){
  nw=++sz;
  lson[nw]=lson[old],rson[nw]=rson[old];
  if(l==r) { 
    f[nw]=k,deep[nw]=deep[old]; return ; 
  }
  int mid=(l+r)>>1;
  if(L<=mid) change(lson[nw],lson[nw],l,mid,L,k);
  else change(rson[nw],rson[nw],mid+1,r,L,k);
}

int Ask(int x,int l,int r,int L){
  if(l==r) return x;
  int mid=(l+r)>>1;
  if(L<=mid) return Ask(lson[x],l,mid,L);
  else return Ask(rson[x],mid+1,r,L);
}

int find(int root,int x){
  int gg=Ask(root,1,n,x);
  if(f[gg]==x) return gg;
  else return find(root,f[gg]);
}

void add(int old,int &nw,int l,int r,int L){
  nw=++sz;
  lson[nw]=lson[old],rson[nw]=rson[old];
  if(l==r){
    f[nw]=f[old];
    deep[nw]=deep[old]+1;
    return ;
  }
  int mid=(l+r)>>1;
  if(L<=mid) add(lson[nw],lson[nw],l,mid,L);
  else add(rson[nw],rson[nw],mid+1,r,L);
}

int main(){
  read(n),read(m);
  build(rt[0],1,n);
  fr(o,1,m){
    int tp;read(tp);
    int ggg=Ask(rt[o-1],1,n,422);
    if(tp==1){
      rt[o]=rt[o-1];
      int A,B;read(A),read(B);
      int a=find(rt[o],A),b=find(rt[o],B);
      if(f[a]==f[b]) continue;
      if(deep[a]>deep[b]) swap(a,b);
      change(rt[o-1],rt[o],1,n,f[a],f[b]);
      if(deep[a]==deep[b]) add(rt[o],rt[o],1,n,f[b]);
    } else if(tp==2) {
      int x;read(x);
      rt[o]=rt[x];
    } else {
      rt[o]=rt[o-1];
      int x,y;read(x),read(y);
      x=find(rt[o],x);
      y=find(rt[o],y);
      if(f[x]==f[y]) printf("1\n");
      else printf("0\n");
    }
  }
  return 0;
}
