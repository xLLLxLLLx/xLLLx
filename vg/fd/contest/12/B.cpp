#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
int a[22];

int main(){
	LL x;scanf("%lld",&x);
	LL zz=0;int res=0;
	for(;x;) {
		++res;
		int y=x%10;
		if(y>=5) a[res]=9-y;
		else a[res]=y;
		x/=10;
	}
	if(!a[res]) a[res]=9;
	rf(i,res,1) {
		zz=zz*10+a[i];
	}
	printf("%lld\n",zz);
	return 0;
}
