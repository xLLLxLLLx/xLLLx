#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>

#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int mod=998244353,N=2e5+10;
ll a[N],b[N];

ll mul(ll x,ll y) {return x*y;}

int main(){
	int n;cin>>n;
	fr(i,1,n) scanf("%lld",&a[i]),a[i]=mul(a[i],mul(i,n-i+1));
	fr(i,1,n) scanf("%lld",&b[i]);
	sort(a+1,a+1+n),sort(b+1,b+1+n);
	ll ans=0;
	fr(i,1,n) ans=(ans+(a[i]%mod)*(b[n-i+1]%mod)%mod)%mod; 
	cout<<ans<<endl;
	return 0;
}