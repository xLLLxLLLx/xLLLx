#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
LL x,y,p,q;

bool check(LL k){
  //printf("%lld %lld %lld\n",k*p-x,k*q-y,k*q-k*p-y+x);
  if(k*p-x<0) return false;
  if(k*q-y<0) return false;
  if(k*q-k*p-y+x<0) return false;
  return true;
}

int main(){
  int T;scanf("%d",&T);
  fr(o,1,T){
    cin>>x>>y>>p>>q;
    LL ans=-1,l=0,r=1e9;
    while(l<=r){
      LL mid=(l+r)>>1;
      if(check(mid)) ans=mid,r=mid-1;
      else l=mid+1;
    }
    if(ans==-1) printf("%lld\n",ans);
    else printf("%lld\n",ans*q-y);
  }
  return 0;
}
