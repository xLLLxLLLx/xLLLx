#include<bits/stdc++.h>
#include<unordered_map>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
unordered_map<int,int>mp;
int gcd(int a,int b){ return b?gcd(b,a%b):a; }
int mul(int a,int b,int p){ return 1ll*a*b%p; }

int Get(int x,int p,int y){
  int g=gcd(x,p),dd=0,zz=1;
  while(g!=1){
   if(y%g){
    if(y!=1) return -1;
    else return dd;
   }
   p/=g,y/=g;
   zz=mul(x/g,zz,p);
   g=gcd(x,p);dd++;
  }
  mp.clear();
  int t=ceil(sqrt(double(p)));
  int pos=1;
  fr(i,0,t-1){
    mp[mul(pos,y,p)]=i;
    pos=mul(pos,x,p);
  }
  int tmp=zz,ans=1e9;
  fr(i,1,t){
    tmp=mul(tmp,pos,p);
    if(mp.count(tmp)) return i*t-mp[tmp]+dd; 
  }
  return -1;
}

int main(){
  int x,p,y;
  while(scanf("%d%d%d",&x,&p,&y)==3){
    if(!x&&!p&&!y) break;
    int ans=Get(x,p,y);
    if(ans==-1) printf("No Solution\n");
    else printf("%d\n",ans);
  }
  return 0;
}
