#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1e5+10;
int ans=0;
int b[N],dp[N],mx[N],mn[N],a[N],tr[N];

int lowerbit(int x){ return x&(-x); }

void Upd(int x,int y){
    for(;x<N;x+=lowerbit(x)) tr[x]=max(tr[x],y);
}

void Qk(int x){
    for(;x<N;x+=lowerbit(x)) tr[x]=0;
}

int Get(int x){
    int pos=0;
    for(;x;x-=lowerbit(x)) pos=max(pos,tr[x]);
    return pos;
}

bool cmp1(int x,int y){
    return a[x]<a[y];
}

bool cmp2(int x,int y){
    return mn[x]<mn[y];
}

bool cmp3(int x,int y){
    return x<y;
}

void cdq(int l,int r){
    if(l==r) return ;
    int mid=(l+r)>>1;
    cdq(l,mid);
    sort(b+l,b+mid+1,cmp1);
    sort(b+mid+1,b+r+1,cmp2);
    int pos=l-1;
    fr(i,mid+1,r){
        while(pos+1<=mid&&a[b[pos+1]]<=mn[b[i]]){
            pos++;
            Upd(mx[b[pos]],dp[b[pos]]);
        }
        dp[b[i]]=max(dp[b[i]],Get(a[b[i]])+1);
    }
    fr(i,l,pos) Qk(mx[b[i]]);
    sort(b+mid+1,b+r+1,cmp3);
    cdq(mid+1,r);
}

int main(){
    int n,m;scanf("%d%d",&n,&m);
    fr(i,1,n) scanf("%d",&a[i]),mx[i]=a[i],mn[i]=a[i];
    fr(i,1,m){
        int x,y;
        scanf("%d%d",&x,&y);
        mx[x]=max(mx[x],y);
        mn[x]=min(mn[x],y);
    }
    fr(i,1,n) b[i]=i,dp[i]=1;
    cdq(1,n);
    fr(i,1,n) ans=max(ans,dp[i]);
    printf("%d\n",ans);
    return 0;
}
