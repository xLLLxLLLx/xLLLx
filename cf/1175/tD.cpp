#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=3e5+10;
ll a[N],qz[N];
int n,k;

bool cmp(ll x,ll y){
	return x>y;
}

int main(){
	ll ans=0;
	scanf("%d%d",&n,&k);
	fr(i,1,n) {
		scanf("%lld",&a[i]);
	}
	rf(i,n,1) qz[i]=qz[i+1]+a[i];
	ans=qz[1];
	sort(qz+2,qz+1+n,cmp);
	fr(i,2,k) {
		// printf("%lld\n",qz[i]);
		ans+=qz[i];
	}
	printf("%lld\n",ans);
	return 0;
}