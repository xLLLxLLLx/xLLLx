#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#include<vector>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long 
using namespace std;
const int N=1010,mod=1e9+7;
ll f[N][2];

void Add(ll &x,ll y){
	x=(x+y)%mod;
}

void Mul(ll &x,ll y){
	x=(x*y)%mod;
}

ll add(ll x,ll y){
	return (x+y)%mod;
}

ll mul(ll x,ll y){
	return (x*y)%mod;
}

int main(){
	int n;cin>>n;
	ll ans=1;
	fr(i,2,n){
		Mul(ans,2);
	}
	cout<<ans<<endl;
	return 0;
}