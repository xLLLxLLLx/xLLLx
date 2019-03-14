#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=5e4+10;
struct data{
    int l,r,id;
}a[N];
int A[N],B[N];
LL fz[N],fm[N],nm[N];

bool cmp(data xx,data yy){
    return B[xx.l]==B[yy.l]?xx.r<yy.r:xx.l<yy.l;
}

LL gcd(LL x,LL y){
    return y?gcd(y,x%y):x;
}

LL pf(LL x){
    return x*x;
}

int main(){
    int n,m;scanf("%d%d",&n,&m);
    int sz=sqrt(n);
    fr(i,1,n) scanf("%d",&A[i]),B[i]=i/sz+1;
    fr(i,1,m){
        a[i].id=i;
        scanf("%d%d",&a[i].l,&a[i].r);
    }
    sort(a+1,a+1+m,cmp);
    int l=1,r=0;
    LL ff=0;
    fr(i,1,m){
        while(l<a[i].l) ff-=pf(nm[A[l]]),ff+=pf(--nm[A[l]]),l++;
        while(l>a[i].l) l--,ff-=pf(nm[A[l]]),ff+=pf(++nm[A[l]]);
        while(r<a[i].r) r++,ff-=pf(nm[A[r]]),ff+=pf(++nm[A[r]]);
        while(r>a[i].r) ff-=pf(nm[A[r]]),ff+=pf(--nm[A[r]]),r--;
        LL pos=a[i].r-a[i].l+1,sum=pos*pos;
        fz[a[i].id]=ff-pos,fm[a[i].id]=sum-pos;
        LL gg=gcd(ff-pos,sum-pos);
        if(a[i].l==a[i].r) fz[a[i].id]=0,fm[a[i].id]=1;
        else fz[a[i].id]/=gg,fm[a[i].id]/=gg;
    }
    fr(i,1,m) printf("%lld/%lld\n",fz[i],fm[i]);
    return 0;
}
