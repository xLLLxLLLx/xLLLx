#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=1e6+10;
ll jc[N]={1};
ll a,b,x;
int mod;

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
	return x*y%mod;
}

ll q_pow(ll x,int y){
	ll ans=1;
	for(;y;y>>=1){
		if(y&1) Mul(ans,x);
		Mul(x,x);
	}
	return ans;
}

ll cal(int nw){
	ll inv=mul(q_pow(jc[nw],mod-2),b);
	ll pos=(mod-1)*add(nw-inv,mod)+nw;
	if(pos>x) return 0ll;
	return (x-pos)/(mod*1ll*(mod-1))+1;
}

int main(){
	cin>>a>>b>>mod>>x;
	ll ans=0;
	fr(i,1,mod-1){
		jc[i]=mul(jc[i-1],a);
		ans+=cal(i);
	}
	cout<<ans<<endl;
	return 0;
}