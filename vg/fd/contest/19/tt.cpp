#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int N=2e4+10;
struct data{
    LL l,r,h;
    int flag;
}qx[N];
LL sum[N<<2],col[N<<2],lq[N<<2],rq[N<<2],jp[N<<2];

bool comp(data xx,data yy){
    if(xx.h==yy.h) return xx.flag>yy.flag;
    return xx.h<yy.h;
}

void pushup(int l,int r,int index){
    if(col[index]){
        lq[index]=rq[index]=1;
        sum[index]=r-l+1;
        jp[index]=2;
    }
    else if(l==r) lq[index]=rq[index]=jp[index]=sum[index]=0;
    else {
        lq[index]=lq[index*2];
        rq[index]=rq[index*2+1];
        sum[index]=sum[index*2]+sum[index*2+1];
        //col[index]=col[index*2]+col[index*2+1];
        jp[index]=jp[index*2]+jp[index*2+1];
        if(lq[index*2+1]&&rq[index*2]) jp[index]-=2;
    }
}

void change(int L,int R,int flag,int l,int r,int index){
    if(L<=l&&r<=R){
        col[index]+=flag;
        pushup(l,r,index);
        return ;
    }
    int mid=(l+r)>>1;
    if(L<=mid) change(L,R,flag,l,mid,index*2);
    if(R>mid) change(L,R,flag,mid+1,r,index*2+1);
    pushup(l,r,index);
}

int main(){
    int n;scanf("%d",&n);
    LL x1,y1,x2,y2;
    LL maxn=-1e4,minn=1e4;
    for(int i=1;i<=n;++i){
        scanf("%lld%lld%lld%lld",&x1,&y1,&x2,&y2);
        qx[i*2-1].l=qx[i*2].l=x1;
        qx[i*2-1].r=qx[i*2].r=x2;
        qx[i*2-1].flag=1;qx[i*2].flag=-1;
        qx[i*2-1].h=y1;qx[i*2].h=y2;
        minn=min(minn,x1);
        maxn=max(maxn,x2);
    }
    sort(qx+1,qx+1+n*2,comp);
    LL last=0,ans=0;
    for(int i=1;i<=n*2;++i){
        if(qx[i].l<qx[i].r) change(qx[i].l,qx[i].r-1,qx[i].flag,minn,maxn-1,1);
        ans+=jp[1]*(qx[i+1].h-qx[i].h);
        ans+=abs(sum[1]-last);
        last=sum[1];
        //printf("%lld\n",ans);
    }
    printf("%lld\n",ans);
    return 0;
}
