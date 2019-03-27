#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ls ch[x][0]
#define rs ch[x][1]
#define LL long long
using namespace std;

int main(){
  srand(time(NULL));
  int n=10;
  cout<<n<<endl;
  fr(o,1,n){
    cout<<"10000"<<endl;
    fr(i,2,10000){
      int x=rand()%(i-1)+1;
      int w=rand()%1000000+1;
      printf("%d %d %d\n",i,x,w);
    }
    fr(i,1,10000){
      int x=rand()%2;
      {
        int y=rand()%10000+1,z=rand()%10000+1,k=rand()%100+1;
        printf("DIST %d %d\n",y,z);
      } else {
        int y=rand()%9999+1,z=rand()%1000000+1;
        printf("C %d %d\n",y,z);
      }
    }
    printf("DONE\n");
  }
  return 0;
}
