#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1e5+10,M=4e6+10;
int sz=0,all[N],a[N],ys[N],sum[M],lson[M],rson[M],rt[M];

void build(int &nw,int l,int r){
    nw=++sz,sum[nw]=0,lson[nw]=0,rson[nw]=0;
    if(l==r) return ;
    int mid=(l+r)>>1;
    build(lson[nw],l,mid),build(rson[nw],mid+1,r);
}

void change(int old,int &nw,int L,int l,int r,int k){
    nw=++sz;
    sum[nw]=sum[old]+k,lson[nw]=lson[old],rson[nw]=rson[old];
    if(l==r) return ;
    int mid=(l+r)>>1;
    if(L<=mid) change(lson[nw],lson[nw],L,l,mid,k);
    else change(rson[nw],rson[nw],L,mid+1,r,k);
}

int Ask(int qq,int hq,int l,int r,int k){
    if(l==r) return ys[l];
    int nm=sum[lson[hq]]-sum[lson[qq]],mid=(l+r)>>1;
    if(nm>=k) Ask(lson[qq],lson[hq],l,mid,k);
    else Ask(rson[qq],rson[hq],mid+1,r,k-nm);
}

int main(){
    int T;scanf("%d",&T);
    fr(o,1,T){
        int n,m;scanf("%d%d",&n,&m);
        sz=0;
        fr(i,1,n) scanf("%d",&a[i]),all[i]=a[i];
        sort(all+1,all+1+n);
        int tot=unique(all+1,all+1+n)-all-1;
        fr(i,1,n){
            int x=a[i];
            a[i]=lower_bound(all+1,all+1+tot,a[i])-all;
            ys[a[i]]=x;
        }
        build(rt[0],1,tot);
        fr(i,1,n) change(rt[i-1],rt[i],a[i],1,tot,1);
        fr(i,1,m){
            int l,r,k;scanf("%d%d%d",&l,&r,&k);
            printf("%d\n",Ask(rt[l-1],rt[r],1,tot,k));
        }
    }
    return 0;
}
