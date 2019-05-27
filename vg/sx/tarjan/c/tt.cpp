#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;

int main(){
	int n=10000;
	printf("%d %d\n",n,n-1);
	fr(i,1,n-1) {
		printf("%d %d\n",i,i+1);
	}
	printf("0\n");
	return 0;
}