#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=110;
LL a[N];

int main(){
  a[1]=1,a[2]=2;
  LL sum=2;int i=2;
  for(;++i;){
    a[i]=a[i-1]+a[i-2];
    printf("%lld\n",a[i]);
    if(a[i]>4000000) break;
    if(a[i]&1) continue;
    sum+=a[i];
  }
  cout<<sum<<endl;
  return 0;
}
