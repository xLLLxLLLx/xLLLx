#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define lson (x<<1)
#define rson (x<<1|1)
#define LL long long
#define db double
using namespace std;
const int N=5e5+10;
const LL inf=123456789123456789;
const db st=0.75;
int pos[N],v[N<<2];
LL val[N];
int flg=0;

struct node{
  int l,r;
};

bool operator < (node x,node y){
  return val[x.l]==val[y.l] ? val[x.r]<val[y.r] : val[x.l]<val[y.l];
}

bool operator == (node x,node y){
  return (val[x.l]==val[y.l])&&(val[x.r]==val[y.r]);
}

struct data{
  int q[N],top,ls[N],rs[N],sz[N],rt,idx;
  node nd[N];
  
  void del(int x){
    if(!x) return ;
    del(ls[x]);   
    q[++top]=x;
    del(rs[x]);
  }
  
  void build(int &x,LL l,LL r,int L,int R){
    int mid=(L+R)>>1;
    LL mm=(l+r)>>1;
    x=q[mid],val[x]=mm,sz[x]=1;
    if(L<mid) build(ls[x],l,mm,L,mid-1);
    else ls[x]=0;
    if(R>mid) build(rs[x],mm,r,mid+1,R);
    else rs[x]=0;
    sz[x]=sz[ls[x]]+sz[rs[x]];
  }
  
  void rebuild(int x,LL l,LL r){
    top=0,del(x);
    build(x,l,r,1,top);
  }
  
  int insert(int &k,LL l,LL r,node x){
    if(!k){
      k=++idx;
      LL mid=(l+r)>>1;
      nd[k]=x,sz[k]=1,val[k]=mid;
      return k;
    }
    else if(nd[k]==x) return k;
    else {
      LL mm=(l+r)>>1;
      int t=(nd[k]<x)?insert(ls[k],l,mm,x):insert(rs[k],mm,r,x);
      if(sz[k]*1.0*st>max(sz[ls[k]],sz[rs[k]])){
        if(flg){
          if(nd[k]<x) rebuild(ls[k],l,mm);
          else rebuild(rs[k],mm,r);
          flg=0;
        }
      } else flg=1;
    }
  }
  
}tz;

void build(int x,int l,int r){
  if(l==r) {val[x]=l;return ;}
  int mid=(l+r)>>1;
  build(lson,l,mid),build(rson,mid+1,r);
}

void modify(int x,int l,int r,int L){
  if(l==r) {
    v[x]=L;
    return ;
  }
  int mid=(l+r)>>1;
  if(L<=mid) modify(lson,l,mid,L);
  else modify(rson,mid+1,r,L);
  if(val[pos[v[lson]]]>val[pos[v[rson]]]) v[x]=v[lson];
  else v[x]=v[rson];
}

int Ask(int x,int l,int r,int L,int R){
  if(L<=l&&r<=R) return v[x];
  int mid=(l+r)>>1;
  if(R<=mid) return Ask(lson,l,mid,L,R);
  else if(L>mid) return Ask(rson,mid+1,r,L,R);
  else {
    int t1=Ask(lson,l,mid,L,R),t2=Ask(rson,mid+1,r,L,R);
    if(val[pos[t1]]<val[pos[t2]]) return t2;
    else return t1;
  }
}

int main(){
  int n,m;scanf("%d%d",&n,&m);
  fr(i,1,n) pos[i]=1;
  build(1,1,n);
  fr(o,1,m){
    char ch;cin>>ch;
    int x,y,z;
    if(ch=='C'){
      scanf("%d%d%d",&x,&y,&z);
      pos[z]=tz.insert(tz.rt,-inf,inf,(node){pos[x],pos[y]});
      if(flg) tz.rebuild(tz.rt,-inf,inf);
      flg=0;
      modify(1,1,n,z);
    } else {
      scanf("%d%d",&x,&y);
      printf("%d\n",Ask(1,1,n,pos[x],pos[y]));
    }
  }
}
