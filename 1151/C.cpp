#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
#include<vector>
#include<cmath>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int mod=1e9+7;
LL qwq;

void Add(LL &x,LL y){
	x%=mod,y%=mod;
	x=(x+y)%mod;
}

void Mul(LL &x,LL y){
	x%=mod,y%=mod;
	x=(x*y)%mod;
}

LL add(LL x,LL y){
	x%=mod,y%=mod;
	return (x+y)%mod;
}

LL mul(LL x,LL y){
	x%=mod,y%=mod;
	return (x*y)%mod;
}

LL js(LL x,LL y){
	LL pos=mul(mul(add(mul(x,2),mul(y-1,2)),y),qwq);
	//printf("%lld\n",pos);
	return pos;
}

LL cal(LL x){
	if(!x) return 0;
	LL gg=1,res=1,tmp=2;
	int nw=1;
	LL ans=0;
	for(;;){
		//cout<<gg<<" "<<res<<" "<<tmp<<" "<<endl;
		if(x<=gg){
			if(nw) Add(ans,js(res,x));
				else Add(ans,js(tmp,x));
			break;
		} else {
			if(nw) Add(ans,js(res,gg)),Add(res,mul(gg,2));
			else Add(ans,js(tmp,gg)),Add(tmp,mul(gg,2));
		}
		x-=gg;
		gg*=2,nw^=1;
	}
	return ans;
}

LL q_pow(LL x,int y=mod-2){
	LL ans=1;
	for(;y;y>>=1){
		if(y&1) ans=ans*x%mod;
		x=x*x%mod;
	}
	return ans;
}

int main(){
	LL l,r;cin>>l>>r;
	qwq=q_pow(2);
	printf("%lld\n",(cal(r)-cal(l-1)+mod)%mod);
	return 0;
}