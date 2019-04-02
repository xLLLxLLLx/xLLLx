#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=15;
char lx[N];

int get(){
  int x;scanf("%d",&x);
  fr(i,1,x) scanf("%s",lx+1);
  return x;
}

int main(){
  for(;;){
    printf("next 0\n");
    fflush(stdout);
    get();
    printf("next 0 1\n");
    fflush(stdout);
    if(get()==2) break;
  }
  for(;;){
    printf("next 0 1 2 3 4 5 6 7 8 9\n");
    fflush(stdout);
    if(get()==1) break;
  }
  printf("done\n");fflush(stdout);
  return 0;
}
