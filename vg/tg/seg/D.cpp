#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i<=y;++i)
#define LL long long
using namespace std;
const int N=1e5+10,M=4e6+10;
int sz=0;
int qx[N];
vector<int>gg[N];
int rt[M],sum[M],lson[M],rson[M];

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

int Get(int qq,int hq,int L,int R,int l,int r){
    if(L<=l&&r<=R) return sum[hq]-sum[qq];
    int mid=(l+r)>>1,ans=0;
    if(L<=mid) ans+=Get(lson[qq],lson[hq],L,R,l,mid);
    if(R>mid) ans+=Get(rson[qq],rson[hq],L,R,mid+1,r);
    return ans;
}

int main(){
    int n,k;scanf("%d%d",&n,&k);
    build(rt[0],1,n);
    fr(i,1,n) {
        int x;scanf("%d",&x);
        if(qx[x]>=k) Change(rt[i-1],rt[i],gg[x][qx[x]-k],1,n,1);
        else rt[i]=rt[i-1];
        qx[x]++;gg[x].push_back(i);
    }
    int m;scanf("%d",&m);
    int pos=0;
    fr(i,1,m){
        int l,r;scanf("%d%d",&l,&r);
        l=(l+pos)%n+1,r=(r+pos)%n+1;
        if(l>r) swap(l,r);
        //cout<<"l=="<<l<<" r="<<r<<endl;
        pos=r-l+1-Get(rt[l-1],rt[r],l,r,1,n);
        printf("%d\n",pos);
    }
    return 0;
}
