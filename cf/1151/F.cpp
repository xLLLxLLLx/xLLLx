#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=110,mod=1e9+7;
struct data{
	ll a[N][N];
}qx;
ll qwq,inv;
int n,k,b[N];

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

data cal(data A,data B){
	data C;
	fr(i,0,n) fr(j,0,n){
		C.a[i][j]=0;
		fr(k,0,n) Add(C.a[i][j],mul(A.a[i][k],B.a[k][j]));
	}
	return C;
}

data ksm(data A,int y){
	data B;
	fr(i,0,n) fr(j,0,n) B.a[i][j]=(i==j);
	for(;y;y>>=1){
		if(y&1) B=cal(A,B);
		A=cal(A,A);
	}
	return B;
}

ll cal(ll x){
	return mul(mul(x,x-1),qwq);
}

int main(){
	scanf("%d%d",&n,&k);
	qwq=q_pow(2,mod-2),inv=q_pow(q_pow(cal(n),mod-2),k);
	int zero=0,one=0;
	fr(i,1,n){
		scanf("%d",&b[i]);
		if(b[i]) one++;
		 else zero++;
	}
	int nw=0;
	fr(i,1,zero) if(!b[i]) nw++;
	data gg;
	fr(i,0,zero){
		if(n-zero-zero+i<0) continue;
		gg.a[i][i]=add(add(add(cal(zero),cal(one)),mul(i,zero-i)),mul(zero-i,one-zero+i));
		gg.a[i][i+1]=mul(zero-i,zero-i);
		if(i) gg.a[i][i-1]=mul(i,one-zero+i);
	}
	// fr(i,0,zero) fr(j,0,zero){
	// 	printf("a[%d][%d]=%lld\n",i,j,gg.a[i][j]);
	// }
	gg=ksm(gg,k);
	ll ans=mul(gg.a[nw][zero],inv);
	cout<<ans<<endl;
	return 0;
}