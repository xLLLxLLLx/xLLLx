#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=3e5+10,mod=1e9+7;

int main(){
  int n;scanf("%d",&n);
  LL maxn=0;
  fr(i,1,n){
    LL x;
    scanf("%lld",&x);
    maxn+=x;
    maxn%=mod;
  }
  printf("%lld\n",maxn);
  return 0;
}
