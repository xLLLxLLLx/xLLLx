#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ls ch[x][0]
#define rs ch[x][1]
#define LL long long
using namespace std;

int main(){
  srand(time(NULL));
  int n=rand()%10+1,m=rand()%10+1;
  printf("%d %d\n",n,m);
  fr(i,2,n){
    int y=rand()%(i-1)+1;
    printf("%d %d\n",i,y);
  }
  fr(i,1,m){
    int x=rand()%2,y=rand()%n+1;
    printf("%d %d\n",x,y);
  }
  return 0;
}
