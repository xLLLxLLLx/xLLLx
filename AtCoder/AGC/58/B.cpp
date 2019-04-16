#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long 
using namespace std;
const int N=2e5+10,mod=1e9+7;
LL jc[N]={1},ny[N]={1};

LL add(LL x,LL y){
	return (x+y)%mod;
}

LL mul(LL x,LL y){
	return x*y%mod;
}

void Add(LL &x,LL y){
	x=(x+y)%mod;
}

void Mul(LL &x,LL y){
	x=(x*y)%mod;
}

LL q_pow(LL x,int y=mod-2){
	LL ans=1;
	for(;y;y>>=1){
		if(y&1) Mul(ans,x);
		Mul(x,x);
	}
	return ans;
}

LL C(int x,int y){
	return mul(jc[x],mul(ny[y],ny[x-y]));
}

LL Get(int x,int y){
	return C(x+y,y);
}

int main(){
	fr(i,1,N) jc[i]=mul(jc[i-1],i),ny[i]=q_pow(jc[i]);
	int h,w,a,b;
	cin>>h>>w>>a>>b;
	LL ans=Get(w-1,h-1),res=0;
	fr(i,1,b) Add(res,mul(Get(h-a-1,i-1),Get(a-1,w-i))); 
	Add(ans,add(mod,-res));
	printf("%lld\n",ans);
	return 0;
}