#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1e5+10,M=4e6+10;
struct node{
  int d,p,l;
}a[N];
struct data{
  LL w,v;
}gg[M];
int cnt=1e5,sz=0;
int all[N],rt[N],lson[M],rson[M];

bool cmp(node A,node B){
  return A.d>B.d;
}

void build(int &x,int l,int r){
  x=++sz;
  if(l==r) return ;
  int mid=(l+r)>>1;
  build(lson[x],l,mid),build(rson[x],mid+1,r);
}

data up(data x,data y){
  data res;
  res.w=x.w+y.w,res.v=x.v+y.v;
  return res;
}

void change(int old,int &nw,int l,int r,data zz){
  nw=++sz;
  lson[nw]=lson[old],rson[nw]=rson[old],gg[nw]=gg[old];
  if(l==r){
    gg[nw].w+=zz.w*zz.v,gg[nw].v+=zz.v;
    return ;
  }
  int mid=(l+r)>>1;
  if(zz.w<=mid) change(lson[nw],lson[nw],l,mid,zz);
  else change(rson[nw],rson[nw],mid+1,r,zz);
  gg[nw]=up(gg[lson[nw]],gg[rson[nw]]);
}

LL Ask(int x,int l,int r,LL w){
  if(l==r) return min(gg[x].v,w/l);
  int mid=(l+r)>>1;
  LL pos=gg[lson[x]].w;
  if(pos==w) return gg[lson[x]].v;
  else if(pos>w) return Ask(lson[x],l,mid,w);
  else return gg[lson[x]].v+Ask(rson[x],mid+1,r,w-pos);
}

int main(){
  int n,m;scanf("%d%d",&n,&m);
  fr(i,1,n) scanf("%d%d%d",&a[i].d,&a[i].p,&a[i].l);
  sort(a+1,a+1+n,cmp);a[0].d=-1;
  build(rt[0],1,cnt);
  fr(i,1,n) change(rt[i-1],rt[i],1,cnt,(data){a[i].p,a[i].l});
  fr(o,1,m){
    LL g,L;scanf("%lld%lld",&g,&L);
    int l=1,r=n,ans=0;
    while(l<=r){
      int mid=(l+r)>>1;
      if(Ask(rt[mid],1,cnt,g)>=L) ans=mid,r=mid-1;
      else l=mid+1;
    }
    printf("%d\n",a[ans].d);
  }
  return 0;
}
