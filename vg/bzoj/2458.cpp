#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
#define db double
using namespace std;
const int N=2e5+10;
const db inf=1e18;
struct data{
  db x,y;
}pt[N],a[N];
int res=0;

db pf(db x){ return x*x; }

bool cmx(data A,data B){ return A.x<B.x; }

bool cmy(data A,data B){ return A.y<B.y; }

db js(data i,data j){
  return sqrt(pf(i.x-j.x)+pf(i.y-j.y));
}

db work(int l,int r){
  if(l==r||l+1==r) return inf;
  if(l+2==r){
    db ans=0;
    fr(i,l,r) fr(j,i+1,r) ans+=js(pt[i],pt[j]);
    return ans;
  }
  int mid=(l+r)>>1;
  db tmp=min(work(l,mid),work(mid+1,r)),pos=tmp/2.0;
  res=0;
  fr(i,l,r) if(fabs(pt[i].x-pt[mid].x)<pos) a[++res]=pt[i];
  sort(a+1,a+1+res,cmy);
  fr(i,1,res){
    fr(j,i+1,res){
      if(a[j].y-a[i].y>pos) continue;
      fr(k,j+1,res){
        if(a[k].y-a[i].y>pos) continue;
        db ans=js(a[k],a[j])+js(a[k],a[i])+js(a[j],a[i]);
        tmp=min(tmp,ans);
      }
    }
  }
  return tmp;
}

int main(){
  int n;scanf("%d",&n);
  fr(i,1,n) scanf("%lf%lf",&pt[i].x,&pt[i].y);
  sort(pt+1,pt+1+n,cmx);
  printf("%.6f\n",work(1,n));
  return 0;
}
