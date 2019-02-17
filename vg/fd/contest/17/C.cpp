#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
#define db double
using namespace std;
const int N=55;
int x[N],y[N];

int main(){
	int n,z;scanf("%d",&n);
	fr(i,1,n) scanf("%d%d%d",&x[i],&y[i],&z);
	fr(i,1,n-1) printf("(");
	fr(i,1,n){
		printf("(%d*((1-abs((t-%d)))+abs((abs((t-%d))-1))))",x[i]/2,i,i);
		if(i>1) printf(")");
		if(i<n) printf("+");
	}
	puts("");
	fr(i,1,n-1) printf("(");
	fr(i,1,n){
		printf("(%d*((1-abs((t-%d)))+abs((abs((t-%d))-1))))",y[i]/2,i,i);
		if(i>1) printf(")");
		if(i<n) printf("+");
	}
	return 0;
}
