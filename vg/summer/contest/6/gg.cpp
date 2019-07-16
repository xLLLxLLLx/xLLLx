#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<vector>
#include<queue>
#include<map>
#include<set>
#include<ctime>
using namespace std;
typedef long long ll;
typedef pair<int,int>P;
const int INF=0x3f3f3f3f,maxn=100005;
#define ls (t<<1)
#define rs ((t<<1)|1)
int num[maxn<<2],lazy[maxn<<2];
void push_up(int t)
{
    num[t]=num[ls]+num[rs];
}
void push_down(int t,int l,int r)
{
    if(lazy[t])
    {
        lazy[t]^=1;
        lazy[ls]^=1,lazy[rs]^=1;
        int mid=(l+r)/2;
        num[ls]=mid-l+1-num[ls],num[rs]=r-mid-num[rs];
    }
}
void update(int L,int R,int l,int r,int t)
{
    if(L<=l&&r<=R)
    {
        num[t]=r-l+1-num[t];
        lazy[t]^=1;
        return ;
    }
    push_down(t,l,r);
    int mid=(l+r)/2;
    if(L<=mid)update(L,R,l,mid,ls);
    if(R>mid)update(L,R,mid+1,r,rs);
    push_up(t);
}
int query(int L,int R,int l,int r,int t)
{
    if(L<=l&&r<=R)return num[t];
    push_down(t,l,r);
    int mid=(l+r)/2,ans=0;
    if(L<=mid)ans+=query(L,R,l,mid,ls);
    if(R>mid)ans+=query(L,R,mid+1,r,rs);
    return ans;
}
int n,k,s[maxn];
vector<int>vl[maxn],vr[maxn];
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=0;i<n;i++)scanf("%d",&s[i]);
    sort(s,s+n);
    while(k--)
    {
        int l,r;
        scanf("%d%d",&l,&r);
        l=lower_bound(s,s+n,l)-s;
        r=upper_bound(s,s+n,r)-s-1;
        if(l>r)continue;
        vl[l].push_back(r),vr[r].push_back(l);
    }
    ll ans=(ll)n*(n-1)*(n-2)/6;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<vl[i].size();j++)update(i,vl[i][j],0,n-1,1);
        int res=0;
        if(i)res+=i-query(0,i-1,0,n-1,1);
        if(i<n-1)res+=query(i+1,n-1,0,n-1,1);
        printf("%lld\n", res);
        ans-=(ll)res*(res-1)/2;
        for(int j=0;j<vr[i].size();j++)update(vr[i][j],i,0,n-1,1);
    }
    cout<<ans<<endl;
    return 0;
}
