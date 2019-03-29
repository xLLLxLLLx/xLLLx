#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ls ch[x][0]
#define rs ch[x][1]
#define LL long long
using namespace std;

int main(){
  srand(time(NULL));
    cout<<"100000"<<endl;
    fr(i,2,100000){
      int x=rand()%(i-1)+1;
      printf("%d %d\n",i,x);
    }
    printf("100000\n");
    fr(i,1,100000){
      int x=rand()%2;
      int y=rand()%100000+1;
      printf("%d %d\n",x,y);
    }
  return 0;
}
