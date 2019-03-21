#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=10;
int a[N];

bool check(int x){
  a[0]=0;
  for(;x;x/=10) a[++a[0]]=x%10;
  fr(i,1,a[0]/2) if(a[i]!=a[a[0]-i+1]) return false;
  return true;
}

int main(){
  int maxn=0;
  fr(i,100,999) fr(j,100,999){
    int pos=i*j;
    if(check(pos)) maxn=max(maxn,pos);
  }
  cout<<maxn<<endl;
  return 0;
}
