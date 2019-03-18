#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;

int main(){
    srand(time(NULL));
    int n=rand()%100000+1,m=rand()%100000+1;
    printf("%d %d\n",n,m);
    fr(i,1,n) {
        int x=rand()%200-100;
        printf("%d ",x);
    }
    puts("");
    int sz=n;
    fr(kk,1,m){
        int o=rand()%6;
        if(o==0){
            int x=rand()%(sz+1),y=rand()%10+1;
            printf("INSERT %d %d ",x,y);
            fr(i,1,y){
                int z=rand()%200-100;
                printf("%d ",z);
            }
            puts("");
            sz+=y;
        }
        if(o==1){
            int x=rand()%sz+1;
            int pos=min(sz,sz-x+1);
            int y=rand()%pos+1;
            printf("DELETE %d %d\n",x,y);
            sz-=y;
        }
        if(o==2){
            int x=rand()%sz+1,y=rand()%(sz-x+1)+1,z=rand()%200-100;
            printf("MAKE-SAME %d %d %d\n",x,y,z);
        }
        if(o==3){
            int x=rand()%sz+1,y=rand()%(sz-x+1)+1;
            printf("REVERSE %d %d\n",x,y);
        }
        if(o==4){
            int x=rand()%sz+1,y=rand()%(sz-x+1)+1;
            printf("GET-SUM %d %d\n",x,y);
        }
        if(o==5) printf("MAX-SUM\n");
    }
    return 0;
}

/*
7 11
-18 -23 -11 -32 51 88 -29 
DELETE 7 1
INSERT 5 3 85 97 -3 
INSERT 0 4 38 -95 23 -73 
DELETE 6 7
MAX-SUM
INSERT 1 2 -28 -70 
INSERT 1 10 -99 2 22 -22 -57 -20 21 73 24 -42 
INSERT 17 9 -57 95 -42 -52 -30 -63 -61 30 64 
MAKE-SAME 24 1 -31
GET-SUM 17 4
GET-SUM 2 6

*/
