#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;

int main(){
    srand(time(NULL));
    int T=rand()%4+1;
    printf("%d\n",T);
    fr(o,1,T){
        int n=rand()%10+1,m=rand()%10+1;
        printf("%d %d\n",n,m);
        fr(i,1,n) {
            int x=rand()%1000000000+1;
            printf("%d ",x);
        }
        puts("");
        fr(i,1,m) {
            int x=rand()%2;
            if(x){
                printf("Q ");
                int z=rand()%n+1,y=rand()%n+1;
                if(z>y) swap(z,y);
                int k=rand()%(y-z+1)+1;
                printf("%d %d %d\n",z,y,k);
            } else {
                printf("C ");
                int z=rand()%n+1,y=rand()%1000000000+1;
                printf("%d %d\n",z,y);
            }
        }
    }
    return 0;
}
