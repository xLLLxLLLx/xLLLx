#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
#include<cmath>

#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=5e5+10,mod=1e9+7;
ll a[N],all[N],tr[N];

void Add(ll &x,ll y){
	x=(x+y)%mod;
}

void Mul(ll &x,ll y){
	x=(x*y)%mod;
}

ll add(ll x,ll y){
	return x+y%mod;
}

ll mul(ll x,ll y){
	return x*y%mod;
}

int lower(int x){
	return x&(-x);
}

ll get(int x){
	ll ans=0;
	for(int i=x;i;i-=lower(i)) {
		Add(ans,tr[i]);
	}
	return ans;
}

void upd(int x,ll y){
	for(int i=x;i<N;i+=lower(i)) {
		Add(tr[i],y);
	}
}

int main(){
	int n;
	ll ans=0;
	scanf("%d",&n);
	fr(i,1,n) {
		scanf("%lld",&a[i]);
		all[i]=a[i];
	}
	sort(all+1,all+1+n);
	fr(i,1,n) {
		a[i]=lower_bound(all+1,all+1+n,a[i])-all;
	}
	fr(i,1,n) {
		ll pos=get(a[i]-1);
		Add(ans,mul(mul(pos,n-i+1),all[a[i]]));
		upd(a[i],i);
	}
	memset(tr,0,sizeof tr);
	rf(i,n,1) {
		ll pos=get(a[i]-1);
		Add(ans,mul(mul(pos,i),all[a[i]]));
		upd(a[i],n-i+1);
	}
	fr(i,1,n) {
		Add(ans,mul(mul(i,n-i+1),all[a[i]]));
	}
	printf("%lld\n",ans);
	return 0;
}