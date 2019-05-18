#include<iostream>
#include<cstdio>
#include<vector>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;

int main(){
	int n;cin>>n;
	if(n==3) printf("13\n");
	else if(n==0) printf("15\n");
	else printf("%d\n",15-n+(n&1));
	return 0;
}