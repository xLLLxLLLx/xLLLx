#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ls ch[x][0]
#define rs ch[x][1]
#define LL long long
using namespace std;

int main(){
  srand(time(NULL));
  int n=5;
  cout<<n<<endl;
  fr(o,1,n){
    cout<<"10"<<endl;
    fr(i,2,10){
      int x=rand()%(i-1)+1;
      int w=rand()%1000000+1;
      printf("%d %d %d\n",i,x,w);
    }
    fr(i,1,10){
      int x=rand()%2;
      if(x){
        int y=rand()%10+1,z=rand()%10+1;
        printf("Q %d %d\n",y,z);
      } else {
        int y=rand()%9+1,z=rand()%1000000+1;
        printf("C %d %d\n",y,z);
      }
    }
    printf("D\n");
  }
  return 0;
}
