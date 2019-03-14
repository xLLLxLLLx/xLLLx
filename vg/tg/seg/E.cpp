#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1e5+10,M=4e6+10,TOT=1e5+2;
int sz=0;
int vis[N],maxn[M],rt[M],lson[M],rson[M];

void build(int &nw,int l,int r){
    nw=++sz;
    if(l==r) return ;
    int mid=(l+r)>>1;
    build(lson[nw],l,mid),build(rson[nw],mid+1,r);
}

void Change(int old,int &nw,int L,int l,int r,int k){
    nw=++sz;
    maxn[nw]=max(k,maxn[old]),lson[nw]=lson[old],rson[nw]=rson[old];
    if(l==r) return ;
    int mid=(l+r)>>1;
    if(L<=mid) Change(lson[old],lson[nw],L,l,mid,k);
    else Change(rson[old],rson[nw],L,mid+1,r,k);
}

int Ask(int old,int l,int r,int L,int R){
    if(L>R) return 0;
    if(L<=l&&r<=R) return maxn[old];
    int mid=(l+r)>>1,pos=0;
    if(L<=mid) pos=max(pos,Ask(lson[old],l,mid,L,R));
    if(R>mid) pos=max(pos,Ask(rson[old],mid+1,r,L,R));
    return pos;
}

int main(){
    int n,m;scanf("%d%d",&n,&m);
    int x,y,w,ans=0;
    fr(i,1,m){
        scanf("%d%d%d",&x,&y,&w);
        w+=2;
        int gg=Ask(rt[x],1,TOT,1,w-1);
        ans=max(ans,gg+1);
        Change(rt[y],rt[y],w,1,TOT,gg+1);
    }
    printf("%d\n",ans);
    return 0;
}
