#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
#include<cmath>

#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int mod=1e9+7;

void Add(ll &x,ll y){
	x=(x+y+mod)%mod;
}

void Mul(ll &x,ll y){
	x=(x*y)%mod;
}

ll add(ll x,ll y){
	return (x+y+mod)%mod;
}

ll mul(ll x,ll y){
	return (x*y)%mod;
}

ll q_pow(ll x,int y){
	ll ans=1;
	for(;y;y>>=1){
		if(y&1) Mul(ans,x);
		Mul(x,x);
	}
	return ans;
}

int get(ll x){
	if(x==1) return 1;
	int res=0;
	ll len=sqrt(x);
	fr(i,2,len){
		if(x%i==0){
			res++;
			x/=i;
			if(x%i==0) return 0;
		}
	}
	if(x!=1) res++;
	return (res&1) ? -1 : 1;
}

int main(){
	ll x,y;
	scanf("%lld%lld",&x,&y);
	if(y%x) return printf("0\n"),0;
	ll pos=y/x;
	ll len=sqrt(pos);
	ll ans=0;
	fr(i,1,len){
		if(pos%i) continue;
		Add(ans,mul(get(i),q_pow(2,pos/i-1)));
		if(i*i!=pos) Add(ans,mul(get(pos/i),q_pow(2,i-1)));
	}
	printf("%lld\n",ans);
	return 0;
}