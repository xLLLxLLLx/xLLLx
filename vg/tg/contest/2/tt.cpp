#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define db double
using namespace std;
const int N=1e5+10;
int mk[N],a[N],q[N];

int main(){
  int n;scanf("%d",&n);
  fr(i,1,n) {
    scanf("%d",&a[i]);
    rf(j,25,0){
      if((a[i]>>j)&1){
        mk[i]=j;
        break;
      }
    }
  }
  int maxn=0;
  fr(i,1,n) maxn=max(maxn,mk[i]);
  int ans=0;
  rf(i,maxn,0){
    q[0]=0;
    fr(j,1,n) if(mk[j]>=i) q[++q[0]]=j;
    q[q[0]+1]=n+1;
    //printf("now%d\n",q[0]);
    fr(j,1,q[0]){
      int pos=0;
      //printf("xx%d ",a[q[j]]);
      rf(k,q[j]-1,q[j-1]+1){
        pos=max(pos,a[k]);
        ans=max(ans,pos^a[q[j]]);
      }
      pos=0;
      fr(k,q[j]+1,q[j+1]-1){
        pos=max(pos,a[k]);
        ans=max(ans,pos^a[q[j]]);
      }
    }
    //puts("");
  }
  printf("%d\n",ans);
  return 0;
}
