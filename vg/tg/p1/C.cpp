#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=2e5+10;
struct data{
  int id;
  LL l,r;
}a[N],b[N];
struct node{
  int id;
  LL l,r;
  bool operator < (const node &A) const {
      return r>A.r;
  }
};
priority_queue<node>q;
int d[N];

bool cmp(data A,data B){
  if(A.l!=B.l) return A.l<B.l;
  else return A.r<B.r;
}

void fail(){
  puts("No");
  exit(0);
}

int main(){
  int n,m;scanf("%d%d",&n,&m);
  LL ll,lr;
  scanf("%lld%lld",&ll,&lr);
  fr(i,1,n-1){
    LL l,r;scanf("%lld%lld",&l,&r);
    a[i].id=i,a[i].l=l-lr,a[i].r=r-ll;
    ll=l,lr=r;
  }
  sort(a+1,a+n,cmp);
  fr(i,1,m) b[i].id=i,scanf("%lld",&b[i].l);
  sort(b+1,b+1+m,cmp);
  int gg=0,pos=0;
  //fr(i,1,n-1) printf("id=%d L=%lld R=%lld\n",a[i].id,a[i].l,a[i].r);
  fr(i,1,m){
    while(pos+1<n&&(a[pos+1].l<=b[i].l&&a[pos+1].r>=b[i].l)){
      pos++;
      q.push((node){a[pos].id,a[pos].l,a[pos].r});
    }
    //printf("%d\n",pos);
    if(q.empty()) continue;
    node h=q.top();q.pop();
    //printf("id=%d l=%lld r=%lld\n",h.id,h.l,h.r);
    if(h.l>b[i].l||h.r<b[i].l) fail();
    gg++;d[h.id]=b[i].id;
  }
  if(gg!=n-1) fail();
  puts("Yes");
  fr(i,1,n-1) printf("%d ",d[i]);
  return 0;
}
