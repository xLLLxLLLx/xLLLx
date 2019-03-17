#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long 
using namespace std;

const int N=6e4+10,Q=1e4+10,M=2.5e6+10;
struct Qu{ int id,l,r,k; }q[Q];
int all[N],a[N-Q+1];
int sz=0,n,m,tot;
int rt[N],tr[N],us[N],lson[M],rson[M],sum[M];

int lowerbit(int x){
  return x&(-x);
}

void build(int &nw,int l,int r){
  nw=++sz;sum[nw]=0;
  if (l==r) return ;
  int mid=(l+r)>>1;
  build(lson[nw],l,mid),build(rson[nw],mid+1,r);
}

void insert(int old,int &nw,int L,int l,int r,int k){
  nw=++sz;
  lson[nw]=lson[old],rson[nw]=rson[old],sum[nw]=sum[old]+k;
  if (l==r) return ;
  int mid=(l+r)>>1;
  if (L<=mid) insert(lson[nw],lson[nw],L,l,mid,k);
  else insert(rson[nw],rson[nw],L,mid+1,r,k);
}

void Gai(int x,int pos,int d){
  for(;x<=n;x+=lowerbit(x)){
    insert(tr[x],tr[x],pos,1,tot,d);
  }
}

int Go(int x){
  int ans=0;
  for(;x;x-=lowerbit(x)) ans+=sum[lson[us[x]]];
  return ans;
}

int Get(int l,int r,int k){
  int qq=rt[l],hq=rt[r],L=1,R=tot;
  for(int i=l;i;i-=lowerbit(i)) us[i]=tr[i];//,printf("ss%d\n",us[i]);
  for(int i=r;i;i-=lowerbit(i)) us[i]=tr[i];//,printf("ss%d\n",us[i]);
  while(L<R){
    int mid=(L+R)>>1;
    int nm=Go(r)-Go(l)+sum[lson[hq]]-sum[lson[qq]];
    //printf("L=%d R=%d Go=%d nm=%d\n",L,R,Go(r)-Go(l),nm);
    if (nm>=k){
      R=mid;
      qq=lson[qq],hq=lson[hq];
      for(int i=l;i;i-=lowerbit(i)) us[i]=lson[us[i]];
      for(int i=r;i;i-=lowerbit(i)) us[i]=lson[us[i]];
    } else {
      L=mid+1;k-=nm;
      qq=rson[qq],hq=rson[hq];
      for(int i=l;i;i-=lowerbit(i)) us[i]=rson[us[i]];
      for(int i=r;i;i-=lowerbit(i)) us[i]=rson[us[i]];
    }
  }
  return all[L];
}

int main(){
  int T;scanf("%d",&T);
  fr(o,1,T){
    sz=0;rt[0]=0;
    scanf("%d%d",&n,&m);
    fr(i,1,n) scanf("%d",&a[i]),all[i]=a[i];
    int cnt=n;
    fr(i,1,m){
      char ch;cin>>ch;
      if (ch=='Q') q[i].id=1,scanf("%d%d%d",&q[i].l,&q[i].r,&q[i].k);
      else {
        scanf("%d%d",&q[i].l,&q[i].r);
        all[++cnt]=q[i].r;q[i].id=0;
      }
    }
    sort(all+1,all+1+cnt);
    tot=unique(all+1,all+1+cnt)-all-1;
    build(rt[0],1,tot);
    fr(i,1,n) a[i]=lower_bound(all+1,all+1+tot,a[i])-all,insert(rt[i-1],rt[i],a[i],1,tot,1);
    fr(i,1,n) tr[i]=rt[0];
    fr(i,1,m){
      if (q[i].id) printf("%d\n",Get(q[i].l-1,q[i].r,q[i].k));
      else {
        q[i].r=lower_bound(all+1,all+1+tot,q[i].r)-all;
        Gai(q[i].l,a[q[i].l],-1),Gai(q[i].l,q[i].r,1);
        a[q[i].l]=q[i].r;
      }
    }
  }
  return 0;
}
