#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=1e4+10;
ll jc[N]={1},ny[N]={1};

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

void init(){
	fr(i,1,N-1) jc[i]=mul(jc[i-1],i);
	fr(i,1,N-1) ny[i]=q_pow(jc[i],mod-2);
}

ll C(int x,int y){
	if(y>x||y<0) return 0ll;
	return mul(jc[x],mul(ny[y],ny[x-y]));
}

int main(){
	init();
	int p,s,r;scanf("%d%d%d",&p,&s,&r);
	ll ans=0;
	fr(w,r,s){
		fr(k,1,p){
			if(s<k*w) break;
			int m=p-k;
			ll pos=C(p,m),C(y+m-1,m-1);
			fr(i,0,m){
				if(i&1) Add(ans,)
					else 
			}
		}
	}
	return 0;
}