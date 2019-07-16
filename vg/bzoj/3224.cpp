#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long

#define ls ch[x][0]
#define rs ch[x][1]

#define fi first
#define se second

using namespace std;

const int N=1e5+10;
const LL mod=3e9;
typedef pair<int,int> pp;
int root=0,idx=0;
int ch[N][2],sz[N],rd[N];
LL v[N];

void up(int x){
  sz[x]=sz[ls]+sz[rs]+1;
}

int merge(int a,int b){
  if(!a||!b) return a+b;
  if(rd[a]<rd[b]){
    ch[a][1]=merge(ch[a][1],b);
    up(a);
    return a;
  } else {
    ch[b][0]=merge(a,ch[b][0]);
    up(b);
    return b;
  }
}

pp split(int x,int k){
  if(!k) return make_pair(0,x);
  int LS=ls,RS=rs;
  if(sz[ls]==k){
    ls=0;up(x);
    return make_pair(LS,x);
  } else if(sz[ls]+1==k){
    rs=0;up(x);
    return make_pair(x,RS);
  } else if(sz[ls]>k){
    pp gg=split(ls,k);
    ls=gg.se,up(x);
    return make_pair(gg.fi,x);
  } else {
    pp gg=split(rs,k-sz[ls]-1);
    rs=gg.fi,up(x);
    return make_pair(x,gg.se);
  }
}

LL qq(int x,LL val){
  LL ans=-2e9;
  while(x){
    if(v[x]<val) ans=max(ans,v[x]),x=rs;
    else x=ls;
  }
  return ans;
}

LL hj(int x,LL val){
  LL ans=2e9;
  while(x){
    if(v[x]>val) ans=min(ans,v[x]),x=ls;
    else x=rs;
  }
  return ans;
}

LL find(int x,int k){
  int gg=sz[ls]+1;
  if(gg<k) return find(rs,k-gg);
  else if(gg==k) return v[x];
  else return find(ls,k);
}

int kth(int x,LL k){
  int ans=1e9,tmp=0;
  while(x){
    if(v[x]==k) ans=min(ans,tmp+sz[ls]+1),x=ls;
    else if(v[x]<k) tmp+=sz[ls]+1,x=rs;
    else x=ls;
  }
  return ans==1e9?tmp:ans;
}

void print(int x){
  if(!x) return ;
  print(ls);
  printf("nw%lld\n",v[x]);
  print(rs);
}

void insert(LL x){
  int gg=kth(root,x);
  pp pos=split(root,gg);
  ++idx;
  v[idx]=x,sz[idx]=1,rd[idx]=rand();
  root=merge(pos.fi,idx);
  root=merge(root,pos.se);
}

void delet(int x){
  int gg=kth(root,x);
  pp pos=split(root,gg);
  pp tmp=split(pos.fi,gg-1);
  root=merge(tmp.fi,pos.se);
}

int main(){
  int n;scanf("%d",&n);
  fr(i,1,n){
    int tp; LL x;scanf("%d%lld",&tp,&x);
    if(tp==1) insert(x);
    if(tp==2) delet(x);
    if(tp==3) printf("%d\n",kth(root,x));
    if(tp==4) printf("%lld\n",find(root,x));
    if(tp==5) printf("%lld\n",qq(root,x));
    if(tp==6) printf("%lld\n",hj(root,x));
  }
  return 0;
}