#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int M=5e6+10,N=5e4+10;
int sz=0;
int rt[M],sum[M],lson[M],rson[M],ys[N],all[N],a[N];

void build(int &nw,int l,int r){
    nw=++sz;
    if(l==r) return ;
    int mid=(l+r)>>1;
    build(lson[nw],l,mid),build(rson[nw],mid+1,r);
}

void Change(int old,int &nw,int L,int l,int r,int k){
    nw=++sz;
    sum[nw]=sum[old]+k,lson[nw]=lson[old],rson[nw]=rson[old];
    if(l==r) return ;
    int mid=(l+r)>>1;
    if(L<=mid) Change(lson[nw],lson[nw],L,l,mid,k);
    else Change(rson[nw],rson[nw],L,mid+1,r,k);
}

int Ask(int qq,int hq,int l,int r,int k){
   // printf("%d %d %d %d %d\n",qq,hq,l,r,k);
    if(l==r) return ys[l];
    int nm=sum[rson[hq]]-sum[rson[qq]],mid=(l+r)>>1;
    if(nm>=k) return Ask(rson[qq],rson[hq],mid+1,r,k);
    else return Ask(lson[qq],lson[hq],l,mid,k-nm);
}

int main(){
    int n;scanf("%d",&n);
    fr(i,1,n) scanf("%d",&a[i]),all[i]=a[i];
    sort(all+1,all+1+n);
    int tot=unique(all+1,all+1+n)-all-1;
    fr(i,1,n) {
        int x=a[i];
        a[i]=lower_bound(all+1,all+1+tot,a[i])-all;
        ys[a[i]]=x;
    }
    int m;scanf("%d",&m);
    build(rt[0],1,tot);
    fr(i,1,n) Change(rt[i-1],rt[i],a[i],1,tot,1);
    fr(i,1,m){
        int l,r,k;scanf("%d%d%d",&l,&r,&k);
        printf("%d\n",Ask(rt[l],rt[r+1],1,tot,k));
    }
    return 0;
}
