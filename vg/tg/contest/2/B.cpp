#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
#define db double
using namespace std;
const int N=1e5+10;
LL a[N];
int q[N];

int main(){
  int n;scanf("%d",&n);
  fr(i,1,n) scanf("%lld",&a[i]);
  LL ans=0;
  rf(i,30,0){
    q[0]=0;
    int res=0;
    fr(j,1,n) if((a[j]>>i)&1) q[++res]=j;
    q[res+1]=n+1;
    //printf("%d %d\n",i,res);
    fr(j,1,res){
      LL pos=0;
      //printf("nwnw%lld\n",a[q[j]]);
      rf(k,q[j]-1,q[j-1]+1){
        //printf("%lld ",a[k]);
        pos=max(pos,a[k]);
        if(pos>=a[q[j]]) break;
        ans=max(ans,pos^a[q[j]]);
      }
      pos=0;
      //puts("");
      fr(k,q[j]+1,q[j+1]-1){
        //printf("%lld ",a[k]);
        pos=max(pos,a[k]);
        if(pos>=a[q[j]]) break;
        ans=max(ans,pos^a[q[j]]);
      }
      //puts("");
    }
  }
  printf("%lld\n",ans);
  return 0;
}
