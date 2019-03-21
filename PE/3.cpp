#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;

int main(){
  LL maxn=0;
  LL n;scanf("%lld",&n);
  LL len=sqrt(n);
  fr(i,2,len){
    if(n%i==0){
      maxn=max(maxn,i*1LL);
      while(n%i==0) n/=i;
    }
  }
  maxn=max(maxn,n);
  cout<<maxn<<endl;
  return 0;
}
