#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=2e5+10;
struct data{
  int x,y;
}a[N],b[N];
int S1[N],S2[N];
LL ans=0;

bool cmx(data A,data B){ return A.x<B.x; }

bool cmy(data A,data B){ return A.y<B.y; }

void work(int l,int r){
  if(l==r) return ;
  int mid=(l+r)>>1;
  sort(a+l,a+r+1,cmy);
  sort(a+l,a+mid+1,cmx),sort(a+mid+1,a+r+1,cmx);
  S1[0]=S2[0]=0;
  int nw=l-1;
  /*printf("l=%d r=%d\n",l,r);
  fr(i,l,r){
    printf("%d %d\n",a[i].x,a[i].y);
  }*/
  fr(i,mid+1,r){
    while(S1[0]&&a[S1[S1[0]]].y>=a[i].y) S1[0]--;
    S1[++S1[0]]=i;
    while(nw+1<=mid&&a[nw+1].x<=a[i].x){
      nw++;
      while(S2[0]&&a[S2[S2[0]]].y<=a[nw].y) S2[0]--;
      S2[++S2[0]]=nw;
    }
    int l=1,r=S2[0],pos=-1,tmp=a[S1[S1[0]-1]].x;
    if(S1[0]==1) tmp=-1;
    while(l<=r){
      int mid=(l+r)>>1;
      if(a[S2[mid]].x>tmp) pos=mid,r=mid-1;
      else l=mid+1;
    }
    if(pos!=-1) ans+=S2[0]-pos+1;
    //printf("gg%d %d,S2=%d pos=%d\n",a[i].x,a[i].y,S2[0],pos);
  }
  work(l,mid),work(mid+1,r);
}

int main(){
  int n;scanf("%d",&n);
  a[0].x=a[0].y=-1;
  fr(i,1,n) scanf("%d%d",&a[i].x,&a[i].y);
  work(1,n);
  printf("%lld\n",ans);
  return 0;
}
