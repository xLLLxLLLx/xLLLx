#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1e5+10,mod=1073741824;
struct data{
  int x,y,z,id;
}a[N],b[N];
struct node{
  int dp;
  LL f;
}tr[N],d[N];
LL tot=0;
int Ax[N],Ay[N],Az[N];
int n,ans=0;

void read(int &x){
  char ch=getchar();x=0;
  for(;ch<'0'||ch>'9';ch=getchar());
  for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
}

void Add(LL &x,LL y){
  x=(x+y)%mod;
}

bool cmp(data xx,data yy){
  if(xx.x!=yy.x) return xx.x<yy.x;
  if(xx.y!=yy.y) return xx.y<yy.y;
  if(xx.z!=yy.z) return xx.z<yy.z;
}

bool cmpy(data xx,data yy){
  if(xx.y!=yy.y) return xx.y<yy.y;
  else return xx.z<yy.z;
}

void Go(node &x,node y){
  if(x.dp<y.dp) x.dp=y.dp,x.f=y.f;
  else if(x.dp==y.dp) Add(x.f,y.f);
}

void Ch(int x){
  if(d[x].dp<ans) return ;
  else if(d[x].dp==ans) Add(tot,d[x].f);
  else ans=d[x].dp,tot=d[x].f;
}

int lowerbit(int x){ return x&(-x); }

void Upd(int x,node y){
  for(;x<N;x+=lowerbit(x)) Go(tr[x],y);
}

node Get(int x){
  if(!x) return (node){0,0};
  node tmp;tmp.dp=0,tmp.f=0;
  for(;x;x-=lowerbit(x)) Go(tmp,tr[x]);
  return tmp;
}

void Qk(int x){
  for(;x<N;x+=lowerbit(x)) tr[x].dp=0,tr[x].f=0;
}

void cdq(int l,int r){
  if(l==r) return ;
  int mid=(l+r)>>1;
  cdq(l,mid);
  sort(a+l,a+1+mid,cmpy);
  sort(a+mid+1,a+1+r,cmpy);
  int pos=l-1,nw=l;
  fr(i,mid+1,r){
    while(pos+1<=mid&&a[pos+1].y<=a[i].y){
      pos++,Upd(a[pos].z,(node){d[a[pos].id].dp,d[a[pos].id].f});
    }
    node gg=Get(a[i].z);
    gg.dp++;
    Go(d[a[i].id],gg);
  }
  fr(i,l,pos) Qk(a[i].z);
  sort(a+mid+1,a+1+r,cmp);
  cdq(mid+1,r);
}

int main(){
  int T;read(T);
  fr(o,1,T){
    read(n);
    ans=0,tot=0;
    fr(i,1,n) {
      scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].z),a[i].z++,a[i].id=i;
      Ax[i]=a[i].x,Ay[i]=a[i].y,A=a[i].z;
    }
    sort(Ax+1,Ax+1+n),sort(Ay+1,Ay+1+n),sort(Az+1,Az+1+n);
    Ax[0]=unique(Ax+1,Ax+1+n)-Ax-1;
    Ay[0]=unique(Ay+1,Ay+1+n)-Ay-1;
    Az[0]=unique(Az+1,Az+1+n)-Az-1;
    fr(i,1,n){
      a[i].x=lower_bound(Ax+1,Ax+1+Ax[0],a[i].x)-Ax;
      a[i].y=lower_bound(Ay+1,Ay+1+Ay[0],a[i].y)-Ay;
      a[i].z=lower_bound(Az+1,Az+1+Az[0],a[i].z)-Az;
    }
    fr(i,1,n) d[i].dp=1,d[i].f=1;
    sort(a+1,a+1+n,cmp);
    cdq(1,n);
    fr(i,1,n) Ch(i);
    printf("%d %lld\n",ans,tot);
    fr(i,1,n) d[i]=(node){0,0LL};
  }
  return 0;
}
