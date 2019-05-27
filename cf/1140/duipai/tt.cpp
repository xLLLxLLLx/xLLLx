#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int inf=1e9;

int main(){
	srand(time(NULL));
	int n=rand()%10+1;
	printf("%d\n",n);
	fr(i,1,n) {
		int x=rand()%inf;
		printf("%d ",x);
	}
	puts("");
	fr(i,2,n) {
		int x=rand()%(i-1)+1;
		int y=rand()%inf,z=rand()%inf;
		printf("%d %d %d %d\n",x,i,y,z);
	}
	int q=rand()%10+1;
	printf("%d\n",q);
	fr(o,1,q) {
		int x=rand()%(2*n)+1;
		int y=rand()%(2*n)+1;
		printf("%d %d\n",x,y);
	}
	return 0;
}