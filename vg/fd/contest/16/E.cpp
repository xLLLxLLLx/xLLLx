#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1e6+10,mod=1e9+7;
LL tr[N];

int lowerbit(int x){
	return x&(-x);
}

void Add(LL &x,LL y){
	x=(x+y+mod)%mod;
}

void Mul(LL &x,LL y){
	x=(x*y)%mod;
}

LL add(LL x,LL y){
	return (x+y+mod)%mod;
}

LL mul(LL x,LL y){
	return (x*y)%mod;
}

void change(int x,LL y){
	for(;x<N;){
		Add(tr[x],y);
		x+=lowerbit(x);
	}
}

LL Get(int x){
	LL ans=0;
	if(!x) return 0;
	for(;x;){
		Add(ans,tr[x]);
		x-=lowerbit(x);
	}
	return ans;
}

int main(){
	int n;scanf("%d",&n);
	fr(i,1,n){
		int x;scanf("%d",&x);
		LL pos=Get(x);
		Mul(pos,x);Add(pos,x);
		Add(pos,add(-Get(x),Get(x-1)));
		change(x,pos);
	}
	printf("%lld\n",Get(N-1));
	return 0;
}
