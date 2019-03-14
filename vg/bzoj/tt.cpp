#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;

int main(){
    srand(time(NULL));
    printf("10000 10000\n");
    fr(i,1,10000){
        int y=rand()%2;
        if(y){
            printf("Q ");
            int x=rand()%10000+1,y=rand()%10000+1;
            if(x>y) swap(x,y);
            printf("%d %d\n",x,y);
        } else {
            printf("C ");
            int x=rand()%10000+1,y=rand()%1000000+1;
            printf("%d %d\n",x,y);
        }
    }
    return 0;
}
