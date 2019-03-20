#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
#define lson x<<1
#define rson x<<1|1
using namespace std;
const int N=1e5+10;

struct qj{
  int l,r;
  void init(int wz){ l=r=wz; }
};

vector<qj>qx;

int n;

struct data{
  int lmx,rmx,mx,sum;
  
  qj lp,rp,mp;
  
  void init(int wz,int v){
    lmx=rmx=mx=sum=v;
    lp.init(wz),rp.init(wz),mp.init(wz);
  }
};

struct node{
  data mx,mn;
  int tag;
  void rev() { swap(mn,mx); }
}tr[N<<2];

void read(int &x){
  char ch=getchar();x=0;int f=0;
  for(;ch<'0'||ch>'9';ch=getchar()) f|=(ch=='-');
  for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
  if(f) x=-x;
}

data merge(data a,data b){/*woc gang!!*/
  data nw;nw.init(0,0);
  nw.sum=a.sum+b.sum;
  if(a.mx>nw.mx) nw.mx=a.mx,nw.mp=a.mp;
  if(b.mx>nw.mx) nw.mx=b.mx,nw.mp=b.mp;
  if(a.rmx+b.lmx>nw.mx) nw.mx=a.rmx+b.lmx,nw.mp.l=a.rp.l,nw.mp.r=b.lp.r;
  if(a.lmx>nw.lmx) nw.lmx=a.lmx,nw.lp=a.lp;
  if(a.sum+b.lmx>nw.lmx) nw.lmx=a.sum+b.lmx,nw.lp.l=a.lp.l,nw.lp.r=b.lp.r;
  if(b.rmx>nw.rmx) nw.rmx=b.rmx,nw.rp=b.rp;
  if(a.rmx+b.sum>nw.rmx) nw.rmx=a.rmx+b.sum,nw.rp.l=a.rp.l,nw.rp.r=b.rp.r;
  return nw;
}

void up(int x){
  tr[x].mx=merge(tr[lson].mx,tr[rson].mx);
  tr[x].mn=merge(tr[lson].mn,tr[rson].mn);
}

void down(int x){
  //printf("x=%d\n",x);
  if(!tr[x].tag) return ;
  tr[lson].rev(),tr[rson].rev();
  tr[lson].tag^=1,tr[rson].tag^=1;
  tr[x].tag=0;
}

void build(int x,int l,int r){
  if(l==r){
    int v;read(v);
    tr[x].mx.init(l,v);
    tr[x].mn.init(l,-v);
    return ;
  }
  int mid=(l+r)>>1;
  build(lson,l,mid),build(rson,mid+1,r);
  up(x);
  /*puts("");
  printf("x=%d l=%d r=%d ::\n",x,l,r);
  printf("lmx=%d l=%d r=%d\n",tr[x].mx.lmx,tr[x].mx.lp.l,tr[x].mx.lp.r);
  printf("rmx=%d l=%d r=%d\n",tr[x].mx.rmx,tr[x].mx.rp.l,tr[x].mx.rp.r);
  printf("mmx=%d l=%d r=%d\n",tr[x].mx.mx,tr[x].mx.mp.l,tr[x].mx.mp.r);
  puts("");*/
}

void change(int x,int l,int r,int L,int k){
  if(l==r){
   tr[x].mx.init(l,k);
   tr[x].mn.init(l,-k);
   return ; 
  }
  int mid=(l+r)>>1;
  down(x);
  if(L<=mid) change(lson,l,mid,L,k);
  else change(rson,mid+1,r,L,k);
  up(x);
}

void modify(int x,int l,int r,int L,int R){
  if(L<=l&&r<=R){
    tr[x].rev();
    tr[x].tag^=1;
    return ;
  }
  int mid=(l+r)>>1;
  down(x);
  if(L<=mid) modify(lson,l,mid,L,R);
  if(R>mid) modify(rson,mid+1,r,L,R);
  up(x);
}

data Ask(int x,int l,int r,int L,int R){
  if(L<=l&&r<=R) return tr[x].mx;
  int mid=(l+r)>>1;
  down(x);
  if(R<=mid) return Ask(lson,l,mid,L,R);
  else if(L>mid) return Ask(rson,mid+1,r,L,R);
  else {
    data pos=Ask(lson,l,mid,L,R),tmp=Ask(rson,mid+1,r,L,R);
    return merge(pos,tmp);
  }
}

int get(int L,int R,int k){
  int ans=0;
  fr(o,1,k){
    data zz=Ask(1,1,n,L,R);
    if(zz.mx>0){
      ans+=zz.mx;
      modify(1,1,n,zz.mp.l,zz.mp.r);
      qx.push_back((qj){zz.mp.l,zz.mp.r});
    }
  }
  int len=qx.size();
  fr(i,0,len-1) modify(1,1,n,qx[i].l,qx[i].r);
  qx.clear();
  return ans;
}

int main(){
  read(n);
  build(1,1,n);
  int m;read(m);
  fr(o,1,m){
    int tp,x,y,z;
    read(tp);
    if(tp==1){
      read(x),read(y),read(z);      
      printf("%d\n",get(x,y,z));
    } else {
      read(x),read(y);
      change(1,1,n,x,y);
    }
  }
  return 0;
}
