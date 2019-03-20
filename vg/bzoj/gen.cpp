#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;

int main(){
  srand(time(NULL));
  int n=20000,m=20000;
  printf("%d %d\n",n,m);
  fr(o,1,n){
    int tp=rand()%3+1;
    if(tp==1||tp==3) {
      int x=rand()%20000+1,y=rand()%20000+1;
      printf("%d %d %d\n",tp,x,y);
    } else if(tp==2) {
      int x=rand()%o;
      printf("%d %d\n",tp,o);
    }
  }
  return 0;
}
