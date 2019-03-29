#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=5010;
map<int,int>mp[2];
int a[N],b[N],pre[N],nm[N];

int Get(int id,int x){
  if(mp[id].count(x)) return mp[id][x];
  else return 0;
}

int main(){
  int n;scanf("%d",&n);
  fr(i,1,n){
    scanf("%d",&a[i]);
    if(a[i]<0) b[i]=1,a[i]=-a[i];
  }
  fr(i,1,n){
    int len=sqrt(a[i]);
    fr(j,2,len){
      if(a[i]%j==0){
        int pos=0;
        while(a[i]%j==0) a[i]/=j,pos++;
        if(pos&1) a[i]*=j;
      }
    }
    if(b[i]) pre[i]=Get(0,a[i]),mp[0][a[i]]=i;
    else pre[i]=Get(1,a[i]),mp[1][a[i]]=i;
  }
  fr(i,1,n){
    int pos=1,flg=0,F=0;
    nm[pos]++;
    if(!a[i]) F=1,flg=1;
    fr(j,i+1,n){
      if(!a[j]) 2333;
      else if(pre[j]<i){
        if(flg) flg=0;
        else pos++;
      }
      nm[pos]++;
    }
  }
  fr(i,1,n) printf("%d ",nm[i]);
  return 0;
}
