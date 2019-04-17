#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;

int main(){
	int q;scanf("%d",&q);
	fr(o,1,q){
		LL k;int x;
		scanf("%lld%d",&k,&x);
		printf("%lld\n",(k-1)*9+x);
	}
	return 0;
}