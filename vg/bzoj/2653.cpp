#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=2e4+10,M=8e5+10;
struct data{
  int v,id;
}all[N];
int ls[M],rs[M],a[N],rt[N],g[5];
struct node{
  int sum,lmx,rmx;
}tr[M];
int sz=0,n;

bool cmp(data xx,data yy){
  return xx.v<yy.v;
}

node merge(node pos,node tmp){
  node res;
  res.sum=pos.sum+tmp.sum;
  res.lmx=max(pos.sum+tmp.lmx,pos.lmx);
  res.rmx=max(tmp.sum+pos.rmx,tmp.rmx);
  return res;
}

void build(int &x,int l,int r){
  x=++sz;
  if(l==r){ tr[x].sum=tr[x].lmx=tr[x].rmx=1; return ; }
  int mid=(l+r)>>1;
  build(ls[x],l,mid),build(rs[x],mid+1,r);
  tr[x]=merge(tr[ls[x]],tr[rs[x]]);
}

void change(int old,int &nw,int l,int r,int L){
  nw=++sz;
  if(l==r){ tr[nw].lmx=tr[nw].rmx=0,tr[nw].sum=-1; return ; };
  ls[nw]=ls[old],rs[nw]=rs[old];
  tr[nw].lmx=tr[old].lmx,tr[nw].rmx=tr[old].rmx,tr[nw].sum=tr[old].sum;
  int mid=(l+r)>>1;
  if(L<=mid) change(ls[nw],ls[nw],l,mid,L);
  else change(rs[nw],rs[nw],mid+1,r,L);
  tr[nw]=merge(tr[ls[nw]],tr[rs[nw]]);
}

node Get(int x,int l,int r,int L,int R){
  if(l>r) return (node){0,0,0};
  if(L<=l&&r<=R) return tr[x];
  int mid=(l+r)>>1;
  if(R<=mid) return Get(ls[x],l,mid,L,R);
  else if(L>mid) return Get(rs[x],mid+1,r,L,R);
  else {
    node pos=Get(ls[x],l,mid,L,R),tmp=Get(rs[x],mid+1,r,L,R);
    return merge(pos,tmp);
  }
}

bool check(int mid){
  node L=Get(rt[mid],1,n,g[1],g[2]-1);
  node M=Get(rt[mid],1,n,g[2],g[3]);
  node R=Get(rt[mid],1,n,g[3]+1,g[4]);
  return (L.rmx+M.sum+R.lmx)>=0;
}

int main(){
  scanf("%d",&n);
  fr(i,1,n) scanf("%d",&a[i]),all[i].v=a[i],all[i].id=i;
  sort(all,all+n,cmp);
  build(rt[1],1,n);
  fr(i,2,n) change(rt[i-1],rt[i],1,n,all[i-1].id);
  int lt=0,m;scanf("%d",&m);
  fr(o,1,m){
    fr(i,1,4) scanf("%d",&g[i]),g[i]=(g[i]+lt)%n,g[i]++;
    sort(g+1,g+5);
    int l=1,r=n,ans;
    while(l<=r){
      int mid=(l+r)>>1;
      if(check(mid)) ans=mid,l=mid+1;
      else r=mid-1;
    }
    lt=all[ans].v;
    printf("%d\n",lt);
  }
  return 0;
}
