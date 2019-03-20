#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long 
using namespace std;
const int N=1e6+10,M=4e7+10;
int sz=0;
int a[N];
int rt[M],ls[M],rs[M],v[M];

void build(int &x,int l,int r){
  x=++sz;
  if(l==r) {
    scanf("%d",&a[l]);
    v[x]=a[l];
    return ;
  }
  int mid=(l+r)>>1;
  build(ls[x],l,mid),build(rs[x],mid+1,r);
}

void change(int old,int &nw,int l,int r,int L,int k){
  nw=++sz;
  ls[nw]=ls[old],rs[nw]=rs[old];
  if(l==r) { v[nw]=k; return ; }
  int mid=(l+r)>>1;
  if(L<=mid) change(ls[nw],ls[nw],l,mid,L,k);
  else change(rs[nw],rs[nw],mid+1,r,L,k);
}

int find(int x,int l,int r,int L){
  if(l==r) return v[x];
  int mid=(l+r)>>1;
  if(L<=mid) return find(ls[x],l,mid,L);
  else return find(rs[x],mid+1,r,L);
}

int main(){
  int n,m;scanf("%d%d",&n,&m);
  build(rt[0],1,n);
  fr(i,1,m){
    int mk,tp;scanf("%d%d",&mk,&tp);
    if(tp==1){
      int x,y;scanf("%d%d",&x,&y);
      rt[i]=rt[mk];
      change(rt[mk],rt[i],1,n,x,y);
    } else {
      rt[i]=rt[mk];
      int sit;scanf("%d",&sit);
      printf("%d\n",find(rt[i],1,n,sit));
    }
  }
  return 0;
}
