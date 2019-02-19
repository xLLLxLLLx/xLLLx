#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<cmath>
#include<map>
#include<stack>
#include<vector>
#include<queue>
#include<set>
#include<algorithm>

#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;

int main(){
	int q;cin>>q;
	fr(o,1,q){
		LL n,a,b;
		scanf("%lld%lld%lld",&n,&a,&b);
		if(a*2<=b) printf("%lld\n",a*n);
		else {
			LL pos=(n/2)*b;
			if(n&1) pos+=a;
			printf("%lld\n",pos);
		}
	}
	return 0;
}