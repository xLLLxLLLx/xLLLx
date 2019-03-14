#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=5e4+10,M=3e6+10;
int sz=0;
int rt[M],sum[M],lson[M],rson[M],pre[N],a[N],all[N];

void build(int &nw,int l,int r){
    nw=++sz;
    if(l==r) return ;
    int mid=(l+r)>>1;
    build(lson[nw],l,mid),build(rson[nw],mid+1,r);
}

void change(int old,int &nw,int L,int l,int r,int k){
    nw=++sz;sum[nw]=sum[old],lson[nw]=lson[old],rson[nw]=rson[old];
    if(l==r) { sum[nw]+=k;return ; }
    int mid=(l+r)>>1;
    if(L<=mid) change(lson[nw],lson[nw],L,l,mid,k);
    else change(rson[nw],rson[nw],L,mid+1,r,k);
    sum[nw]=sum[lson[nw]]+sum[rson[nw]];
}

int Get(int qq,int hq,int L,int R,int l,int r){
    if(L<=l&&r<=R) return sum[hq]-sum[qq];
    int mid=(l+r)>>1,ans=0;
    if(L<=mid) ans+=Get(lson[qq],lson[hq],L,R,l,mid);
    if(R>mid) ans+=Get(rson[qq],rson[hq],L,R,mid+1,r);
    return ans;
}

int main(){
    int n;scanf("%d",&n);
    build(rt[0],1,n);
    fr(i,1,n) scanf("%d",&a[i]),all[i]=a[i];
    sort(all+1,all+1+n);
    int tot=unique(all+1,all+1+n)-all-1;
    fr(i,1,n){
        a[i]=lower_bound(all+1,all+1+tot,a[i])-all;
        change(rt[i-1],rt[i],pre[a[i]]+1,1,n,1);
        pre[a[i]]=i;
    }
    int m;scanf("%d",&m);
    fr(i,1,m){
        int x,y;scanf("%d%d",&x,&y);
        printf("%d\n",Get(rt[x-1],rt[y],1,x,1,n));
    }
    return 0;
}
