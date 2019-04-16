#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int M=4e6+10;
int ch[M][2],a[M],rt[M],ls[M],rs[M],t[M];
int idx=0,sz=0,root=0;
LL ans=0,ans1=0,ans2=0;

void up(int x){
  t[x]=t[ls[x]]+t[rs[x]];
}

void read(int &x){
  x=++idx;
  scanf("%d",&a[x]);
  if(a[x]) return ;
  read(ch[x][0]),read(ch[x][1]);
}

void build(int &x,int l,int r,int L){
  x=++sz;
  if(l==r){ t[x]=1; return ; }
  int mid=(l+r)>>1;
  if(L<=mid) build(ls[x],l,mid,L);
  else build(rs[x],mid+1,r,L);
  up(x);
}

int merge(int x,int y){
  if(!x) return y;
  if(!y) return x;
  ans1+=1LL*t[rs[x]]*t[ls[y]];
  ans2+=1LL*t[ls[x]]*t[rs[y]];
  ls[x]=merge(ls[x],ls[y]);
  rs[x]=merge(rs[x],rs[y]);
  up(x);
  return x;
}

void solve(int x){
  if(!x) return ;
  solve(ch[x][0]),solve(ch[x][1]);
  if(!a[x]){
    ans1=ans2=0;
    rt[x]=merge(rt[ch[x][0]],rt[ch[x][1]]);
    ans+=min(ans1,ans2);
  }
}

int main(){
  int n;scanf("%d",&n);
  read(root);
  fr(i,1,idx)
    if(a[i]) build(rt[i],1,n,a[i]);
  solve(1);
  printf("%lld\n",ans);
  return 0;
}