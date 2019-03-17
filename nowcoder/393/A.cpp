#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=2e5+10;
char A[N],B[N];

int main(){
  scanf("%s%s",A+1,B+1);
  int len=strlen(A+1);
  int lt,flg=0;
  LL maxn=0;
  fr(i,1,len){
    if(A[i]!=B[i]){
      if(flg) maxn=max(maxn,(i-lt)*1LL);
      flg=0;lt=len+1;
    } else {
      if(!flg) lt=i;
      flg=1;
    }
  }
  maxn=max(maxn,(len-lt+1)*1LL);
  printf("%lld\n",(maxn+1)*(maxn+1)-1);
}
