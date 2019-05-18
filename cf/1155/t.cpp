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