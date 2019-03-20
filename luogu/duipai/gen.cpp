#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int mod=1e9;

int main(){
  fr(o,1,100){
    LL x=rand()%mod+1,y=rand()%mod+1,z=rand()%mod+1;
    printf("%lld %lld %lld\n",x,y,z);
  }
  printf("0 0 0\n");
}
