#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=110;
int a[N][N][N];

int main(){
	srand(time(NULL));
	int T=rand()%5+1;
	printf("%d\n",T);
	fr(o,1,T){
		memset(a,0,sizeof a);
		int n=rand()%1000+1;
		printf("%d\n",n);
		fr(i,1,n) {
			for(;;){
				int x=rand()%101,y=rand()%101,z=rand()%101;
				if(!a[x][y][z]){
					printf("%d %d %d\n",x,y,z);
					a[x][y][z]=1;
					a[x][z][y]=1;
					a[y][x][z]=1;
					a[y][z][x]=1;
					a[z][x][y]=1;
					a[z][y][x]=1;
					break;
				}
			}
		}
	}
}