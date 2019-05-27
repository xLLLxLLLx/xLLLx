#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;

int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	fr(i,1,n) {
		printf("%d",i&1);
	}
	return 0;
}