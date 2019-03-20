#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
map<LL,LL>mp;
LL p,b,n;

void Mul(LL &x,LL y){
  x=(x*y)%p;
}

LL q_pow(LL x,LL y){
  LL ans=1;
  for(;y;y>>=1){
    if(y&1) Mul(ans,x);
    Mul(x,x);
  }
  return ans;
}

void UPD(LL x,LL y){
  //printf("%lld %lld\n",x,y);
  if(mp.count(x)) mp[x]=max(mp[x],y);
  else mp[x]=y;
}

LL Find(LL x){
  //printf("f%lld\n",x);
  if(mp.count(x)) return mp[x];
  else return -1;
}

int main(){
  cin>>p>>b>>n;
  LL len=ceil(sqrt(double(p)));
  LL ans=1e18,pos=n;
  //printf("len=%lld\n",len);
  fr(i,0,len){
    UPD(pos,i);
    Mul(pos,b);
  }
  fr(i,0,len){
    LL gg=q_pow(b,i*1LL*len);
    LL pos=Find(gg);
    if(pos!=-1) {
      LL tmp=i*1LL*len-pos;
      if(tmp<0) tmp=p-1-tmp;
      //printf("tt%lld\n",tmp);
      ans=min(ans,tmp);
    }
  }
  if(ans==1e18) printf("no solution\n");
  else printf("%lld\n",ans);
  return 0;
}
