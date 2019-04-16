#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=4010,mod=998244353;
LL dp[N][N],jc[N]={1};

void Add(LL &x,LL y){
	x=(x+y)%mod;
}

void Mul(LL &x,LL y){
	x=(x*y)%mod;
}

LL add(LL x,LL y){
	return (x+y)%mod;
}

LL mul(LL x,LL y){
	return x*y%mod;
}

LL q_pow(LL x,int y=mod-2){
	LL ans=1;
	for(;y;y>>=1){
		if(y&1) Mul(ans,x);
		Mul(x,x);
	}
	return ans;
}

int main(){
	int n,k,l;scanf("%d%d%d",&n,&k,&l);
	dp[1][1]=1;
	fr(i,1,n*2) fr(j,0,min(i,n)) {
		if(dp[i][j]){
			Add(dp[i+1][j+1],dp[i][j]);
			if(j) Add(dp[i+1][j-1],mul(dp[i][j],j));
		}
	}
	LL ans=0;
	fr(i,1,n) jc[i]=mul(jc[i-1],i);
	fr(i,1,n*2) fr(j,k,min(i,n)) {
		Add(ans,mul(mul(dp[i][j],dp[n*2-i][j]),jc[j]));
	}
	Mul(ans,mul(l,q_pow(2*n+1)));
	Mul(ans,q_pow(dp[2*n][0]));
	printf("%lld\n",ans);
	return 0;
}