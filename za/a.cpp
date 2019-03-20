#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#define rep(i,l,r) for(int i=(l);i<=(r);++i)
#define per(i,r,l) for(int i=(r);i>=(l);--i)
#define mp make_pair
#define fi first
#define se second
using namespace std;
const int maxn=6010;
int n,q,a,b,c[maxn],k,x,tp;
double dp[maxn],ans,psc=1;
pair<double,double> f[maxn<<1];
int main(){
    scanf("%d%d%d%d",&n,&q,&a,&b);
    rep(i,1,n){
        scanf("%d",&x);c[i]=x;
        if(i==1){
            f[++tp]=mp(1,(1-x)*2);
            f[++tp]=mp(1e18,(1e18-x)*2);
        }
        else{
            per(i,tp,k+1) f[i+2]=f[i];
            f[k+1]=mp(psc,0);f[k+2]=mp(psc,0);
            rep(i,1,k+1) f[i].fi+=a;tp+=2;
            rep(i,k+2,tp) f[i].fi+=b;
            rep(i,1,tp) f[i].se+=(f[i].fi-x)*2;
        }
        if(f[1].se>=0) k=0,psc=f[1].fi;
        else{
            rep(i,1,tp-1) if(f[i].se<=0&&f[i+1].se>=0){k=i;break;}
            psc=f[k].fi-(f[k+1].fi-f[k].fi)/(f[k+1].se-f[k].se)*f[k].se;
        }
        dp[i]=psc;
    }
    dp[n]=min(dp[n],(double)q);
    per(i,n-1,1){
        if(dp[i]>dp[i+1]-a) dp[i]=dp[i+1]-a;
        else if(dp[i]<dp[i+1]-b) dp[i]=dp[i+1]-b;
    }
    rep(i,1,n) printf("%.10lf ",dp[i]);puts("");
    rep(i,1,n) ans+=(dp[i]-c[i])*(dp[i]-c[i]);
    printf("%.10lf\n",ans);
    return 0;
}
