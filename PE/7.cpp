#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1e4+10,M=1e7+10;
int flg[M],gg[N];

int main(){
  for(int i=2;i<=1e7;++i){
    if(!flg[i]) gg[++gg[0]]=i;
    fr(j,1,gg[0]){
      if(i*gg[j]>M) break;
      flg[i*gg[j]]=1;
      if(i%gg[j]==0) break;
    }
    if(gg[0]>=10001) break;
  }
  fr(i,1,10) printf("%d ",gg[i]);
  puts("");
  printf("%d\n",gg[10001]);
  return 0;
}
