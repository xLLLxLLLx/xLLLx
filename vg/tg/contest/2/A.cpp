#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define db double
using namespace std;
const db PI=acos(-1);
const int N=10;
db kk[N],bb[N];
struct data{ db x,y; }a[N];
struct node{
  db l,r,flg,v;
}zz[N];
db w,h,Arg;
int res=0;

db cross(data A,data B){
  return A.x*B.y-A.y*B.x;
}

bool cmp(data xx,data yy){
  return atan2(xx.y,xx.x)<atan2(yy.y,yy.x);
}

db js(){
  sort(a+1,a+1+res,cmp);
  db ans=0;
  a[res+1]=a[1];
  fr(i,1,res){
    ans+=cross(a[i],a[i+1]);
  }
  return ans/2.0;
}

db jsx(db k,db b,db y){
  return (y-b)/k;
}

db jsy(db k,db b,db x){
  return k*x+b;
}

void init(){
  kk[1]=kk[3]=tan(Arg);
  kk[2]=kk[4]=-1/tan(Arg);
  bb[1]=h/2.0/cos(Arg);
  bb[2]=w/2.0/sin(Arg);
  bb[3]=-bb[1],bb[4]=-bb[2];
  zz[1].l=zz[2].l=-w/2.0;
  zz[1].r=zz[2].r=w/2.0;
  zz[1].flg=zz[2].flg=1;
  zz[1].v=h/2.0,zz[2].v=-h/2.0;
  zz[3].l=zz[4].l=-h/2.0;
  zz[3].r=zz[4].r=h/2.0;
  zz[3].flg=zz[4].flg=0;
  zz[3].v=w/2.0,zz[4].v=-w/2.0;
}

int main(){
  cin>>w>>h>>Arg;
  if(Arg==90){
    printf("%.12f\n",min(h,w)*min(h,w));
    return 0;
  }
  Arg=Arg/180.0*PI;
  db tmp;
  init();
  fr(i,1,4){
    fr(j,1,4){
      if(!zz[j].flg){
        tmp=jsy(kk[i],bb[i],zz[j].v);
        if(tmp>=zz[j].l&&tmp<=zz[j].r) a[++res]=(data){tmp,zz[j].v};
      } else {
        tmp=jsx(kk[i],bb[i],zz[j].v);
        if(tmp>=zz[j].l&&tmp<=zz[j].r) a[++res]=(data){zz[j].v,tmp};
      }
    }
  }
  printf("%.12f\n",js());
  return 0;
}
