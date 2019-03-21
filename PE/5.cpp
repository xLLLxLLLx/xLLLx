#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;

int main(){
  LL pos=0,tmp=0;
  fr(i,1,100) pos+=i*i*1LL;
  tmp=(5050)*5050;
  cout<<tmp-pos<<endl;
  return 0;
}
