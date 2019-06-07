#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;

int main(){
	int T;scanf("%d",&T);
	fr(o,1,T) {
		ll n,k;
		scanf("%lld%lld",&n,&k);
		ll ans=0;
		for(;;) {
			if(n%k) ans+=n%k;
			n-=n%k;
			if(!n) break;
			n/=k,ans++;
		}
		printf("%lld\n",ans);
	}
	return 0;
}